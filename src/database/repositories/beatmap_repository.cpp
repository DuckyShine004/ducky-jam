#include "database/repositories/beatmap_repository.hpp"

using namespace database::models;

namespace database::repositories {

BeatmapRepository::BeatmapRepository(Storage &storage) : m_storage(storage) {
}

void BeatmapRepository::create(BeatmapModel &beatmap) {
}

void BeatmapRepository::create_set(BeatmapSetModel &beatmap_set) {
}

} // namespace database::repositories
