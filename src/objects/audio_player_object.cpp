#include "../../include/objects/audio_player_object.hpp"
#include "../../include/render_objects.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"
#include "../../include/objects/camera_object.hpp"
#include <iostream>

namespace fresh {
AudioPlayerObject::AudioPlayerObject() {
  this->_object_def = "audioplayerobject";
}

AudioPlayerObject::AudioPlayerObject(const idk::StringViewChar& audio_file_path,
                  idk::i32 frequency,
                  idk::u16 format,
                  idk::i32 channel,
                  idk::i32 buffer_size) noexcept {
  this->_audio_resource = std::make_shared<AudioResource>(audio_file_path, frequency, format, channel, buffer_size);
}

AudioPlayerObject::AudioPlayerObject(idk::StringViewChar&& audio_file_path,
                                     idk::i32 frequency,
                                     idk::u16 format,
                                     idk::i32 channel,
                                     idk::i32 buffer_size) noexcept {
  this->_audio_resource = std::make_shared<AudioResource>(std::move(audio_file_path), frequency, format, channel, buffer_size);
}

AudioPlayerObject::~AudioPlayerObject() {
}

void
AudioPlayerObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  APPLY_DELTAS()
}

[[nodiscard]] void AudioPlayerObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AudioPlayerObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void
AudioPlayerObject::load_audio_source(const idk::StringViewChar& audio_file_path,
                  idk::i32 frequency,
                  idk::u16 format,
                  idk::i32 channel,
                  idk::i32 buffer_size) noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::load_audio_source")
  this->_audio_resource->load_audio_source(audio_file_path, frequency, format, channel, buffer_size);
}

void
AudioPlayerObject::load_audio_source(idk::StringViewChar&& audio_file_path,
                  idk::i32 frequency,
                  idk::u16 format,
                  idk::i32 channel,
                  idk::i32 buffer_size) noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::load_audio_source")
  this->_audio_resource->load_audio_source(std::move(audio_file_path), frequency, format, channel, buffer_size);
}

__idk_nodiscard
idk::i32&
AudioPlayerObject::get_audio_volume() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::get_audio_volume")
  return this->_audio_resource->get_audio_volume();
}

void
AudioPlayerObject::sync_audio_volume() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::sync_music_volume")
  this->_audio_resource->sync_audio_volume();
}

void
AudioPlayerObject::pause_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::pause_audio")
  this->_audio_resource->pause_audio();
}

void
AudioPlayerObject::pause_all_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::pause_all_audio")
  this->_audio_resource->pause_all_audio();
}

void
AudioPlayerObject::resume_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::resume_audio")
  this->_audio_resource->resume_audio();
}

void
AudioPlayerObject::resume_all_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::resume_all_audio")
  this->_audio_resource->resume_all_audio();
}

void
AudioPlayerObject::play_audio(bool loop) noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::play_audio")
  this->_audio_resource->play_audio(loop);
}

void
AudioPlayerObject::play_fade_in_audio(bool loop, idk::i32 ms) noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::play_fade_in_audio")
  this->_audio_resource->play_fade_in_audio(loop, ms);
}

void
AudioPlayerObject::stop_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::stop_audio")
  this->_audio_resource->stop_audio();
}

void
AudioPlayerObject::stop_fade_out_audio(bool loop, idk::i32 ms) noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::stop_fade_out_audio")
  this->_audio_resource->stop_fade_out_audio(loop, ms);
}

void
AudioPlayerObject::stop_all_audio() noexcept {
  CHECK_IS_AUDIO_RESOURCE_EMPTY("AudioPlayerObject::stop_all_audio")
  this->_audio_resource->stop_all_audio();
}
} // namespace fresh