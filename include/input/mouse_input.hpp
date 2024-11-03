// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>
#include <array>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace fresh {
class MouseInput {
public:
  MouseInput() noexcept = default;
  ~MouseInput() noexcept = default;

  /// MouseInput::init() initializes GLFW callbacks.
  static void init() noexcept;
  /// MouseInput::reset_states() resets button states to false.
  static void reset_states() noexcept;

  /// MouseInput::is_button_pressed(i8) returns pressed state of given button.
  [[nodiscard]] static const bool& is_button_pressed(idk::i8 button) noexcept;
  /// MouseInput::is_button_just_pressed(i8) returns just_pressed state of given button.
  [[nodiscard]] static const bool& is_button_just_pressed(idk::i8 button) noexcept;
  /// MouseInput::is_button_released(i8) returns released state of given button.
  [[nodiscard]] static const bool& is_button_released(idk::i8 button) noexcept;

  /// MouseInput::button_state_cb is callback function that's
  /// being automatically called by GLFW.
  /// Do not use it to call, but it might be good for simulating mouse inputs.
  static void button_state_cb(
    [[unused]] GLFWwindow* window,
    idk::i32 button,
    idk::i32 action,
    idk::i32 mods
  );
private:
  static inline constinit std::array<KeyState, 7> buttons;
};
} // namespace fresh