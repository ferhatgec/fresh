#pragma once

#include <SDL.h>
#include <types/predefined.hpp>
#include <unordered_map>

namespace fresh {
class KeyboardInput {
public:
  KeyboardInput();
  ~KeyboardInput();

  __idk_nodiscard
  static bool
  is_key_pressed(idk::u8 key) noexcept;

  __idk_nodiscard
  static bool
  is_key_just_pressed(idk::u8 key) noexcept;

  __idk_nodiscard
  static bool
  is_key_released(idk::u8 key) noexcept;
};
} // namespace fresh