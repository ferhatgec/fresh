// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>
#include <unordered_map>
#include <array>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace fresh {
struct KeyState {
  bool pressed { false };
  bool just_pressed { false };
  bool released { false };
};

class KeyboardInput {
public:
  KeyboardInput() noexcept = default;
  ~KeyboardInput() noexcept = default;

  /// KeyboardInput::init() initializes GLFW callbacks.
  static void init() noexcept;
  /// KeyboardInput::reset_states() resets key states to false.
  static void reset_states() noexcept;

  /// KeyboardInput::is_key_pressed(i8) returns pressed state of given key.
  [[nodiscard]] static const bool& is_key_pressed(idk::i32 key) noexcept;
  /// KeyboardInput::is_key_just_pressed(i8) returns just_pressed state of given key.
  [[nodiscard]] static const bool& is_key_just_pressed(idk::i32 key) noexcept;
  /// KeyboardInput::is_key_released(i8) returns released state of given key.
  [[nodiscard]] static const bool& is_key_released(idk::i32 key) noexcept;

  /// KeyboardInput::key_state_cb is callback function that's
  /// being automatically called by GLFW.
  /// Do not use it to call, but it might be good for simulating keyboard inputs.
  static void key_state_cb(
    GLFWwindow* window,
    idk::i32 key,
    idk::i32 scancode,
    idk::i32 action,
    idk::i32 mods
  );
private:
  static inline constinit std::array<KeyState, 348> keys;
};
} // namespace fresh