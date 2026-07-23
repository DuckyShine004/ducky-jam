#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "engine/sound/source.hpp"
#include "engine/sound/buffer.hpp"
#include "engine/sound/enums/sound_type.hpp"

namespace engine::sound {

class SoundManager {
  public:
    SoundManager(const SoundManager &) = delete;
    SoundManager &operator=(const SoundManager &) = delete;

    static SoundManager &get_instance();

    void initialise();
    ALuint add_sound(const engine::sound::enums::SoundType &sound_type, const std::string &path);
    void play(const engine::sound::enums::SoundType &sound_type, const std::string &name);
    engine::sound::Source *get_empty_source();

  private:
    SoundManager();
    ~SoundManager();

    void initialise_music();

    static inline constexpr int m_MAX_SOURCES = 128;

    ALCdevice *m_device;
    ALCcontext *m_context;

    std::unordered_map<engine::sound::enums::SoundType, std::unordered_map<std::string, engine::sound::Buffer>> m_sounds;
    std::vector<engine::sound::Source> m_sources;
};

} // namespace engine::sound
