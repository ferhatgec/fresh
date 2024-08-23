#include <resources/audio_resource.hpp>

namespace fresh {
idk::u16 AudioResource::_channel{0_u16};

AudioResource::AudioResource() {
  // no need for Mix_Init, it's loads up dynamic libraries automatically when we actually load an audio.
  Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
}

AudioResource::AudioResource(const idk::StringViewChar& audio_file_path,
                             idk::i32 frequency,
                             idk::u16 format,
                             idk::i32 channel,
                             idk::i32 buffer_size) noexcept {
  this->load_audio_source(audio_file_path, frequency, format, channel, buffer_size);
}

AudioResource::AudioResource(idk::StringViewChar&& audio_file_path,
                             idk::i32 frequency,
                             idk::u16 format,
                             idk::i32 channel,
                             idk::i32 buffer_size) noexcept {
  this->load_audio_source(std::move(audio_file_path), frequency, format, channel, buffer_size);
}

AudioResource::~AudioResource() {
  if(this->_audio_source) {
    Mix_FreeChunk(this->_audio_source);
    --AudioResource::_channel;
  } else {
    std::cout << "Engine error: AudioResource is not initialized but Engine trying to deallocate it.\n";
  }
}

__idk_nodiscard
  Mix_Chunk*&
  AudioResource::get_audio_source() noexcept {
  return this->_audio_source;
}

void AudioResource::load_audio_source(const idk::StringViewChar& audio_file_path,
                                      idk::i32 frequency,
                                      idk::u16 format,
                                      idk::i32 channel,
                                      idk::i32 buffer_size) noexcept {
  if(this->_audio_source) {
    Mix_FreeChunk(this->_audio_source);
  }

  this->_audio_channel = AudioResource::_channel;
  ++AudioResource::_channel;

  if(Mix_AllocateChannels(AudioResource::_channel) < 0) {
    std::cout << "Engine error: Cannot allocate enough channels for AudioResource.\n";
    return;
  }

  Mix_OpenAudio(frequency, format, channel, buffer_size);
  this->_audio_source = Mix_LoadWAV(audio_file_path.data());
}

void AudioResource::load_audio_source(idk::StringViewChar&& audio_file_path,
                                      idk::i32 frequency,
                                      idk::u16 format,
                                      idk::i32 channel,
                                      idk::i32 buffer_size) noexcept {
  if(this->_audio_source) {
    Mix_FreeChunk(this->_audio_source);
  }

  this->_audio_channel = AudioResource::_channel;

  ++AudioResource::_channel;
  if(Mix_AllocateChannels(AudioResource::_channel) < 0) {
    std::cout << "Engine error: Cannot allocate enough channels for AudioResource.\n";
    return;
  }

  Mix_OpenAudio(frequency, format, channel, buffer_size);
  this->_audio_source = Mix_LoadWAV(idk::move(audio_file_path).data());
}

__idk_nodiscard
  idk::i32&
  AudioResource::get_audio_volume() noexcept {
  this->sync_audio_volume();
  return this->_audio_volume;
}

void AudioResource::sync_audio_volume() noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, yet calling get_audio_volume() is not will work.\n";
    return;
  }

  Mix_VolumeChunk(this->_audio_source, this->_audio_volume);
}

void AudioResource::pause_audio() noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, resume_audio() will not work properly.\n";
    return;
  }

  Mix_Pause(this->_audio_channel);
}

void AudioResource::pause_all_audio() noexcept {
  Mix_Pause(-1);
}

void AudioResource::resume_audio() noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, resume_audio() will not work properly.\n";
    return;
  }

  Mix_Resume(this->_audio_channel);
}

void AudioResource::resume_all_audio() noexcept {
  Mix_Resume(-1);
}

void AudioResource::play_audio(bool loop) noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, play_audio() will not work properly.\n";
    return;
  }

  if(this->_audio_channel = Mix_PlayChannel(this->_audio_channel, this->_audio_source, (loop) ? -1 : 1);
     this->_audio_channel < 0) {
    std::cout << "Engine error: Can't play AudioResource at the moment.\n";
  }
}

void AudioResource::play_fade_in_audio(bool loop, idk::i32 ms) noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, play_fade_in_audio() will not work properly.\n";
    return;
  }

  if(this->_audio_channel = Mix_FadeInChannel(this->_audio_channel, this->_audio_source, (loop) ? -1 : 1, ms);
     this->_audio_channel < 0) {
    std::cout << "Engine error: Can't play AudioResource at the moment.\n";
  }
}

void AudioResource::stop_audio() noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, stop_audio() will not work properly.\n";
    return;
  }

  Mix_HaltChannel(this->_audio_channel);
}

void AudioResource::stop_fade_out_audio(bool loop, idk::i32 ms) noexcept {
  if(!this->_audio_source) {
    std::cout << "Engine error: AudioResource is not initialized, stop_fade_out_audio() will not work properly.\n";
    return;
  }

  Mix_FadeOutChannel(this->_audio_channel, this->_audio_channel);
}

void AudioResource::stop_all_audio() noexcept {
  Mix_HaltChannel(-1);
}
}// namespace fresh