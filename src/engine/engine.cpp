#include "external/imgui/imgui.h"

#include "engine/engine.hpp"

#include "engine/sound/sound_clock.hpp"
#include "engine/sound/sound_manager.hpp"

#include "engine/graphic/shader/shader_manager.hpp"
#include "engine/graphic/texture/texture_manager.hpp"
#include "engine/graphic/effect/effect_manager.hpp"

#include "game/gameplay/effects/lighting_effect.hpp"
#include "game/gameplay/effects/note_effect.hpp"
#include "game/gameplay/stage/stage.hpp"
#include "game/gameplay/stage/drawable/drawable_note.hpp"

#include "game/parser/converter.hpp"

#include "game/scenes/menu.hpp"
#include "game/skinning/skin_manager.hpp"

#include "game/ui/theme/theme_config.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine::sound;
using namespace engine::sound::enums;

using namespace engine::graphic::effect;
using namespace engine::graphic::shader;
using namespace engine::graphic::texture;

using namespace game::gameplay::effects;
using namespace game::gameplay::stage;
using namespace game::gameplay::stage::drawable;

using namespace game::parser;
using namespace game::parser::components;

using namespace game::skinning;

using namespace game::scenes;

using namespace game::ui::theme;

namespace engine {

Engine::Engine() : m_time(0.0) {
}

// NOTE: Suppose beatmap initialisation is done here for now, since we don't have ui yet lol, also
// sound clock should be the one playing the music, music sync is probably the most important part
void Engine::initialise() {
    // TODO: Effects should be loaded if custom defined
    EffectManager::get_instance().add_effect("gameplay.lighting", std::make_shared<LightingEffect>(ShaderManager::get_instance().get_shader_id("base")));
    EffectManager::get_instance().add_effect("gameplay.note", std::make_shared<NoteEffect>(ShaderManager::get_instance().get_shader_id("base")));

    SoundManager &sound_manager = SoundManager::get_instance();

    Source *source = sound_manager.get_empty_source();

    if (source == nullptr) {
        LOG_ERROR("No sound sources found");
        return;
    }

    ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2099753/4404686/bgm.mp3");
    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2321277/4973089/bgm.mp3");
    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2383964/5154675/bgm.mp3");
    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2325151/4983858/bgm.mp3");

    m_sound_clock.emplace(*source, id);

    m_beatmap = Converter::convert("resources/beatmaps/2099753/4404686/beatmap.osu");
    // m_beatmap = Converter::convert("resources/beatmaps/2321277/4973089/beatmap.osu");
    // m_beatmap = Converter::convert("resources/beatmaps/2383964/5154675/beatmap.osu");
    // m_beatmap = Converter::convert("resources/beatmaps/2325151/4983858/beatmap.osu");

    std::sort(m_beatmap.hit_objects.begin(), m_beatmap.hit_objects.end(), [](const auto &a, const auto &b) {
        return a.start_time < b.start_time;
    });

    SkinManager &skin_manager = SkinManager::get_instance();

    // NOTE: Load skin textures and skin config for the current beatmap
    skin_manager.load_textures();

    m_skin_config = skin_manager.load_skin_config(m_beatmap);

    m_stage.emplace(m_skin_config, m_beatmap);

    if (m_sound_clock.has_value()) {
        m_sound_clock->start();
    }

    TextureManager::get_instance().load_texture("resources/core/textures/colours/white.png");

    TextureManager::get_instance().upload();
    ThemeConfig theme_config = ThemeConfig::load();
    m_scene = std::make_unique<Menu>(theme_config);
}

void Engine::update(GLFWwindow *window, double delta_time) {
    m_scene->submit(m_renderer);
    // SoundManager &sound_manager = SoundManager::get_instance();
    //
    // m_time += delta_time;
    //
    // if (m_sound_clock.has_value()) {
    //     m_sound_clock->update(delta_time);
    // }
    //
    // double track_time = m_sound_clock->track_time();
    //
    // m_stage->update(track_time, delta_time);
    //
    // for (Lane &lane : m_stage->lanes()) {
    //     for (const DrawableNote *note : lane.active_notes()) {
    //         note->submit(m_renderer);
    //     }
    // }
    //
    // m_stage->judge().submit(m_renderer);
    //
    // for (Lane &lane : m_stage->lanes()) {
    //     lane.lighting_hold().submit(m_renderer);
    // }
}

/* TODO: Allow for custom GL flags */
void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderer.render();

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

} // namespace engine
