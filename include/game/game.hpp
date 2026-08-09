#pragma once

#include "database/database.hpp"
#include "engine/engine.hpp"
#include "engine/scene/scene_manager.hpp"
#include "game/audio/music_player.hpp"
#include "game/importer/importer.hpp"
#include "game/skinning/skin_manager.hpp"

namespace game {

class Game {
  public:
    Game(engine::EngineServices engine_services);

    void load();

    /**
     * @brief Resizes the UI based on logical width and height (screen coords).
     *
     * @param width the new logical width.
     * @param height the new logical height.
     */
    void resize_ui(int width, int height);

    void import(const std::vector<std::filesystem::path> &paths);

    void update(double delta_time);
    void render();

    void render_imgui();

  private:
    // likewise with engine services, we should make resource pool
    engine::EngineServices m_services;

    engine::scene::SceneManager m_scene_manager;

    database::Database m_database;
    game::importer::Importer m_importer;
    game::skinning::SkinManager m_skin_manager;
    game::audio::MusicPlayer m_music_player;
};

} // namespace game
