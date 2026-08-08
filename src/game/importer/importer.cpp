#include "game/importer/importer.hpp"

#include "core/exceptions/runtime_exception.hpp"
#include "core/logger/logger_macros.hpp"
#include "core/platform/environment.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/hash_utility.hpp"
#include "core/utility/string_utility.hpp"
#include "database/models/beatmap_set_model.hpp"
#include "database/repositories/beatmap_repository.hpp"
#include "game/importer/beatmap.hpp"
#include "game/importer/converter.hpp"

#include <zip.h>
#include <zipconf.h>

#include <algorithm>
#include <filesystem>
#include <fstream>

namespace game::importer {

namespace utility = core::utility;
namespace platform = core::platform;
namespace exceptions = core::exceptions;

Importer::Importer(database::repositories::BeatmapRepository &beatmap_repository) : m_beatmap_repository(beatmap_repository), m_image_extensions(std::begin(image_extensions), std::end(image_extensions)), m_valid_extensions(std::begin(valid_extensions), std::end(valid_extensions)) {
}

void Importer::import(const std::vector<std::filesystem::path> &paths) {
    for (const std::filesystem::path &path : paths) {
        const std::string extension = utility::FileUtility::extension(path);

        if (extension != ".osz") {
            LOG_WARN("Unhandled file type '{}', skipping import...", extension);
            continue;
        }

        const std::vector<std::filesystem::path> &extracted_paths = extract(path);

        std::unordered_map<std::string, std::string> audio_hashes;
        std::unordered_map<std::string, std::string> image_hashes;

        int beatmap_set_id = m_beatmap_repository.create_set({});

        database::models::BeatmapSetModel beatmap_set_model = m_beatmap_repository.get_set(beatmap_set_id);

        bool beatmap_set_initialised = false;

        for (const std::filesystem::path &extracted_path : extracted_paths) {
            const std::string extracted_file_extension = utility::FileUtility::extension(extracted_path);

            if (!m_valid_extensions.contains(extracted_file_extension)) {
                LOG_WARN("Unhandled file type: {}, skipping zip extraction...", extracted_file_extension);
                continue;
            }

            const std::string hash = utility::HashUtility::hash_file(extracted_path);
            const std::string shard = utility::StringUtility::slice(hash, 0, 1);
            const std::string filename = utility::FileUtility::filename(extracted_path);
            const std::string basename = utility::FileUtility::basename(extracted_path);

            if (extracted_file_extension == ".mp3") {
                audio_hashes.emplace(filename, hash);
            } else if (m_image_extensions.contains(extracted_file_extension)) {
                image_hashes.emplace(filename, hash);
            } else if (extracted_file_extension == ".osu") {
                Beatmap beatmap = Converter::convert(extracted_path);

                if (!beatmap_set_initialised) {
                    beatmap_set_model.title = beatmap.title;
                    beatmap_set_model.title_unicode = beatmap.title_unicode;
                    beatmap_set_model.artist = beatmap.artist;
                    beatmap_set_model.artist_unicode = beatmap.artist_unicode;
                    beatmap_set_model.creator = beatmap.creator;
                    beatmap_set_model.source = beatmap.source;
                    beatmap_set_model.tags = beatmap.tags;

                    beatmap_set_initialised = true;
                }

                // TODO: remember to parse normal and hold notes
                m_beatmap_repository.create({
                    .set_id = beatmap_set_id,
                    .audio_title = basename,
                    .version = beatmap.version,
                    .key_count = static_cast<int>(beatmap.circle_size),
                    .health_drain_rate = beatmap.health_drain_rate,
                    .overall_difficulty = beatmap.overall_difficulty,
                    .hash = hash,
                    .audio_hash = audio_hashes[beatmap.audio_filename],
                    .background_hash = image_hashes[beatmap.background_filename],
                });
            }

            m_beatmap_repository.update_set(beatmap_set_model);

            std::filesystem::path hash_path = platform::objects_path() / shard / (hash + extracted_file_extension);

            utility::FileUtility::create_directory(hash_path.parent_path());

            try {
                utility::FileUtility::move(extracted_path, hash_path);
            } catch (std::filesystem::filesystem_error &error) {
                LOG_ERROR("Cannot move file. Reason: {}", error.what());
            }

            LOG_DEBUG("Successfully moved file from '{}' to '{}'", extracted_path.string(), hash_path.string());
        }

        utility::FileUtility::clear(core::platform::tmp_path());
    }
    // TODO: (Fine to not remove if DEV), if extracted successfully, we can safely delete the .osz file and clear the tmp directory
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

    // NOTE: we can either do two-pass or partition the output paths based on extension - .osu last
    std::partition(output_paths.begin(), output_paths.end(), [](const std::filesystem::path &output_path) {
        const std::string &extension = utility::FileUtility::extension(output_path);

        return extension != ".osu";
    });

    return output_paths;
}

} // namespace game::importer
