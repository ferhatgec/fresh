// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_array.hpp>
#include <fescript/modules/engine_io.hpp>
#include <freshengine.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fescript {
[[nodiscard]] Object FescriptEngineIOIsKeyPressed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_pressed()", 1)
  return FreshInstance->get_keyboard_input().is_key_pressed(static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[0])));
}

[[nodiscard]] Object FescriptEngineIOIsKeyJustPressed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_just_pressed()", 1)
  return FreshInstance->get_keyboard_input().is_key_just_pressed(static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[0])));
}

[[nodiscard]] Object FescriptEngineIOIsKeyReleased::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_released()", 1)
  return FreshInstance->get_keyboard_input().is_key_released(static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[0])));
}

[[nodiscard]] Object FescriptEngineIOIsMouseButtonPressed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_mouse_button_pressed()", 1)
  return FreshInstance->get_mouse_input().is_button_pressed(static_cast<idk::i8>(std::get<LongDoubleIndex>(arguments[0])));
}

[[nodiscard]] Object FescriptEngineIOIsMouseButtonJustPressed::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_mouse_button_just_pressed()", 1)
  return FreshInstance->get_mouse_input().is_button_just_pressed(static_cast<idk::i8>(std::get<LongDoubleIndex>(arguments[0])));
}

[[nodiscard]] Object FescriptEngineIOIsMouseButtonReleased::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_mouse_button_released", 1)
  return FreshInstance->get_mouse_input().is_button_released(static_cast<idk::i8>(std::get<LongDoubleIndex>(arguments[0])));
}
}