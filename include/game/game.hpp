#pragma once

#include "database/database.hpp"
#include "engine/engine.hpp"
#include "engine/scene/scene_manager.hpp"
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

    /**
     * @brief Resizes components which rely on actual pixel coords.
     *
     * @param width the new framebuffer width.
     * @param height the new framebuffer height.
     */
    void resize(int width, int height);

    void import(const std::vector<std::filesystem::path> &paths);

    void update(double delta_time);
    void render();

    void render_imgui();

  private:
    engine::EngineServices m_services;

    engine::scene::SceneManager m_scene_manager;

    database::Database m_database;
    game::importer::Importer m_importer;
    game::skinning::SkinManager m_skin_manager;
};

} // namespace game
