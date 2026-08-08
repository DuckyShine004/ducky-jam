#include "database/repositories/beatmap_repository.hpp"

namespace database::repositories {

BeatmapRepository::BeatmapRepository(Storage &storage) : m_storage(storage) {
}

int BeatmapRepository::create(const models::BeatmapModel &beatmap) {
    return m_storage.insert(beatmap);
}

models::BeatmapSetModel BeatmapRepository::get_set(int id) {
    return m_storage.get<models::BeatmapSetModel>(id);
}

int BeatmapRepository::create_set(const models::BeatmapSetModel &beatmap_set) {
    return m_storage.insert(beatmap_set);
}

void BeatmapRepository::update_set(models::BeatmapSetModel &beatmap_set) {
    m_storage.update(beatmap_set);
}

} // namespace database::repositories
