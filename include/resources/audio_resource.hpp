// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/stringview.hpp>
#include <miniaudio.h>


namespace fresh {
class AudioResource {
public:
  AudioResource() noexcept;
  explicit AudioResource(const std::string& audio_file_path, idk::u32 frequency = 44100) noexcept;
  ~AudioResource() noexcept;

  /// AudioResource::load_audio_source(std::string, unsigned) loads given
  /// file using miniaudio library.
  void load_audio_source(const std::string& audio_file_path, idk::u32 frequency = 44100) noexcept;

  /// AudioResource::get_audio_volume() is read-only access to _audio_volume property.
  [[nodiscard]] const idk::f32& get_audio_volume() const noexcept;

  /// AudioResource::get_audio_frequency() is read-only access to _frequency property.
  [[nodiscard]] const idk::u32& get_audio_frequency() const noexcept;

  /// AudioResource::get_paused() is read-only access to _paused property.
  [[nodiscard]] const bool& get_paused() const noexcept;

  /// AudioResource::get_loop() is read-only access to _loop property.
  [[nodiscard]] const bool& get_loop() const noexcept;

  /// AudioResource::get_initialized() is read-only access to _initialized property.
  /// only true when load_audio_source(std::string, unsigned) is called.
  [[nodiscard]] const bool& get_initialized() const noexcept;

  /// AudioResource::set_audio_volume(float) is write-only access to _audio_volume property.
  /// takes value between 0 and 1.
  void set_audio_volume(idk::f32 volume) noexcept;

  /// AudioResource::pause_audio() pauses current audio.
  void pause_audio() noexcept;

  /// AudioResource::resume_audio() resumes current audio.
  void resume_audio() noexcept;

  /// AudioResource::stop_audio() stops current audio.
  void stop_audio() noexcept;

  /// AudioResource::play_audio(bool) plays current audio.
  void play_audio(bool loop = false) noexcept;

  /// AudioResource::fade_in_audio(bool, float) plays current audio with
  /// fade in effect.
  /// note: this function might need some changes since it might end
  /// earlier than given function parameter seconds.
  void fade_in_audio(bool loop = false, idk::f32 seconds = 1.f) noexcept;

  /// AudioResource::fade_out_audio(bool, float) plays current audio with
  /// fade out effect.
  /// note: this function might need some changes since it might end
  /// earlier than given function parameter seconds.
  void fade_out_audio(bool loop = false, idk::f32 seconds = 1.f) noexcept;
private:
  ma_engine _engine;
  ma_sound _sound;
  idk::f32 _audio_volume, _fade_duration, _fade_step;
  idk::u32 _frequency;
  bool _paused, _loop, _initialized;
};
} // namespace fresh