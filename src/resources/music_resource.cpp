#include <resources/music_resource.hpp>

namespace fresh {
MusicResource::MusicResource() {
  // no need for Mix_Init, it's loads up dynamic libraries automatically when we actually load an audio.
  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
}

MusicResource::MusicResource(const idk::StringViewChar& audio_file_path,
                             idk::i32 frequency,
                             idk::u16 format,
                             idk::i32 channel,
                             idk::i32 buffer_size) noexcept {
  this->load_music_source(audio_file_path);
}

MusicResource::MusicResource(idk::StringViewChar&& audio_file_path,
                             idk::i32 frequency,
                             idk::u16 format,
                             idk::i32 channel,
                             idk::i32 buffer_size) noexcept {
  this->load_music_source(idk::move(audio_file_path));
}

MusicResource::~MusicResource() {
  if(this->_music_source) {
    Mix_FreeMusic(this->_music_source);
  } else {
    std::cout << "Engine info: MusicResource is not initialized but Engine trying to deallocate it.\n";
  }
}

__idk_nodiscard
  Mix_Music*&
  MusicResource::get_music_source() noexcept {
  return this->_music_source;
}

void MusicResource::load_music_source(const idk::StringViewChar& audio_file_path,
                                      idk::i32 frequency,
                                      idk::u16 format,
                                      idk::i32 channel,
                                      idk::i32 buffer_size) noexcept {
  if(this->_music_source) {
    Mix_FreeMusic(this->_music_source);
  }

  Mix_OpenAudio(frequency, format, channel, buffer_size);
  this->_music_source = Mix_LoadMUS(audio_file_path.data());
}

void MusicResource::load_music_source(idk::StringViewChar&& audio_file_path,
                                      idk::i32 frequency,
                                      idk::u16 format,
                                      idk::i32 channel,
                                      idk::i32 buffer_size) noexcept {
  if(this->_music_source) {
    Mix_FreeMusic(this->_music_source);
  }

  Mix_OpenAudio(frequency, format, channel, buffer_size);
  this->_music_source = Mix_LoadMUS(idk::move(audio_file_path).data());
}

__idk_nodiscard
  idk::i32&
  MusicResource::get_music_volume() noexcept {
  this->sync_music_volume();
  return this->_music_volume;
}

void MusicResource::sync_music_volume() noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, yet calling get_music_volume() is not will work.\n";
    return;
  }

  Mix_VolumeMusic(this->_music_volume);
}

void MusicResource::pause_music() noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, resume_music() will not work properly.\n";
    return;
  }

  Mix_PauseMusic();
}

void MusicResource::resume_music() noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, resume_music() will not work properly.\n";
    return;
  }

  Mix_ResumeMusic();
}

void MusicResource::play_music(bool loop) noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, play_music() will not work properly.\n";
    return;
  }

  if(Mix_PlayMusic(this->_music_source, (loop) ? -1 : 1) < 0) {
    std::cout << "Engine error: Can't play MusicResource at the moment.\n";
  }
}

void MusicResource::play_fade_in_music(bool loop, idk::i32 ms) noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, play_fade_in_music() will not work properly.\n";
    return;
  }

  Mix_FadeInMusic(this->_music_source, (loop) ? -1 : 1, ms);
}

void MusicResource::stop_music() noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, stop_music() will not work properly.\n";
    return;
  }

  Mix_HaltMusic();
}

void MusicResource::stop_fade_out_music(bool loop, idk::i32 ms) noexcept {
  if(!this->_music_source) {
    std::cout << "Engine error: MusicResource is not initialized, play_fade_in_music() will not work properly.\n";
    return;
  }

  Mix_FadeOutMusic(ms);
}
}// namespace fresh