#include "database/database.hpp"

namespace database {

Database::Database(const std::filesystem::path &path) : m_storage(initialise_database(path)), m_beatmap_repository(m_storage), m_resource_repository(m_storage) {
    m_storage.pragma.journal_mode(sqlite_orm::journal_mode::WAL);
    m_storage.sync_schema(true);
}

repositories::BeatmapRepository &Database::beatmap_repository() {
    return m_beatmap_repository;
}

repositories::ResourceRepository &Database::resource_repository() {
    return m_resource_repository;
}

} // namespace database
