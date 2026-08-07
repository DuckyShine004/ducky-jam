#pragma once

#include "engine/audio/audio_buffer.hpp"
#include "engine/audio/audio_source.hpp"
#include "engine/audio/enums/audio_type.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <filesystem>
#include <unordered_map>

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

    ALuint add_audio(const engine::audio::enums::AudioType &audio_type, const std::filesystem::path &path);
    void play(const engine::audio::enums::AudioType &audio_type, const std::filesystem::path &path);

    engine::audio::AudioSource *get_empty_audio_source();
    engine::audio::AudioBuffer *get_audio_buffer(const engine::audio::enums::AudioType &audio_type, const std::filesystem::path &path);

  private:
    static inline constexpr int max_audio_sources = 128;

    static inline const std::filesystem::path m_AUDIO_DIRECTORY = "resources/core/audio";

    ALCdevice *m_device;
    ALCcontext *m_context;

    std::unordered_map<engine::audio::enums::AudioType, std::unordered_map<std::filesystem::path, engine::audio::AudioBuffer>> m_audios;
    std::array<engine::audio::AudioSource, max_audio_sources> m_audio_sources;
};

} // namespace engine::audio
