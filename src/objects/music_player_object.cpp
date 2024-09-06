#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/music_player_object.hpp>
#include <objects/camera_object.hpp>

#include <render_objects.hpp>
#include <iostream>

namespace fresh {
MusicPlayerObject::MusicPlayerObject() {
  this->_object_def = "musicplayerobject";
}

MusicPlayerObject::MusicPlayerObject(const idk::StringViewChar& music_file_path,
                         idk::i32 frequency,
                         idk::u16 format,
                         idk::i32 channel,
                         idk::i32 buffer_size) noexcept {
  this->_music_resource = std::make_shared<MusicResource>(music_file_path, frequency, format, channel, buffer_size);
}

MusicPlayerObject::MusicPlayerObject(idk::StringViewChar&& music_file_path,
                         idk::i32 frequency,
                         idk::u16 format,
                         idk::i32 channel,
                         idk::i32 buffer_size) noexcept {
  this->_music_resource = std::make_shared<MusicResource>(std::move(music_file_path), frequency, format, channel, buffer_size);
}

MusicPlayerObject::~MusicPlayerObject() {
}

void
MusicPlayerObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  APPLY_DELTAS()
}

void MusicPlayerObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: MusicPlayerObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void
MusicPlayerObject::load_music_source(const idk::StringViewChar& music_file_path,
                  idk::i32 frequency,
                  idk::u16 format,
                  idk::i32 channel,
                  idk::i32 buffer_size) noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::load_music_source")
  this->_music_resource->load_music_source(music_file_path, frequency, format, channel, buffer_size);
}

void
MusicPlayerObject::load_music_source(idk::StringViewChar&& audio_file_path,
                  idk::i32 frequency,
                  idk::u16 format,
                  idk::i32 channel,
                  idk::i32 buffer_size) noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::load_music_source")
  this->_music_resource->load_music_source(std::move(audio_file_path), frequency, format, channel, buffer_size);
}

__idk_nodiscard
idk::i32&
MusicPlayerObject::get_music_volume() noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::get_music_volume")
  return this->_music_resource->get_music_volume();
}

void
MusicPlayerObject::sync_music_volume() noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::sync_music_volume")
  this->_music_resource->sync_music_volume();
}

void
MusicPlayerObject::pause_music() noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::pause_music")
  this->_music_resource->pause_music();
}

void
MusicPlayerObject::resume_music() noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::resume_music")
  this->_music_resource->resume_music();
}

void
MusicPlayerObject::play_music(bool loop) noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::play_music")
  this->_music_resource->play_music(loop);
}

void
MusicPlayerObject::play_fade_in_music(bool loop, idk::i32 ms) noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::play_fade_in_music")
  this->_music_resource->play_fade_in_music(loop, ms);
}

void
MusicPlayerObject::stop_music() noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::stop_music")
  this->_music_resource->stop_music();
}

void
MusicPlayerObject::stop_fade_out_music(bool loop, idk::i32 ms) noexcept {
  CHECK_IS_MUSIC_RESOURCE_EMPTY("MusicPlayerObject::stop_fade_out_music")
  this->_music_resource->stop_fade_out_music(loop, ms);
}
} // namespace fresh