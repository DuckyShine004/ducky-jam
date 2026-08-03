#pragma once

#include "game/gameplay/stage/lane.hpp"

#include "game/skinning/config/skin_config.hpp"

#include "game/parser/beatmap.hpp"

namespace game::gameplay::stage {

class Stage {
  public:
    Stage(const game::skinning::config::SkinConfig &skin_config, const game::parser::Beatmap &beatmap);

    void update(double track_time, double delta_time);

    std::vector<Lane> &lanes();
    const engine::graphics::drawable::Sprite &judge() const;

  private:
    static engine::graphics::drawable::Sprite create_judge(const game::skinning::config::SkinConfig &skin_config, const game::parser::Beatmap &beatmap);

    std::vector<Lane> m_lanes;

    engine::graphics::drawable::Sprite m_judge;
};

} // namespace game::gameplay::stage
