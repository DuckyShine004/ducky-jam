#include "game/audio/music_player.hpp"

namespace game::audio {

namespace engine_audio = engine::audio;

MusicPlayer::MusicPlayer(engine_audio::AudioPool &audio_pool) : m_audio_pool(audio_pool) {
}

// WARN: Handle null buffer and source
void MusicPlayer::play(const std::filesystem::path &path) {
    m_audio_pool.add_audio(path);

    engine_audio::AudioBuffer *buffer = m_audio_pool.get_audio_buffer(path);
    engine_audio::AudioSource *source = m_audio_pool.get_empty_audio_source();

    source->play(buffer->id());
}

void MusicPlayer::update_playlist(std::vector<audio::MusicTrack> &playlist) {
    m_playlist = std::move(playlist);
}

} // namespace game::audio
