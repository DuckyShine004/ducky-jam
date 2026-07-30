#include <AL/alext.h>

#include "engine/audio/audio_manager.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

using namespace core::logger;
using namespace core::utility;

namespace engine::audio {

using engine::audio::enums::AudioType;

AudioManager &AudioManager::get_instance() {
    static AudioManager instance;

    return instance;
}

AudioManager::AudioManager() {
    const ALCchar *device_name = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);

    m_device = alcOpenDevice(device_name);

    if (!m_device) {
        throw("Failed to get audio device");
    }

    m_context = alcCreateContext(m_device, nullptr);

    if (!m_context) {
        throw("Failed to set audio context");
    }

    ALCboolean is_context_current = alcMakeContextCurrent(m_context);

    if (!is_context_current) {
        throw("Failed to make audio context current");
    }

    m_audio_sources.reserve(m_MAX_SOURCES);

    for (int i = 0; i < m_MAX_SOURCES; ++i) {
        m_audio_sources.emplace_back();
    }
}

AudioManager::~AudioManager() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

void AudioManager::initialise() {
    // this->initialise_music();
}

ALuint AudioManager::add_audio(const AudioType &audio_type, const std::string &path) {
    if (!FileUtility::path_exists(path)) {
        LOG_ERROR("Audio file '{}' does not exist", path);
        return 0;
    }

    AudioBuffer &audio_buffer = m_audios[audio_type][path];

    audio_buffer.add_audio(path);

    return audio_buffer.id();
}

void AudioManager::play(const AudioType &audio_type, const std::string &name) {
    auto type_iterator = m_audios.find(audio_type);

    if (type_iterator == m_audios.end()) {
        LOG_ERROR("Audio type '{}' not found", static_cast<int>(audio_type));
        return;
    }

    std::unordered_map<std::string, AudioBuffer> &audio_buffers = type_iterator->second;

    if (audio_buffers.empty()) {
        LOG_WARN("Audio buffers are empty");
        return;
    }

    auto buffer_iterator = audio_buffers.find(name);

    if (buffer_iterator == audio_buffers.end()) {
        LOG_ERROR("Audio name '{}' not found", name);
        return;
    }

    AudioBuffer &audio_buffer = buffer_iterator->second;
    AudioSource *audio_source = get_empty_audio_source();

    if (!audio_source) {
        LOG_WARN("No sources found. Skipping '{}'", buffer_iterator->first);
    }
}

AudioSource *AudioManager::get_empty_audio_source() {
    for (int i = 0; i < m_MAX_SOURCES; ++i) {
        AudioSource &audio_source = m_audio_sources[i];

        if (!audio_source.is_playing()) {
            return &audio_source;
        }
    }

    return nullptr;
}

AudioBuffer *AudioManager::get_audio_buffer(const AudioType &audio_type, const std::string &name) {
    auto type_iterator = m_audios.find(audio_type);

    if (type_iterator == m_audios.end()) {
        LOG_ERROR("Audio type '{}' not found", static_cast<int>(audio_type));
        return nullptr;
    }

    std::unordered_map<std::string, AudioBuffer> &audio_buffers = type_iterator->second;

    if (audio_buffers.empty()) {
        LOG_WARN("Audio buffers are empty");
        return nullptr;
    }

    auto buffer_iterator = audio_buffers.find(name);

    if (buffer_iterator == audio_buffers.end()) {
        LOG_ERROR("Audio name '{}' not found", name);
        return nullptr;
    }

    return &buffer_iterator->second;
}

} // namespace engine::audio
