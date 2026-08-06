#pragma once

#include "database/storage.hpp"

#include "database/repositories/beatmap_repository.hpp"

// Number of repositories should be relatively small, so we can just define it all here without extra dependencies
namespace database {

class Database {
  public:
    Database(const std::string &path = m_DEVELOPMENT_DATA_PATH);

    database::repositories::BeatmapRepository &beatmap_repository();

  private:
    static inline constexpr const char *m_DEVELOPMENT_DATA_PATH = ".data/library.db";

    database::Storage m_storage;

    database::repositories::BeatmapRepository m_beatmap_repository;
};

} // namespace database
