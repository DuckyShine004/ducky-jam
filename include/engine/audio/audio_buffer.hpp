#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <cstdint>
#include <filesystem>
#include <span>
#include <vector>

namespace engine::audio {

class AudioBuffer {
  public:
    AudioBuffer(const std::filesystem::path &path);

    ALuint id() const;

    std::int64_t frames() const;
    int channels() const;
    int samplerate() const;

    std::span<const float> samples() const;
    float samples(int index) const;

  private:
    ALenum get_audio_format(SNDFILE *audio_file);

    bool is_openal_error();
    const char *get_openal_error(ALenum error);

    ALuint m_id;

    std::int64_t m_frames;
    int m_channels;
    int m_samplerate;

    std::vector<float> m_samples;
};

} // namespace engine::audio
