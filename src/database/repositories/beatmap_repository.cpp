#include "database/repositories/beatmap_repository.hpp"

namespace database::repositories {

BeatmapRepository::BeatmapRepository(Storage &storage) : m_storage(storage) {
}

void BeatmapRepository::create(models::BeatmapModel &beatmap) {
}

void BeatmapRepository::create_set(models::BeatmapSetModel &beatmap_set) {
}

} // namespace database::repositories
