#include "game/importer/importer.hpp"

#include "core/exceptions/runtime_exception.hpp"
#include "core/platform/environment.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/hash_utility.hpp"
#include "core/utility/string_utility.hpp"
#include "game/importer/beatmap.hpp"
#include "game/importer/converter.hpp"

#include <zip.h>
#include <zipconf.h>

#include <fstream>

namespace game::importer {

namespace utility = core::utility;
namespace platform = core::platform;
namespace exceptions = core::exceptions;

Importer::Importer() {
}

void Importer::import(const std::vector<std::filesystem::path> &paths) {
    for (const std::filesystem::path &path : paths) {
        const std::string extension = utility::FileUtility::extension(path);

        if (extension != ".osz") {
            continue;
        }

        const std::vector<std::filesystem::path> &extracted_paths = extract(path);

        std::unordered_map<std::string, std::string> audio_hashes = handle_audio_files(extracted_paths);
        handle_beatmap_files(extracted_paths, audio_hashes);

        // we only need to temporarily parse the beatmap to get the metadata
    }
    // if extracted successfully, we can safely delete the .osz file and clear the tmp directory
}

std::vector<std::filesystem::path> Importer::extract(const std::filesystem::path &path) {
    const std::filesystem::path tmp_path = core::platform::tmp_path();

    int error = 0;
    const std::string path_string = path.string();
    zip *archive = zip_open(path_string.c_str(), 0, &error);

    if (!archive) {
        throw exceptions::RuntimeException("Failed to extract '{}'. Error code: {}", path.string(), error);
    }

    zip_int64_t file_count = zip_get_num_entries(archive, 0);
    std::vector<std::filesystem::path> output_paths;

    for (zip_int64_t i = 0; i < file_count; ++i) {
        struct zip_stat file_stat;

        zip_stat_init(&file_stat);

        if (zip_stat_index(archive, i, 0, &file_stat) != 0) {
            continue;
        }

        zip_file *zip = zip_fopen_index(archive, i, 0);

        if (!zip) {
            throw exceptions::RuntimeException("Failed to open zip file: {}", file_stat.name);
        }

        std::filesystem::path output_path = tmp_path / file_stat.name;
        utility::FileUtility::create_directory(output_path.parent_path());
        std::ofstream output_file(output_path, std::ios::binary);

        if (!output_file.is_open()) {
            zip_fclose(zip);
            throw exceptions::RuntimeException("Failed to create output file: {}", output_path.string());
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

std::unordered_map<std::string, std::string> Importer::handle_audio_files(const std::vector<std::filesystem::path> &paths) {
    std::unordered_map<std::string, std::string> audio_hashes;

    // get hash: basename, hash
    for (const std::filesystem::path &path : paths) {
        const std::string extension = utility::FileUtility::extension(path);

        if (extension == ".mp3") {
            const std::string hash = utility::HashUtility::hash_file(path);
            const std::string shard = utility::StringUtility::slice(hash, 0, 1);
            const std::string filename = utility::FileUtility::filename(path);

            // NOTE: app_data/objects/shard/hash.ext
            std::filesystem::path hash_path = platform::objects_path() / shard / (hash + extension);

            utility::FileUtility::create_directory(hash_path.parent_path());
            utility::FileUtility::move(path, hash_path);

            audio_hashes.emplace(filename, hash);
        }
    }

    return audio_hashes;
}

// TODO: Handle beatmap file
void Importer::handle_beatmap_files(const std::vector<std::filesystem::path> &paths, const std::unordered_map<std::string, std::string> &audio_hashes) {
    for (const std::filesystem::path &path : paths) {
        const std::string extension = utility::FileUtility::extension(path);

        if (extension == ".osu") {
            Beatmap beatmap = Converter::convert(path);
        }
    }
}

} // namespace game::importer
