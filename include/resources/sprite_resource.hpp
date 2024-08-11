#pragma once

// resources are objects those are not have any position,
// visibility etc. parameters.

#include <types/stringview.hpp>
#include "../../libs/SDL/include/SDL.h"

namespace fresh {
enum class SpriteBlendMode {
  None,
  Alpha,
  Additive,
  Modulate,
  Multiply
};

class SpriteResource {
public:
  SpriteResource();
  SpriteResource(const idk::StringViewChar& sprite_file);
  SpriteResource(idk::StringViewChar&& sprite_file);
  SpriteResource(const SpriteResource& sprite_resource);
  SpriteResource(SpriteResource&& sprite_resource);
  ~SpriteResource();

  __idk_nodiscard
  SDL_Texture*&
  get_texture() noexcept;

  __idk_nodiscard
  SpriteBlendMode&
  get_blend_mode() noexcept;

  void
  load_resource(const idk::StringViewChar& sprite_file) noexcept;

  void
  load_resource(idk::StringViewChar&& sprite_file) noexcept;

  __idk_nodiscard
  SpriteResource&
  operator=(const SpriteResource& right) noexcept;

  __idk_nodiscard
  SpriteResource&
  operator=(SpriteResource&& right) noexcept;
  idk::StringViewChar _texture_path;
private:
  // we store resource as SDL_Texture, then free it using RAII techniques.
  SDL_Texture* _sprite_texture = nullptr;
  SpriteBlendMode _sprite_blend_mode { SpriteBlendMode::Alpha };
};
} // namespace fresh