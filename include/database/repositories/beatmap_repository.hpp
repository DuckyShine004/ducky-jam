#pragma once

#include "database/models/beatmap_model.hpp"
#include "database/models/beatmap_set_model.hpp"
#include "database/storage.hpp"

namespace database::repositories {

class BeatmapRepository {
  public:
    BeatmapRepository(database::Storage &storage);

    int create(const database::models::BeatmapModel &beatmap);

    database::models::BeatmapSetModel get_set(int id);
    int create_set(const database::models::BeatmapSetModel &beatmap_set);
    void update_set(database::models::BeatmapSetModel &beatmap_set);

  private:
    database::Storage &m_storage;
};

} // namespace database::repositories
