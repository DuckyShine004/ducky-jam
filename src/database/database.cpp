#include "database/database.hpp"

using namespace database::repositories;

namespace database {

Database::Database(const std::string &path) : m_storage(initialise_database(path)), m_beatmap_repository(m_storage) {
    m_storage.pragma.journal_mode(sqlite_orm::journal_mode::WAL);
    m_storage.sync_schema(true);
}

BeatmapRepository &Database::beatmap_repository() {
    return m_beatmap_repository;
}

} // namespace database
