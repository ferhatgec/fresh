// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <freshengine.hpp>

#include "log/log.hpp"

namespace fresh {
SpriteResource::SpriteResource(const std::string& sprite_file) noexcept {
  this->load_resource(sprite_file);
}

[[nodiscard]] fre2d::Texture& SpriteResource::get_texture() noexcept {
  return this->_texture;
}

// TODO: check if Engine (or Window) already initialized; we might need it
// since fre2d uses OpenGL calls when loading a texture.
void SpriteResource::load_resource(const std::string& sprite_file) noexcept {
  this->_texture.load(sprite_file.data());
}

void SpriteResource::load_resource() noexcept {
  if(this->get_path().empty()) {
    log_info(src(), "_texture_path is already empty.");
    return;
  }
  this->load_resource(this->_texture_path);
}

[[nodiscard]] const std::string& SpriteResource::get_path() const noexcept {
  return this->_texture_path;
}

void SpriteResource::set_path(const std::string& sprite_file) noexcept {
  this->_texture_path = sprite_file;
}
}  // namespace fresh