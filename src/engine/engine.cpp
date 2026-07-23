
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
    // ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2321277/4973089/bgm.mp3");
    ALuint id = sound_manager.add_sound(SoundType::Music, "resources/beatmaps/2325151/4983858/bgm.mp3");

    m_sound_clock.emplace(*source, id);

    // m_beatmap = Converter::convert("resources/beatmaps/2099753/4404686/beatmap.osu");
    // m_beatmap = Converter::convert("resources/beatmaps/2321277/4973089/beatmap.osu");
    m_beatmap = Converter::convert("resources/beatmaps/2325151/4983858/beatmap.osu");

    std::sort(m_beatmap.hit_objects.begin(), m_beatmap.hit_objects.end(), [](const auto &a, const auto &b) {
        return a.start_time < b.start_time;
    });

    SkinManager &skin_manager = SkinManager::get_instance();

    // NOTE: Load skin textures and skin config for the current beatmap
    skin_manager.load_textures();
    m_skin_config = skin_manager.load_skin_config(m_beatmap);

    if (!m_skin_config.notes.empty()) {
        TextureManager &texture_manager = TextureManager::get_instance();
        const std::string &head_path = m_skin_config.notes.front().head;
        m_note_head_texture_id = texture_manager.get_texture(head_path).texture_id();
    }

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
    double scroll_speed = 4.0;
    double rate = 0.75f;
    double width = 100.0f;
    double height = 40.0f;

    TextureManager &texture_manager = TextureManager::get_instance();
    for (HitObject hit_object : m_beatmap.hit_objects) {
        int lane = hit_object.lane;
        double start_time = static_cast<double>(hit_object.start_time);
        double end_time = static_cast<double>(hit_object.end_time);

        double x0 = hit_object.lane * width;
        double x1 = x0 + width;

        double y0 = 0.5 * (start_time - current_time) * scroll_speed * rate;
        double y1 = y0 + height;

        if (hit_object.hold_time > 0) {
            y1 = 0.5 * (end_time - current_time) * scroll_speed * rate;
        }

        if (y1 < 0.0 || y0 > 1440.0) {
            continue;
        }

        const std::string &head_path = m_skin_config.notes[lane].head;

        m_renderer.queue(Sprite(x0, y0, x1 - x0, y1 - y0, m_skin_config.notes[lane].head));
    }

    // LOG_INFO("Current track time: {}", m_sound_clock->get_current_time());
}

void Engine::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_renderer.render();

    // ShaderManager &shader_manager = ShaderManager::get_instance();
    // Shader &shader = shader_manager.get_shader("hit_object");
    //
    // glm::mat4 model = glm::mat4(1.0f);
    // glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // shader.use();
    // shader.set_matrix4fv("u_model", model);
    // shader.set_matrix4fv("u_projection", projection);
    // shader.set_integer("u_texture", 0);
    //
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, m_note_head_texture_id);
    //
    // m_mesh.render(TopologyType::Triangle);
}

} // namespace engine
