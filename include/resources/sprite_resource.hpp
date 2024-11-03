#pragma once

// resources are objects those are not have any position,
// visibility etc. parameters.

#include <types/stringview.hpp>
#include "../../libs/fre2d/include/texture.hpp"

namespace fresh {
enum class SpriteBlendMode {
  None,
  Alpha,
  Additive,
  Modulate,
  Multiply
};

// TODO: sprite batching? (should be done within fre2d)
class SpriteResource {
public:
  SpriteResource() noexcept = default;
  explicit SpriteResource(const std::string& sprite_file) noexcept;
  ~SpriteResource() noexcept = default;

  /// SpriteResource::get_texture() returns fre2d::Texture reference.
  [[nodiscard]] fre2d::Texture& get_texture() noexcept;

  /// SpriteResource::load_resource(std::string) loads texture by given
  /// sprite file path.
  void load_resource(const std::string& sprite_file) noexcept;

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