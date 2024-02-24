#ifndef FRESHENGINE_WINDOW_HPP
#define FRESHENGINE_WINDOW_HPP

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/types/stringview.hpp"
#include "../../libs/SDL/include/SDL.h"

namespace fresh {
class Window {
public:
  friend class Engine;
  friend class Editor;

  Window();
  Window(idk::StringViewChar&& title,
         idk::i32&& width,
         idk::i32&& height,
         idk::i32&& position_x,
         idk::i32&& position_y,
         idk::u32 renderer_flags = SDL_RENDERER_ACCELERATED);

  Window(const idk::StringViewChar& title,
         const idk::i32& width,
         const idk::i32& height,
         const idk::i32& position_x,
         const idk::i32& position_y,
         const idk::u32& renderer_flags);

  ~Window();

  void
  init_window() noexcept;

  __idk_nodiscard
  SDL_Renderer*&
  get_renderer() noexcept;

  __idk_nodiscard
  idk::u32&
  get_renderer_flags() noexcept;

  __idk_nodiscard
  bool
  set_icon(const idk::StringViewChar& icon_path) noexcept;

  __idk_nodiscard
  bool
  set_icon(idk::StringViewChar&& icon_path) noexcept;

  __idk_nodiscard
  bool
  set_title(const idk::StringViewChar& title) noexcept;

  __idk_nodiscard
  bool
  set_title(idk::StringViewChar&& title) noexcept;

  __idk_nodiscard
  SDL_Color&
  get_default_clear_color() noexcept;
private:
  idk::i32 _width { 800_i32 };
  idk::i32 _height { 600_i32 };

  idk::i32 _position_x { 0_i32 },
           _position_y { 0_i32 };

  idk::u32 _renderer_flags { SDL_RENDERER_ACCELERATED };
  idk::StringViewChar _title = "freshEngine Application";

  SDL_Renderer* _renderer = nullptr;
  SDL_Window* _window = nullptr;
  SDL_Color _default_clear_color {
      255, 255, 255, 255
  };
};
} // namespace fresh
#endif // FRESHENGINE_WINDOW_HPP