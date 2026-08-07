#include "game/game.hpp"

#include "game/scenes/menu.hpp"
#include "game/ui/theme/theme_config.hpp"

#include "external/imgui/imgui.h"

namespace game {

Game::Game(engine::EngineServices engine_services) : m_services(engine_services), m_skin_manager(m_services.texture_manager) {
    ui::theme::ThemeConfig theme_config = ui::theme::ThemeConfig::load();

    m_scene_manager.add_scene("menu", std::make_unique<scenes::Menu>(theme_config));

    m_scene_manager.load_scene("menu");
}

void Game::load() {
    // m_services.effect_manager.add_effect();
}

void Game::import(const std::vector<std::filesystem::path> &paths) {
    m_importer.import(paths);
}

void Game::update(double delta_time) {
    engine::scene::Scene *scene = m_scene_manager.scene();

    // scene->update_by_audio(m_audio_clock->audio_buffer(), track_time);
    scene->update(delta_time);

    scene->submit(m_services.renderer);
}

void Game::render() {
    m_services.renderer.render();
}

void Game::render_imgui() {
    ImGui::SetNextWindowSize(ImVec2(400.0f, 0.0f), ImGuiCond_FirstUseEver);

    ImGui::Begin("Debug");

    if (ImGui::CollapsingHeader("Engine", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginTable("engine_table", 2, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_BordersInnerV)) {
            ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("Control", ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted("FPS");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%.1f FPS (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

            ImGui::EndTable();
        }
    }

    ImGui::End();
}

} // namespace game
