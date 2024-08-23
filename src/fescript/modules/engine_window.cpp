#include "../../../libs/SDL/include/SDL_render.h"
#include <fescript/modules/engine_window.hpp>
#include <fescript/fescript_array.hpp>
#include <fescript/fescript_token.hpp>
#include <freshengine.hpp>
#include <filesystem>

namespace fescript {
// output: [ width, height ]
__idk_nodiscard Object FescriptEngineWindowGetCurrentWindowSize::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& window_size = fresh::Engine::get_instance()->get_window()->get_window_size();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size))); // w
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size))); // h
  }
  return std::move(array);
}

// output: [ position_x, position_y ]
__idk_nodiscard Object FescriptEngineWindowGetCurrentWindowPos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& window_size = fresh::Engine::get_instance()->get_window()->get_window_position();
    array->push_value(static_cast<idk::f80>(std::get<0>(window_size))); // w
    array->push_value(static_cast<idk::f80>(std::get<1>(window_size))); // h
  }
  return std::move(array);
}

__idk_nodiscard Object FescriptEngineWindowGetCurrentCursorPos::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto array = std::make_shared<FescriptArray>();
  {
    const auto& cursor_pos = fresh::Engine::get_instance()->get_mouse_input().get_current_coordinates();
    array->push_value(static_cast<idk::f80>(cursor_pos._first)); // x
    array->push_value(static_cast<idk::f80>(cursor_pos._second)); // y
  }
  return std::move(array);
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowIcon::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("EngineWindow_set_window_icon()", 1)
  return fresh::Engine::get_instance()->get_window()->set_icon(std::get<StringIndex>(arguments.front()).data());
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowTitle::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return fresh::Engine::get_instance()->get_window()->set_title(Interpreter::stringify(arguments.front()).data());
}

// output: string
__idk_nodiscard Object FescriptEngineWindowGetWindowTitle::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return std::string(fresh::Engine::get_instance()->get_window()->get_title().data());
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowCursor::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.size() < 3) {
    std::cout << "Engine error: EngineWindow_set_window_cursor() must take 3 arguments.\n";
    std::exit(1);
  }
  if(arguments.front().index() != StringIndex) {
    std::cout << "Engine error: EngineWindow_set_window_cursor() first argument must be string.\n";
    std::exit(1);
  }
  if((arguments[1].index() != LongDoubleIndex) || (arguments[2].index() != LongDoubleIndex)) {
    std::cout << "Engine error: EngineWindow_set_window_cursor() second and third arguments must be decimal.\n";
    std::exit(1);
  }
  if(const auto& cursor_image_path = std::get<StringIndex>(arguments.front()); std::filesystem::exists(cursor_image_path)) {
    fresh::Engine::get_instance()->get_cursor_resource().get_cursor_sprite().load_resource(cursor_image_path.data());
    fresh::Engine::get_instance()->get_cursor_resource().get_position_info().w = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]));
    fresh::Engine::get_instance()->get_cursor_resource().get_position_info().h = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[2]));
    fresh::Engine::get_instance()->get_cursor_resource().sync_sprite();
    return true;
  }
  return false;
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowMode::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_window_mode()", 1)
  const auto& window_mode = std::get<LongDoubleIndex>(arguments.front());
  return fresh::Engine::get_instance()->get_window()->set_window_mode([window_mode]() -> fresh::Window::WindowMode {
    switch(static_cast<idk::i64>(window_mode)) {
      case SDL_WINDOW_FULLSCREEN: {
        return fresh::Window::WindowMode::Fullscreen;
      }
      case SDL_WINDOW_FULLSCREEN_DESKTOP: {
        return fresh::Window::WindowMode::FullscreenWindowed;
      }
      case 0: {
        [[fallthrough]];
      }
      default: {
        return fresh::Window::WindowMode::Windowed;
      }
    }
  }());
}

// output: EngineWindow_Fullscreen, EngineWindow_FullscreenWindowed or EngineWindow_Windowed
__idk_nodiscard Object FescriptEngineWindowGetWindowMode::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto flag = SDL_GetWindowFlags(fresh::Engine::get_instance()->get_window()->get_raw_window());
  if((flag & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP)
    return static_cast<idk::f80>(SDL_WINDOW_FULLSCREEN_DESKTOP);
  if(flag & SDL_WINDOW_FULLSCREEN_DESKTOP)
    return static_cast<idk::f80>(SDL_WINDOW_FULLSCREEN);
  return 0_f80;
}

// output: nil
__idk_nodiscard Object FescriptEngineWindowSetDefaultClearColor::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_default_clear_color()", 4)
  fresh::Engine::get_instance()->get_window()->get_default_clear_color() = SDL_Color {
    .r = static_cast<idk::u8>(std::get<LongDoubleIndex>(arguments[0])),
    .g = static_cast<idk::u8>(std::get<LongDoubleIndex>(arguments[1])),
    .b = static_cast<idk::u8>(std::get<LongDoubleIndex>(arguments[2])),
    .a = static_cast<idk::u8>(std::get<LongDoubleIndex>(arguments[3]))
  };
  return nullptr;
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetVSync::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("EngineWindow_set_vsync()", 1)
  return static_cast<bool>(
    SDL_RenderSetVSync(fresh::Engine::get_instance()->get_window()->get_renderer(), std::get<BoolIndex>(arguments.front()))
  );
}

// output: nil
__idk_nodiscard Object FescriptEngineWindowCloseWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  fresh::Engine::get_instance()->is_engine_running() = false;
  return nullptr;
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowMaximizeWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return fresh::Engine::get_instance()->get_window()->maximize();
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowMinimizeWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return fresh::Engine::get_instance()->get_window()->minimize();
}

// output: nil
__idk_nodiscard Object FescriptEngineWindowRestoreWindow::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  fresh::Engine::get_instance()->get_window()->restore();
  return nullptr;
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowIsWindowMaximized::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return fresh::Engine::get_instance()->get_window()->is_maximized();
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowIsWindowMinimized::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return fresh::Engine::get_instance()->get_window()->is_minimized();
}

// output: bool
__idk_nodiscard Object FescriptEngineWindowSetWindowOpacity::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("EngineWindow_set_window_opacity", 1)
  return fresh::Engine::get_instance()->get_window()->set_opacity(std::get<LongDoubleIndex>(arguments.front()));
}

// output: decimal
__idk_nodiscard Object FescriptEngineWindowGetWindowOpacity::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(fresh::Engine::get_instance()->get_window()->get_opacity());
}
} // namespace fescript