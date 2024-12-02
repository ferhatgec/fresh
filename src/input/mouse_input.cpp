// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <freshengine.hpp>

namespace fresh {
void MouseInput::init() noexcept {
  if(!FreshInstance->get_window()->initialized()) {
    log_error(src(), "cannot initialize MouseInput since Window is not initialized.");
    return;
  }
  glfwSetMouseButtonCallback(FreshInstance->get_window()->get_raw_window(), MouseInput::button_state_cb);
}

void MouseInput::reset_states() noexcept {
  std::ranges::for_each(MouseInput::buttons, [](auto& state) noexcept {
    state.just_pressed = state.released = false;
  });
}

[[nodiscard]] const bool&
MouseInput::is_button_pressed(idk::i8 button) noexcept {
  return MouseInput::buttons[button].pressed;
}

[[nodiscard]] const bool& MouseInput::is_button_just_pressed(
    idk::i8 button) noexcept {
  return MouseInput::buttons[button].just_pressed;
}

[[nodiscard]] const bool& MouseInput::is_button_released(idk::i8 button) noexcept {
  return MouseInput::buttons[button].released;
}

void MouseInput::button_state_cb(
  GLFWwindow* window,
  idk::i32 button,
  idk::i32 action,
  idk::i32 mods
) {
  if(button < 0 || button >= MouseInput::buttons.size()) {
    return;
  }
  switch(action) {
    case GLFW_PRESS: {
      if(!buttons[button].pressed) {
        buttons[button].just_pressed = true;
      }
      buttons[button].pressed = true;
      break;
    }
    case GLFW_RELEASE: {
      buttons[button].pressed = false;
      buttons[button].released = true;
    }
  }
}
}  // namespace fresh