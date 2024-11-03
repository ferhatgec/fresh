#include <resources/audio_resource.hpp>
#include <log/log.hpp>
#include <thread>
#define MINIAUDIO_IMPLEMENTATION
#include "../../libs/miniaudio/miniaudio.h"

namespace fresh {
AudioResource::AudioResource() noexcept
  : _audio_volume{1.f},
    _frequency{44100},
    _initialized{false} {}

AudioResource::AudioResource(const std::string& audio_file_path,
                             idk::u32 frequency) noexcept {
  this->load_audio_source(audio_file_path, frequency);
}

AudioResource::~AudioResource() noexcept {
  ma_sound_uninit(&this->_sound);
  ma_engine_uninit(&this->_engine);
}

void AudioResource::load_audio_source(const std::string& audio_file_path,
                                      idk::u32 frequency) noexcept {
  this->_audio_volume = 1.f;
  this->_paused = false;
  this->_loop = false;
  this->_fade_step = 0.01f;
  this->_fade_duration = 0.f;
  this->_frequency = frequency;
  ma_engine_config engine_config = ma_engine_config_init();
  engine_config.sampleRate = frequency;

  if(ma_engine_init(&engine_config, &this->_engine) != MA_SUCCESS) {
    log_error(src(), "failed to initialize audio engine.");
    return;
  }
  if(ma_sound_init_from_file(
    &this->_engine,
    audio_file_path.c_str(),
    MA_SOUND_FLAG_DECODE,
    NULL,
    NULL,
    &this->_sound
  ) != MA_SUCCESS) {
    log_error(src(), "failed to load sound.");
    return;
  }
  this->set_audio_volume(this->_audio_volume);
  this->_initialized = true;
}

[[nodiscard]] const idk::f32& AudioResource::get_audio_volume() const noexcept {
  return this->_audio_volume;
}

[[nodiscard]] const idk::u32& AudioResource::get_audio_frequency()
    const noexcept {
  return this->_frequency;
}

[[nodiscard]] const bool& AudioResource::get_paused() const noexcept {
  return this->_paused;
}

[[nodiscard]] const bool& AudioResource::get_loop() const noexcept {
  return this->_loop;
}

[[nodiscard]] const bool& AudioResource::get_initialized() const noexcept {
  return this->_initialized;
}

void AudioResource::set_audio_volume(idk::f32 volume) noexcept {
  ma_engine_set_volume(&this->_engine, volume);
  this->_audio_volume = volume;
}

void AudioResource::pause_audio() noexcept {
  if (!this->_paused) {
    ma_sound_stop(&this->_sound);
    this->_paused = true;
  }
}

void AudioResource::resume_audio() noexcept {
  if (this->_paused) {
    ma_sound_start(&this->_sound);
    this->_paused = false;
  }
}

void AudioResource::stop_audio() noexcept {
  ma_sound_stop(&this->_sound);
}

void AudioResource::play_audio(bool loop) noexcept {
  this->_loop = loop;
  ma_sound_start(&this->_sound);
  if (this->_loop) {
    ma_sound_set_looping(&this->_sound, MA_TRUE);
  }
}

void AudioResource::fade_in_audio(bool loop, idk::f32 seconds) noexcept {
  this->_fade_duration = seconds;
  this->_audio_volume = 0.0f;

  idk::f32 step = this->_fade_step * this->_fade_duration;
  ma_sound_start(&this->_sound);

  std::thread fade_thread([this, step] {
    while (this->_audio_volume < 1.0f) {
      this->_audio_volume += step;
      this->set_audio_volume(this->_audio_volume);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });
  fade_thread.detach();
}

void AudioResource::fade_out_audio(bool loop, idk::f32 seconds) noexcept {
  this->_fade_duration = seconds;
  idk::f32 step = this->_fade_step * this->_fade_duration;
  std::thread fade_thread([this, step]() {
    do {
      this->_audio_volume -= step;
      this->set_audio_volume(this->_audio_volume);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (this->_audio_volume > 0.0f);
    this->stop_audio();
  });
  fade_thread.detach();
}
}// namespace fresh