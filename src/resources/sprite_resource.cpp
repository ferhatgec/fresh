// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <stb_image.h>
#include <filesystem>
#include <freshengine.hpp>
#include <fstream>

#include <log/log.hpp>
#include <ranges>

namespace fresh {
SpriteResource::SpriteResource(const std::string& sprite_file) noexcept {
  this->load_resource(sprite_file);
}

[[nodiscard]] fre2d::Texture& SpriteResource::get_texture() noexcept {
  return this->_texture;
}

// TODO: check if Engine (or Window) already initialized; we might need it
// since fre2d uses OpenGL calls when loading a texture.
void SpriteResource::load_resource(
  const std::string& sprite_file,
  const std::shared_ptr<SpriteObject>& opt_ptr
) noexcept {
  if(!FreshInstance->get_cache_sprite_resource().get_map().contains(sprite_file)) {
    int w {0}, h {0}, channels{0};
    stbi_set_flip_vertically_on_load(true);
    auto* image_data = stbi_load(
      sprite_file.c_str(),
      &w,
      &h,
      &channels,
      0
    );
    if(image_data) {
      SpriteMetadata meta;
      meta.width = w;
      meta.height = h;
      meta.channels = channels;
      meta.tex.load_from_data(
        image_data,
        meta.width,
        meta.height,
        fre2d::detail::texture::default_use_nearest,
        fre2d::detail::texture::default_use_mipmap,
        fre2d::Texture::WrapOptions::default_value(),
        meta.channels
      );
      FreshInstance->get_cache_sprite_resource().push_overwrite(sprite_file, meta);
      stbi_image_free(image_data);
    } else {
      log_warning(src(), "failed to load sprite resource: {}", sprite_file.data());
      return;
    }
  }
  if(const auto& it = FreshInstance->get_cache_sprite_resource().get_sprite_iter(sprite_file);
    it != FreshInstance->get_cache_sprite_resource().end()) {
    const auto& meta = it->second;
    this->_texture = meta.tex;
    this->_texture_path = sprite_file;
    // automatically synchronizes textures between fre2d and fresh;
    // otherwise you need to do it later, fescript does it automatically.
    if(opt_ptr) {
      BaseObject::sync_textures_if_necessary(
        opt_ptr->get_rectangle_mutable().get_mesh_mutable().get_texture_mutable(),
        opt_ptr->get_sprite_resource().get_texture()
      );
    }
  }
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