#ifndef FRESHENGINE_KEYBOARD_INPUT_HPP
#define FRESHENGINE_KEYBOARD_INPUT_HPP

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/SDL/include/SDL.h"

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
#endif // FRESHENGINE_KEYBOARD_INPUT_HPP