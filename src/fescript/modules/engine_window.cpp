#include "../../../include/fescript/modules/engine_window.hpp"
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/freshengine.hpp"

namespace fescript {
// output: [ width, height ]
__idk_nodiscard Object FescriptEngineWindowGetCurrentWindowSize::call(Interpreter& interpreter, std::vector <Object> arguments) {
  std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
  {
    const auto window_size = fresh::Engine::get_instance()->get_window()->get_window_size();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size)));
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size)));
  }
  return std::move(array);
}

// output: [ position_x, position_y ]
__idk_nodiscard Object FescriptEngineWindowGetCurrentWindowPos::call(Interpreter& interpreter, std::vector <Object> arguments) {
  std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
  {
    const auto window_size = fresh::Engine::get_instance()->get_window()->get_window_position();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size)));
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size)));
  }
  return std::move(array);
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowIcon::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("EngineWindow_set_window_icon()", 1)
  return fresh::Engine::get_instance()->get_window()->set_icon(std::get<StringIndex>(arguments.front()).data());
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowTitle::call(Interpreter& interpreter, std::vector <Object> arguments) {
  return fresh::Engine::get_instance()->get_window()->set_title(Interpreter::stringify(arguments.front()).data());
}
} // namespace fescript