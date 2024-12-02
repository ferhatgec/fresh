// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/modules/engine_window.hpp>
#include <fescript/fescript_array.hpp>
#include <fescript/fescript_token.hpp>
#include <freshengine.hpp>
#include <application/window.hpp>
#include <filesystem>

namespace fescript {
// output: [ width, height ]
[[nodiscard]] Object FescriptEngineWindowGetCurrentWindowSize::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& window_size = FreshInstance->get_window()->get_window_size();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size))); // w
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size))); // h
  }
  return std::move(array);
}

// output: [ position_x, position_y ]
[[nodiscard]] Object FescriptEngineWindowGetCurrentWindowPos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& window_size = FreshInstance->get_window()->get_window_position();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size))); // w
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size))); // h
  }
  return std::move(array);
}

[[nodiscard]] Object FescriptEngineWindowGetCurrentCursorPos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& cursor_pos = FreshInstance->get_cursor_resource().get_world_space_position();
    array->push_value(static_cast<idk::f80>(cursor_pos.x));
    array->push_value(static_cast<idk::f80>(cursor_pos.y));
  }
  return std::move(array);
}

[[nodiscard]] Object FescriptEngineWindowSetWindowIcon::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("EngineWindow_set_window_icon()", 1)
  FreshInstance->get_window()->set_icon(std::get<StringIndex>(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptEngineWindowSetWindowTitle::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  FreshInstance->get_window()->set_title(Interpreter::stringify(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptEngineWindowGetWindowTitle::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return FreshInstance->get_window()->get_title();
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowSetWindowCursor::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.size() < 3) {
    fresh::log_error(fresh::src(), "EngineWindow_set_window_cursor() must take 3 arguments, got {}.", arguments.size());
    return nullptr;
  }
  ERR_CHECK_TYPE_AT("EngineWindow_set_window_cursor()", 0, "string", StringIndex)
  ERR_CHECK_TYPE_AT("EngineWindow_set_window_cursor()", 1, "decimal", LongDoubleIndex)
  ERR_CHECK_TYPE_AT("EngineWindow_set_window_cursor()", 2, "decimal", LongDoubleIndex)
  if(const auto& cursor_image_path = std::get<StringIndex>(arguments.front()); std::filesystem::exists(cursor_image_path)) {
    FreshInstance->get_cursor_resource().load_sprite(
      cursor_image_path,
      static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[2]))
    );
    return true;
  }
  return false;
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowSetWindowMode::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_window_mode()", 1)
  const auto& window_mode = std::get<LongDoubleIndex>(arguments.front());
  switch(static_cast<std::uint8_t>(window_mode)) {
    case FullscreenWindowed:
      FreshInstance->get_window()->fullscreen_windowed();
      break;
    case Fullscreen:
      FreshInstance->get_window()->fullscreen();
      break;
    case Windowed:
    default:
      FreshInstance->get_window()->windowed();
      break;
  }
  return nullptr;
}

// output: EngineWindow_Fullscreen, EngineWindow_FullscreenWindowed or EngineWindow_Windowed
[[nodiscard]] Object FescriptEngineWindowGetWindowMode::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(FreshInstance->get_window()->get_window_mode());
}

// output: nil
[[nodiscard]] Object FescriptEngineWindowSetDefaultClearColor::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_default_clear_color", 3)
  FreshInstance->get_window()->set_clear_color(
    fresh::ColorResource {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[1])),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[2]))
    }
  );
  return nullptr;
}

// output: nil
[[nodiscard]] Object FescriptEngineWindowSetVSync::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("EngineWindow_set_vsync", 1)
  FreshInstance->get_window()->set_vsync_on(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

// output: nil
[[nodiscard]] Object FescriptEngineWindowCloseWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  FreshInstance->set_engine_running(false);
  return nullptr;
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowMaximizeWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  FreshInstance->get_window()->maximize();
  return nullptr;
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowMinimizeWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  FreshInstance->get_window()->minimize();
  return nullptr;
}

// output: nil
[[nodiscard]] Object FescriptEngineWindowRestoreWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  FreshInstance->get_window()->restore();
  return nullptr;
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowIsWindowMaximized::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return FreshInstance->get_window()->maximized();
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowIsWindowMinimized::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return FreshInstance->get_window()->minimized();
}

// output: bool
[[nodiscard]] Object FescriptEngineWindowSetWindowOpacity::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_window_opacity", 1)
  FreshInstance->get_window()->set_opacity(static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments.front())));
  return nullptr;
}

// output: decimal
[[nodiscard]] Object FescriptEngineWindowGetWindowOpacity::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(FreshInstance->get_window()->get_opacity());
}
} // namespace fescript