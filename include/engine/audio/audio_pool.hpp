#pragma once

#include "engine/audio/audio_buffer.hpp"
#include "engine/audio/audio_source.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <filesystem>
#include <unordered_map>

namespace engine::audio {

class AudioPool {
  public:
    AudioPool();
    ~AudioPool();

    AudioPool(const AudioPool &other) = delete;
    AudioPool &operator=(const AudioPool &other) = delete;
    AudioPool(AudioPool &&other) = delete;
    AudioPool &operator=(AudioPool &&other) = delete;

    void initialise();

    ALuint add_audio(const std::filesystem::path &path);

    engine::audio::AudioSource *get_empty_audio_source();
    engine::audio::AudioBuffer *get_audio_buffer(const std::filesystem::path &path);

  private:
    static inline constexpr int max_audio_sources = 128;

    int m_audio_buffer_id;

    ALCdevice *m_device;
    ALCcontext *m_context;

    std::unordered_map<std::filesystem::path, int> m_audio_buffer_references;
    std::vector<engine::audio::AudioBuffer> m_audio_buffers;

    std::array<engine::audio::AudioSource, max_audio_sources> m_audio_sources;
};

} // namespace engine::audio
