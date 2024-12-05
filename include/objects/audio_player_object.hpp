// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "base_object.hpp"
#include <types/predefined.hpp>
#include <string>
#include <fescript/fescript_token.hpp>
#include <resources/audio_resource.hpp>

namespace fresh {
class AudioPlayerObject : public BaseObject {
public:
  AudioPlayerObject() noexcept;
  ~AudioPlayerObject() override = default;

  void sync(bool is_member_of_camera = false) noexcept override;
  void set(const fescript::Token& name, fescript::Object value) override;

  /// AudioPlayerObject::get_audio_resource() returns AudioResource reference.
  /// generally AudioPlayerObject is just wrapper around AudioResource; just
  /// derived from BaseObject to make it usable within RenderObjects.
  [[nodiscard]] AudioResource& get_audio_resource() noexcept;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "audioplayerobject";
  }
protected:
  std::shared_ptr<AudioResource> _audio_resource;
};
} // namespace fresh