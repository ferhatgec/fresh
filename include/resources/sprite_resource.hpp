// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

// resources are objects those are not have any position,
// visibility etc. parameters.

#include <stb_image.h>
#include <texture.hpp>

namespace fresh {
enum class SpriteBlendMode {
  None,
  Alpha,
  Additive,
  Modulate,
  Multiply
};

struct SpriteMetadata {
  fre2d::Texture tex;
  idk::i32 width;
  idk::i32 height;
  idk::i32 channels;
};

using PathSpritePair = std::unordered_map<std::string, SpriteMetadata>;

class CacheSpriteResource {
public:
  CacheSpriteResource() noexcept = default;
  ~CacheSpriteResource() noexcept = default;

  void push_overwrite(const std::string& sprite_path, const SpriteMetadata& sprite_data) noexcept;
  [[nodiscard]] PathSpritePair::const_iterator get_sprite_iter(const std::string& sprite_path) const noexcept;
  [[nodiscard]] PathSpritePair& get_map() noexcept;

  [[nodiscard]] PathSpritePair::iterator begin() noexcept;
  [[nodiscard]] PathSpritePair::iterator end() noexcept;
  [[nodiscard]] PathSpritePair::const_iterator cbegin() const noexcept;
  [[nodiscard]] PathSpritePair::const_iterator cend() const noexcept;
private:
  /// first part is sprite path, second is content of the sprite;
  /// mostly in RGBA format.
  PathSpritePair _sprites;
};

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