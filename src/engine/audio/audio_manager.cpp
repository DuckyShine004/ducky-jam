#include "engine/audio/audio_manager.hpp"

#include "core/exceptions/runtime_exception.hpp"
#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

#include <AL/alext.h>

namespace engine::audio {

namespace utility = core::utility;
namespace exceptions = core::exceptions;

using engine::audio::enums::AudioType;

AudioManager::AudioManager() {
    const ALCchar *device_name = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);

    m_device = alcOpenDevice(device_name);

    if (!m_device) {
        throw exceptions::RuntimeException("Failed to get audio device");
    }

    m_context = alcCreateContext(m_device, nullptr);

    if (!m_context) {
        throw exceptions::RuntimeException("Failed to set audio context");
    }

    ALCboolean is_context_current = alcMakeContextCurrent(m_context);

    if (!is_context_current) {
        throw exceptions::RuntimeException("Failed to make audio context current");
    }
}

AudioManager::~AudioManager() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

ALuint AudioManager::add_audio(const AudioType &audio_type, const std::filesystem::path &path) {
    if (!utility::FileUtility::exists(path)) {
        LOG_ERROR("Audio file '{}' does not exist", path.string());
        return 0;
    }

    AudioBuffer &audio_buffer = m_audios[audio_type][path];

    audio_buffer.add_audio(path);

    return audio_buffer.id();
}

void AudioManager::play(const AudioType &audio_type, const std::filesystem::path &path) {
    auto type_iterator = m_audios.find(audio_type);

    if (type_iterator == m_audios.end()) {
        LOG_ERROR("Audio type '{}' not found", static_cast<int>(audio_type));
        return;
    }

    std::unordered_map<std::filesystem::path, AudioBuffer> &audio_buffers = type_iterator->second;

    if (audio_buffers.empty()) {
        LOG_WARN("Audio buffers are empty");
        return;
    }

    auto buffer_iterator = audio_buffers.find(path);

    if (buffer_iterator == audio_buffers.end()) {
        LOG_ERROR("Audio path '{}' not found", path.string());
        return;
    }

    AudioBuffer &audio_buffer = buffer_iterator->second;
    AudioSource *audio_source = get_empty_audio_source();

    if (!audio_source) {
        LOG_WARN("No sources found. Skipping '{}'", buffer_iterator->first.string());
    }
}

AudioSource *AudioManager::get_empty_audio_source() {
    for (int i = 0; i < max_audio_sources; ++i) {
        AudioSource &audio_source = m_audio_sources[i];

        if (!audio_source.is_playing()) {
            return &audio_source;
        }
    }

    return nullptr;
}

AudioBuffer *AudioManager::get_audio_buffer(const AudioType &audio_type, const std::filesystem::path &path) {
    auto type_iterator = m_audios.find(audio_type);

    if (type_iterator == m_audios.end()) {
        LOG_ERROR("Audio type '{}' not found", static_cast<int>(audio_type));
        return nullptr;
    }

    std::unordered_map<std::filesystem::path, AudioBuffer> &audio_buffers = type_iterator->second;

    if (audio_buffers.empty()) {
        LOG_WARN("Audio buffers are empty");
        return nullptr;
    }

    auto buffer_iterator = audio_buffers.find(path);

    if (buffer_iterator == audio_buffers.end()) {
        LOG_ERROR("Audio path '{}' not found", path.string());
        return nullptr;
    }

    return &buffer_iterator->second;
}

} // namespace engine::audio
