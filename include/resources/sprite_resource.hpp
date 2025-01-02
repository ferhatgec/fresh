// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <texture.hpp>
#include "cache_resource.hpp"
#include "meta_data_resource.hpp"

namespace fresh {
enum class SpriteBlendMode {
  None,
  Alpha,
  Additive,
  Modulate,
  Multiply
};


using CacheSpriteResource = CacheResource<std::string, SpriteMetadata>;
using PathSpritePair = CacheSpriteResource::KeyValueType;

// TODO: sprite batching? (should be done within fre2d)
class SpriteResource {
public:
  SpriteResource() noexcept = default;
  explicit SpriteResource(const std::string& sprite_file) noexcept;
  ~SpriteResource() noexcept = default;

  /// SpriteResource::get_texture() returns fre2d::Texture reference.
  [[nodiscard]] fre2d::Texture& get_texture() noexcept;

  /// SpriteResource::load_resource(std::string) loads texture from given
  /// sprite file path.
  /// note:
  /// -----
  /// always pass opt_ptr to make sure that fre2d and fresh textures synchronizes seamlessly.
  /// otherwise you need to do it yourself.
  void load_resource(const std::string& sprite_file, const std::shared_ptr<SpriteObject>& opt_ptr = nullptr) noexcept;

  /// SpriteResource::load_resource() loads texture using previously given
  /// _texture_path via set_path(std::string). no effect if _texture_path is empty.
  void load_resource() noexcept;

  /// SpriteResource::get_path() returns file path that being used for loading
  /// the texture. it will return empty string if no texture had loaded.
  [[nodiscard]] const std::string& get_path() const noexcept;

  void set_path(const std::string& sprite_file) noexcept;
private:
  std::string _texture_path;
  fre2d::Texture _texture;
};
} // namespace fresh