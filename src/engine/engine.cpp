#include "game/parser/converter.hpp"
#include "game/parser/components/hit_object.hpp"

#include "game/skinning/skin_manager.hpp"

#include "engine/engine.hpp"

#include "engine/graphic/model/sprite.hpp"
#include "engine/graphic/shader/shader.hpp"
#include "engine/graphic/shader/shader_manager.hpp"
#include "engine/graphic/texture/texture_manager.hpp"

#include "engine/sound/sound_clock.hpp"
#include "engine/sound/sound_manager.hpp"

#include "core/logger/logger_macros.hpp"

using namespace game::parser;
using namespace game::parser::components;

using namespace game::skinning;

using namespace engine::sound;
using namespace engine::sound::enums;

using namespace engine::graphic::shader;
using namespace engine::graphic::model;
using namespace engine::graphic::model::enums;
using namespace engine::graphic::texture;

namespace engine {

Engine::Engine() : m_time(0.0) {
}

// NOTE: Suppose beatmap initialisation is done here for now, since we don't have ui yet lol, also
// sound clock should be the one playing the music, music sync is probably the most important part
void Engine::initialise() {
    SoundManager &sound_manager = SoundManager::get_instance();

    Source *source = sound_manager.get_empty_source();

    if (source == nullptr) {
        LOG_ERROR("No sound sources found");
        return;
    }

    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2099753/4404686/bgm.mp3");
    ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2321277/4973089/bgm.mp3");
    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2325151/4983858/bgm.mp3");

    m_sound_clock.emplace(*source, id);

    // m_beatmap = Converter::convert("resources/beatmaps/2099753/4404686/beatmap.osu");
    m_beatmap = Converter::convert("resources/beatmaps/2321277/4973089/beatmap.osu");
    // m_beatmap = Converter::convert("resources/beatmaps/2325151/4983858/beatmap.osu");

    std::sort(m_beatmap.hit_objects.begin(), m_beatmap.hit_objects.end(), [](const auto &a, const auto &b) {
        return a.start_time < b.start_time;
    });

    SkinManager &skin_manager = SkinManager::get_instance();

    // NOTE: Load skin textures and skin config for the current beatmap
    skin_manager.load_textures();

    m_skin_config = skin_manager.load_skin_config(m_beatmap);

    if (m_sound_clock.has_value()) {
        m_sound_clock->start();
    }
}

// PERF: optimise check for in-range notes CPU speed up
void Engine::update(GLFWwindow *window, double delta_time) {
    SoundManager &sound_manager = SoundManager::get_instance();

    m_time += delta_time;

    // sync audio
    if (m_sound_clock.has_value()) {
        m_sound_clock->update(delta_time);
    }

    double current_time = m_sound_clock->get_current_time();

    // just do a brute force for now
    int index_offset = 0;
    double scroll_speed = 6.0f;
    double rate = 0.75f;
    double width = 150.0f;
    double height = 80.0f;
    double approach_time = 400.0f;
    // double approach_rate = 0.5*scroll_speed*rate;
    double approach_rate = 1440.0f / approach_time;

    TextureManager &texture_manager = TextureManager::get_instance();
    for (HitObject hit_object : m_beatmap.hit_objects) {
        int lane = hit_object.lane;
        double start_time = static_cast<double>(hit_object.start_time);
        double end_time = static_cast<double>(hit_object.end_time);

        double x0 = hit_object.lane * width;
        double x1 = x0 + width;

        double y0 = approach_rate * (start_time - current_time);
        double y1 = y0 + height;

        if (hit_object.hold_time > 0) {
            y1 = approach_rate * (end_time - current_time);
        }

        if (y1 < 0.0 || y0 > 1440.0) {
            continue;
        }

        m_renderer.queue(Sprite(x0, y0, width, height, m_skin_config.notes[lane].head));

        if (hit_object.hold_time > 0 && y0 + height < y1) {
            const Region &tail_region = TextureManager::get_instance().get_texture(m_skin_config.notes[lane].tail).get_region(m_skin_config.notes[lane].tail);

            double body_y = y0 + height;

            double natural_height = width * static_cast<double>(tail_region.source_height) / static_cast<double>(tail_region.source_width);
            double available_height = y1 - body_y;
            double visible_height = std::min(available_height, natural_height);

            double visible_fraction = visible_height / natural_height;

            UV local_uv{
                .u0 = 0.0f,
                .u1 = 1.0f,
                .v0 = 1.0f - static_cast<float>(visible_fraction),
                .v1 = 1.0f,
            };

            double tail_y = y1 - visible_height;
            double body_height = tail_y - body_y;

            m_renderer.queue(Sprite(x0, body_y, width, body_height, m_skin_config.notes[lane].body));
            m_renderer.queue(Sprite(x0, tail_y, width, visible_height, local_uv, m_skin_config.notes[lane].tail));
        }
    }

    // LOG_INFO("Current track time: {}", m_sound_clock->get_current_time());
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_renderer.render();
}

} // namespace engine
