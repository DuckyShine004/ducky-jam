#pragma once

#include "engine/audio/audio_buffer.hpp"
#include "engine/audio/audio_source.hpp"
#include "engine/audio/enums/audio_type.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace engine::audio {

class AudioManager {
  public:
    AudioManager();
    ~AudioManager();

    AudioManager(const AudioManager &other) = delete;
    AudioManager &operator=(const AudioManager &other) = delete;
    AudioManager(AudioManager &&other) = delete;
    AudioManager &operator=(AudioManager &&other) = delete;

    void initialise();

    void cache_audio(const std::string &path, const std::string &hash);
    void write_cache();

    ALuint add_audio(const engine::audio::enums::AudioType &audio_type, const std::string &path);
    void play(const engine::audio::enums::AudioType &audio_type, const std::string &name);

    engine::audio::AudioSource *get_empty_audio_source();
    engine::audio::AudioBuffer *get_audio_buffer(const engine::audio::enums::AudioType &audio_type, const std::string &name);

  private:
    static inline constexpr int m_MAX_SOURCES = 128;

    static inline constexpr const char *m_AUDIO_DIRECTORY = "resources/core/audio/";
    static inline constexpr const char *m_AUDIO_CACHE_FILE = "resources/core/audio/cache.json";

    ALCdevice *m_device;
    ALCcontext *m_context;

    std::unordered_map<engine::audio::enums::AudioType, std::unordered_map<std::string, engine::audio::AudioBuffer>> m_audios;
    std::array<engine::audio::AudioSource, m_MAX_SOURCES> m_audio_sources;

    std::unordered_map<std::string, std::string> m_audio_cache;

    static std::unordered_map<std::string, std::string> initialise_audio_cache();
};

} // namespace engine::audio
