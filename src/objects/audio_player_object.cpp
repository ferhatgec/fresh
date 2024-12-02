// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/audio_player_object.hpp>
#include <objects/camera_object.hpp>
#include <render_objects.hpp>
#include <log/log.hpp>
#include <iostream>

namespace fresh {
AudioPlayerObject::AudioPlayerObject() noexcept {
  this->_audio_resource = std::make_shared<fresh::AudioResource>();
}

void AudioPlayerObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes();
}

void AudioPlayerObject::set(const fescript::Token& name,
                            fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout
        << "Engine [language] error: AudioPlayerObject has no field named as '"
        << name.lexeme << "'.\n";
    std::exit(1);
  }
}

[[nodiscard]] AudioResource& AudioPlayerObject::get_audio_resource() noexcept {
  if(!this->_audio_resource) {
    log_warning(src(), "somehow AudioResource is not initialized by constructor.");
    this->_audio_resource = std::make_shared<fresh::AudioResource>();
  }
  return *this->_audio_resource;
}
} // namespace fresh