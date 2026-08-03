#include "engine/graphics/drawable/sprite.hpp"

#include "engine/graphics/texture/region.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include "game/gameplay/stage/stage.hpp"
#include "game/gameplay/stage/note.hpp"
#include "game/gameplay/stage/drawable/drawable_hold_note.hpp"
#include "game/gameplay/stage/drawable/drawable_normal_note.hpp"

#include "game/parser/components/hit_object.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine::graphics::texture;
using namespace engine::graphics::drawable;

using namespace game::skinning::config;

using namespace game::parser;
using namespace game::parser::components;

using namespace game::gameplay::stage::drawable;

using namespace core::logger;

namespace game::gameplay::stage {

Stage::Stage(const SkinConfig &skin_config, const Beatmap &beatmap) : m_judge(create_judge(skin_config, beatmap)) {

    for (int i = 0; i < beatmap.circle_size; ++i) {
        Lane &lane = m_lanes.emplace_back(skin_config.lighting_frame_rate);

        double note_width = static_cast<double>(skin_config.notes[i].width);
        // double width = static_cast<double>(skin_config.notes[i].width);
        double width = 200.0f;
        double height = 200.0f;

        double x = note_width * i;
        double y = skin_config.lighting_position;

        double offset_x = 0.5f * (note_width - width);
        // double offset_y = -0.5f * height;
        double offset_y = 0.0f;

        for (const std::string &texture_path : skin_config.lighting_hold) {
            Sprite lighting(x, y, width, height, texture_path, "gameplay.lighting");

            lighting.set_offset_x(offset_x);

            lane.lighting_hold().add_frame(lighting);
        }

        for (const std::string &texture_path : skin_config.lighting_normal) {
            Sprite lighting(x, y, width, height, texture_path, "gameplay.lighting");

            lighting.set_offset_x(offset_x);

            lane.lighting_normal().add_frame(lighting);
        }

        // TEMP: Continuously loop the hold lighting in every lane.
        lane.lighting_hold().play();
        lane.lighting_normal().play();
    }

    double head_height = static_cast<double>(skin_config.height);

    // NOTE: These should be called in user config (also 1440 is playfield height)
    double approach_time = 400.0f;
    double approach_rate = (1440.0f / approach_time) / 0.75f;

    for (const HitObject &hit_object : beatmap.hit_objects) {
        int lane = hit_object.lane;

        double width = static_cast<double>(skin_config.notes[lane].width);

        double start_time = static_cast<double>(hit_object.start_time);
        double end_time = static_cast<double>(hit_object.end_time);

        double x = width * lane;
        double y = approach_rate * start_time;

        Sprite head(x, y, width, head_height, skin_config.notes[lane].head, "gameplay.note");

        if (hit_object.hold_time > 0) {
            const Region &tail_region = TextureManager::get_instance().get_texture(skin_config.notes[lane].tail).get_region(skin_config.notes[lane].tail);

            double end_y = approach_rate * end_time;
            double hold_height = approach_rate * (end_time - start_time);

            double body_y = y + head_height;
            double available_height = end_y - body_y;

            double tail_texture_height = width * static_cast<double>(tail_region.source_height) / static_cast<double>(tail_region.source_width);
            double tail_height = std::min(tail_texture_height, available_height);

            double tail_y = end_y - tail_height;
            double body_height = tail_y - body_y;

            /* NOTE: Use this UV to ensure that the tail texture is rendered correctly, or use some advanced texture chunking algo */
            UV tail_uv{
                .u0 = 0.0f,
                .u1 = 1.0f,
                .v0 = 1.0f - static_cast<float>(tail_height / tail_texture_height),
                .v1 = 1.0f,
            };

            Note note{
                .x = x,
                .y = y,
                .width = width,
                .height = hold_height,
                .start_time = start_time,
                .end_time = end_time,
            };

            Sprite body(x, body_y, width, body_height, skin_config.notes[lane].body, "gameplay.note");
            Sprite tail(x, tail_y, width, tail_height, tail_uv, skin_config.notes[lane].tail, "gameplay.note");

            m_lanes[lane].add_note(std::make_unique<DrawableHoldNote>(note, head, body, tail));
        } else {
            Note note{
                .x = x,
                .y = y,
                .width = width,
                .height = head_height,
                .start_time = start_time,
                .end_time = end_time,
            };

            m_lanes[lane].add_note(std::make_unique<DrawableNormalNote>(note, head));
        }
    }
}

void Stage::update(double track_time, double delta_time) {
    for (Lane &lane : m_lanes) {
        lane.update(track_time, delta_time);
    }
}

std::vector<Lane> &Stage::lanes() {
    return m_lanes;
}

Sprite Stage::create_judge(const SkinConfig &skin_config, const Beatmap &beatmap) {
    double total_width = 0.0f;
    for (int i = 0; i < beatmap.circle_size; ++i) {
        total_width += skin_config.notes[i].width;
    }

    Sprite judge(0, skin_config.hit_position + 0.5f * 100.0f, total_width, 100.0f, skin_config.judge, "gameplay.note");

    return judge;
}

const Sprite &Stage::judge() const {
    return m_judge;
}

} // namespace game::gameplay::stage
