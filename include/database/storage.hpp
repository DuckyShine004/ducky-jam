#pragma once

#include "database/models/beatmap_model.hpp"
#include "database/models/beatmap_set_model.hpp"

#include <sqlite_orm/sqlite_orm.h>

#include <filesystem>

namespace database {

inline auto initialise_database(const std::filesystem::path &path) {
    if (const std::filesystem::path parent = path.parent_path(); !parent.empty()) {
        std::filesystem::create_directories(parent);
    }

    return sqlite_orm::make_storage(path.string(),
                                    sqlite_orm::make_table("beatmap_sets",
                                                           sqlite_orm::make_column("id", &database::models::BeatmapSetModel::id, sqlite_orm::primary_key().autoincrement()),
                                                           sqlite_orm::make_column("title", &database::models::BeatmapSetModel::title),
                                                           sqlite_orm::make_column("title_unicode", &database::models::BeatmapSetModel::title_unicode),
                                                           sqlite_orm::make_column("artist", &database::models::BeatmapSetModel::artist),
                                                           sqlite_orm::make_column("artist_unicode", &database::models::BeatmapSetModel::artist_unicode),
                                                           sqlite_orm::make_column("creator", &database::models::BeatmapSetModel::creator),
                                                           sqlite_orm::make_column("source", &database::models::BeatmapSetModel::source),
                                                           sqlite_orm::make_column("tags", &database::models::BeatmapSetModel::tags),
                                                           sqlite_orm::make_column("date_added", &database::models::BeatmapSetModel::date_added)),

                                    sqlite_orm::make_table("beatmaps",
                                                           sqlite_orm::make_column("id", &database::models::BeatmapModel::id, sqlite_orm::primary_key().autoincrement()),
                                                           sqlite_orm::make_column("set_id", &database::models::BeatmapModel::set_id),
                                                           sqlite_orm::make_column("version", &database::models::BeatmapModel::version),
                                                           sqlite_orm::make_column("key_count", &database::models::BeatmapModel::key_count),
                                                           sqlite_orm::make_column("health_drain_rate", &database::models::BeatmapModel::health_drain_rate),
                                                           sqlite_orm::make_column("overall_difficulty", &database::models::BeatmapModel::overall_difficulty),
                                                           sqlite_orm::make_column("normal_notes", &database::models::BeatmapModel::normal_notes),
                                                           sqlite_orm::make_column("hold_notes", &database::models::BeatmapModel::hold_notes),
                                                           sqlite_orm::make_column("audio_hash", &database::models::BeatmapModel::audio_hash),
                                                           sqlite_orm::make_column("background_hash", &database::models::BeatmapModel::background_hash),
                                                           sqlite_orm::foreign_key(&database::models::BeatmapModel::set_id).references(&database::models::BeatmapSetModel::id).on_delete.cascade()));
}

using Storage = decltype(initialise_database(std::filesystem::path{}));

} // namespace database
