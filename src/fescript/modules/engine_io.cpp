#include <fstream>
#include <filesystem>
#include "../../../include/fescript/fescript_interpreter.hpp"
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/fescript/modules/engine_io.hpp"
#include "../../../include/freshengine.hpp"
#include <iostream>

namespace fescript {
__idk_nodiscard Object FescriptEngineIOIsKeyPressed::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_pressed()", 1)
  return fresh::Engine::get_instance()->get_keyboard_input().is_key_pressed(
    static_cast<SDL_Scancode>(fabsl(std::get<LongDoubleIndex>(arguments.front())))
  );
}

__idk_nodiscard Object FescriptEngineIOIsKeyJustPressed::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_just_pressed()", 1)
  return fresh::Engine::get_instance()->get_keyboard_input().is_key_just_pressed(
    static_cast<SDL_Scancode>(fabsl(std::get<LongDoubleIndex>(arguments.front())))
    );
}

__idk_nodiscard Object FescriptEngineIOIsKeyReleased::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_key_released()", 1)
  return fresh::Engine::get_instance()->get_keyboard_input().is_key_released(
    static_cast<SDL_Scancode>(fabsl(std::get<LongDoubleIndex>(arguments.front())))
    );
}

__idk_nodiscard Object FescriptEngineIOIsMouseButtonPressed::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_mouse_button_pressed()", 1)
  return fresh::Engine::get_instance()->get_mouse_input().is_button_pressed(
    static_cast<SDL_Scancode>(fabsl(std::get<LongDoubleIndex>(arguments.front())))
    );
}

__idk_nodiscard Object FescriptEngineIOIsMouseButtonJustPressed::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_DECIMAL("EngineIO_is_mouse_button_just_pressed()", 1)
  return fresh::Engine::get_instance()->get_mouse_input().is_button_just_pressed(
    static_cast<SDL_Scancode>(fabsl(std::get<LongDoubleIndex>(arguments.front())))
    );
}
}