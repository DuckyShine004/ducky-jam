#include <fstream>
#include <stdexcept>

#include <zip.h>
#include <fmt/format.h>
#include <zipconf.h>

#include "game/parser/importer.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"
#include "engine/audio/audio_manager.hpp"
#include "game/parser/beatmap.hpp"
#include "game/parser/converter.hpp"

using namespace core::logger;
using namespace core::utility;

namespace game::parser {

void Importer::import(const std::vector<std::string> &paths) {

    for (const std::string &path : paths) {
        const std::string &extension = FileUtility::get_extension(path);

        if (extension != ".osz") {
            continue;
        }

        const std::vector<std::string> &extracted_paths = extract(path);

        std::unordered_map<std::string, std::string> audio_hashes = handle_audio_files(extracted_paths);
        handle_beatmap_files(extracted_paths, audio_hashes);

        // we only need to temporarily parse the beatmap to get the metadata
    }
    // if extracted successfully, we can safely delete the .osz file and clear the tmp directory
}

std::vector<std::string> Importer::extract(const std::string &path) {
    int error = 0;
    zip *archive = zip_open(path.c_str(), 0, &error);

    if (!archive) {
        throw std::runtime_error(fmt::format("Failed to extract '{}'. Error code: {}", path, error));
    }

    zip_int64_t file_count = zip_get_num_entries(archive, 0);
    std::vector<std::string> output_paths;

    for (zip_int64_t i = 0; i < file_count; ++i) {
        struct zip_stat file_stat;

        zip_stat_init(&file_stat);

        if (zip_stat_index(archive, i, 0, &file_stat) != 0) {
            continue;
        }

        LOG_INFO("Creating temporary file: {}", file_stat.name);

        zip_file *zip = zip_fopen_index(archive, i, 0);

        if (!zip) {
            throw std::runtime_error(fmt::format("Failed to open zip file: {}", file_stat.name));
        }

        std::string output_path = std::string(m_OUTPUT_DIRECTORY) + "/" + file_stat.name;
        std::ofstream output_file(output_path, std::ios::binary);

        if (!output_file.is_open()) {
            throw std::runtime_error(fmt::format("Failed to create output file: {}", output_path));
            zip_fclose(zip);
        }

        std::vector<char> buffer(8192);
        zip_int64_t bytes_read = 0;

        while ((bytes_read = zip_fread(zip, buffer.data(), buffer.size())) > 0) {
            output_file.write(buffer.data(), bytes_read);
        }

        output_file.close();
        zip_fclose(zip);

        output_paths.emplace_back(output_path);
    }

    return output_paths;
}

std::unordered_map<std::string, std::string> Importer::handle_audio_files(const std::vector<std::string> &paths) {
    std::unordered_map<std::string, std::string> audio_hashes;

    // get hash: basename, hash
    for (const std::string &path : paths) {
        const std::string &extension = FileUtility::get_extension(path);

        if (extension == ".mp3") {
            const std::string &hash = FileUtility::hash_file(path);
            const std::string &filename = FileUtility::get_filename_from_path(path);

            engine::audio::AudioManager::get_instance().cache_audio(path, hash);

            audio_hashes.emplace(filename, hash);
        }
    }

    engine::audio::AudioManager::get_instance().write_cache();

    return audio_hashes;
}

// TODO: Handle beatmap file
void Importer::handle_beatmap_files(const std::vector<std::string> &paths, const std::unordered_map<std::string, std::string> &audio_hashes) {
    for (const std::string &path : paths) {
        const std::string &extension = FileUtility::get_extension(path);

        if (extension == ".osu") {
            Beatmap beatmap = Converter::convert(path);
        }
    }
}

} // namespace game::parser
