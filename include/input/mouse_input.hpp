//
// Created by gech on 2/6/2024.
//

#ifndef FRESHENGINE_MOUSE_INPUT_HPP
#define FRESHENGINE_MOUSE_INPUT_HPP

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/utilities/pair.hpp"
#include "../../libs/idk/idk/containers/vector.hpp"
#include "../../libs/SDL/include/SDL.h"

namespace fresh {
class MouseInput {
public:
  MouseInput();
  ~MouseInput();

  __idk_nodiscard
  bool
  is_button_pressed(idk::u8 button) noexcept;

  __idk_nodiscard
  bool
  is_button_just_pressed(idk::u8 button) noexcept;

  __idk_nodiscard
  void
  sync_current_coordinates() noexcept;

  __idk_nodiscard
  idk::Pair<idk::i32, idk::i32>&
  get_current_coordinates() noexcept;
protected:
  idk::Pair<idk::i32, idk::i32> _coords { 0_i32, 0_i32 };
  idk::Vector<idk::Pair<bool, idk::u8>> _button_infos {
      { false, SDL_BUTTON_LEFT },
      { false, SDL_BUTTON_MIDDLE },
      { false, SDL_BUTTON_RIGHT },
      { false, SDL_BUTTON_X1 },
      { false, SDL_BUTTON_X2 }
  };
};
} // namespace fresh

#endif // FRESHENGINE_MOUSE_INPUT_HPP
