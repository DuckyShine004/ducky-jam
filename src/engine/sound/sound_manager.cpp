#include <AL/alext.h>

#include "engine/sound/sound_manager.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

using namespace core::logger;
using namespace core::utility;

namespace engine::sound {

using engine::sound::enums::SoundType;

SoundManager &SoundManager::get_instance() {
    static SoundManager instance;

    return instance;
}

SoundManager::SoundManager() {
    const ALCchar *device_name = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);

    m_device = alcOpenDevice(device_name);

    if (!m_device) {
        throw("Failed to get sound device");
    }

    m_context = alcCreateContext(m_device, nullptr);

    if (!m_context) {
        throw("Failed to set sound context");
    }

    ALCboolean is_context_current = alcMakeContextCurrent(m_context);

    if (!is_context_current) {
        throw("Failed to make sound context current");
    }

    m_sources.reserve(m_MAX_SOURCES);

    for (int i = 0; i < m_MAX_SOURCES; ++i) {
        m_sources.emplace_back();
    }
}

SoundManager::~SoundManager() {
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

void SoundManager::initialise() {
    // this->initialise_music();
}

ALuint SoundManager::add_sound(const SoundType &sound_type, const std::string &path) {
    // WARN: should not return 0, exit immediately
    if (!FileUtility::path_exists(path)) {
        LOG_ERROR("Sound file '{}' does not exist", path);
        return 0;
    }

    std::string basename = FileUtility::get_basename_from_path(path);

    LOG_INFO("Sound file: {}", path.c_str());

    Buffer &buffer = m_sounds[sound_type][basename];

    buffer.add_sound(path.c_str());

    return buffer.id;
}

void SoundManager::play(const SoundType &sound_type, const std::string &name) {
    auto type_iterator = m_sounds.find(sound_type);

    if (type_iterator == m_sounds.end()) {
        LOG_ERROR("Sound type '{}' not found", static_cast<int>(sound_type));
        return;
    }

    std::unordered_map<std::string, Buffer> &buffers = type_iterator->second;

    if (buffers.empty()) {
        LOG_WARN("Sound buffers are empty");
        return;
    }

    auto buffer_iterator = buffers.find(name);

    if (buffer_iterator == buffers.end()) {
        LOG_ERROR("Sound name '{}' not found", name);
        return;
    }

    Buffer &buffer = buffer_iterator->second;
    Source *source = get_empty_source();

    if (!source) {
        LOG_WARN("No sources found. Skipping '{}'", buffer_iterator->first);
    }
}

Source *SoundManager::get_empty_source() {
    for (int source_index = 0; source_index < m_MAX_SOURCES; ++source_index) {
        Source &source = m_sources[source_index];

        if (!source.is_playing()) {
            return &source;
        }
    }

    return nullptr;
}

} // namespace engine::sound
