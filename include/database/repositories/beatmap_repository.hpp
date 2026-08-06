#pragma once

#include "database/storage.hpp"

#include "database/models/beatmap_model.hpp"
#include "database/models/beatmap_set_model.hpp"

namespace database::repositories {

class BeatmapRepository {
  public:
    BeatmapRepository(database::Storage &storage);

    void create(database::models::BeatmapModel &beatmap);
    void create_set(database::models::BeatmapSetModel &beatmap_set);

  private:
    database::Storage &m_storage;
};

} // namespace database::repositories
