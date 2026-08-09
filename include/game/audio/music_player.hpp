#pragma once

#include "engine/audio/audio_pool.hpp"
#include "game/audio/music_track.hpp"

#include <filesystem>

namespace game::audio {

class MusicPlayer {
  public:
    MusicPlayer(engine::audio::AudioPool &audio_pool);

    void play(const std::filesystem::path &path);
    void update_playlist(std::vector<game::audio::MusicTrack> &playlist);

  private:
    engine::audio::AudioPool &m_audio_pool;

    std::vector<game::audio::MusicTrack> m_playlist;
};

} // namespace game::audio
