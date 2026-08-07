#pragma once

#include "game/gameplay/stage/lane.hpp"

#include "game/skinning/config/skin_config.hpp"

#include "game/importer/beatmap.hpp"

#include "engine/graphics/effect/effect_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

namespace game::gameplay::stage {

class Stage {
  public:
    Stage(const game::skinning::config::SkinConfig &skin_config,
          const game::importer::Beatmap &beatmap,
          engine::graphics::texture::TextureManager &texture_manager,
          engine::graphics::effect::EffectManager &effect_manager);

    void update(double track_time, double delta_time);

    std::vector<Lane> &lanes();
    const engine::graphics::drawable::Sprite &judge() const;

  private:
    static engine::graphics::drawable::Sprite create_judge(const game::skinning::config::SkinConfig &skin_config,
                                                            const game::importer::Beatmap &beatmap,
                                                            engine::graphics::effect::EffectPtr effect);

    std::vector<Lane> m_lanes;

    engine::graphics::drawable::Sprite m_judge;
};

} // namespace game::gameplay::stage
