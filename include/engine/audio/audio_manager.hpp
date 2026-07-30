#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <sndfile.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "engine/audio/audio_source.hpp"
#include "engine/audio/audio_buffer.hpp"
#include "engine/audio/enums/audio_type.hpp"

namespace engine::audio {

class AudioManager {
  public:
    AudioManager(const AudioManager &) = delete;
    AudioManager &operator=(const AudioManager &) = delete;

    static AudioManager &get_instance();

    void initialise();
    ALuint add_audio(const engine::audio::enums::AudioType &audio_type, const std::string &path);
    void play(const engine::audio::enums::AudioType &audio_type, const std::string &name);

    engine::audio::AudioSource *get_empty_audio_source();
    engine::audio::AudioBuffer *get_audio_buffer(const engine::audio::enums::AudioType &audio_type, const std::string &name);

  private:
    AudioManager();
    ~AudioManager();

    void initialise_music();

    static inline constexpr int m_MAX_SOURCES = 128;

    ALCdevice *m_device;
    ALCcontext *m_context;

    std::unordered_map<engine::audio::enums::AudioType, std::unordered_map<std::string, engine::audio::AudioBuffer>> m_audios;
    std::vector<engine::audio::AudioSource> m_audio_sources;
};

} // namespace engine::audio
