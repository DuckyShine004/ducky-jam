#pragma once

#include "core/platform/environment.hpp"
#include "database/repositories/beatmap_repository.hpp"
#include "database/storage.hpp"

#include <filesystem>

// Number of repositories should be relatively small, so we can just define it all here without extra dependencies
namespace database {

class Database {
  public:
    explicit Database(const std::filesystem::path &path = database_path);

    database::repositories::BeatmapRepository &beatmap_repository();

  private:
    static inline constexpr const char *database_name = "application.db";

    static inline const std::filesystem::path database_path = core::platform::app_data_path() / database_name;

    database::Storage m_storage;

    database::repositories::BeatmapRepository m_beatmap_repository;
};

} // namespace database
