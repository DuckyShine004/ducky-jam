#include "engine/audio/audio_pool.hpp"

#include "core/exceptions/runtime_exception.hpp"
#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

#include <AL/alext.h>

namespace engine::audio {

namespace utility = core::utility;
namespace exceptions = core::exceptions;

AudioPool::AudioPool() : m_audio_buffer_id(0) {
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

    for (audio::AudioSource &audio_source : m_audio_sources) {
        audio_source.initialise();
    }
}

AudioPool::~AudioPool() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

ALuint AudioPool::add_audio(const std::filesystem::path &path) {
    if (!utility::FileUtility::exists(path)) {
        LOG_ERROR("Audio file '{}' does not exist", path.string());
        return 0;
    }

    auto iterator = m_audio_buffer_references.find(path);

    if (iterator != m_audio_buffer_references.end()) {
        return m_audio_buffers[iterator->second].id();
    }

    // NOTE: Path is technically unique, so we should expect a 1-1 mapping
    m_audio_buffer_references[path] = m_audio_buffer_id;
    AudioBuffer &audio_buffer = m_audio_buffers.emplace_back(path);

    ++m_audio_buffer_id;

    return audio_buffer.id();
}

AudioSource *AudioPool::get_empty_audio_source() {
    for (int i = 0; i < max_audio_sources; ++i) {
        AudioSource &audio_source = m_audio_sources[i];

        if (!audio_source.playing() && !audio_source.reserved()) {
            audio_source.set_reserved(true);
            return &audio_source;
        }
    }

    return nullptr;
}

/* WARN: Dangerous once we add multithreading, since a pointer reference can become null when a rehash happens */
AudioBuffer *AudioPool::get_audio_buffer(const std::filesystem::path &path) {
    auto iterator = m_audio_buffer_references.find(path);

    if (iterator == m_audio_buffer_references.end()) {
        LOG_ERROR("Audio '{}' not found", path.string());
        return nullptr;
    }

    int buffer_id = iterator->second;

    return &m_audio_buffers[buffer_id];
}

} // namespace engine::audio
