#include "../../include/application/window.hpp"
#include "../../libs/SDL_image/include/SDL_image.h"
#include <iostream>

namespace fresh {
Window::Window() {}

Window::Window(idk::StringViewChar&& title,
               idk::i32&& width,
               idk::i32&& height,
               idk::i32&& position_x,
               idk::i32&& position_y,
               idk::u32 renderer_flags) : _title(idk::move(title)),
                                          _width(idk::move(width)),
                                          _height(idk::move(height)),
                                          _position_x(idk::move(position_x)),
                                          _position_y(idk::move(position_y)),
                                          _renderer_flags(renderer_flags) {
}

Window::Window(const idk::StringViewChar& title,
               const idk::i32& width,
               const idk::i32& height,
               const idk::i32& position_x,
               const idk::i32& position_y,
               const idk::u32& renderer_flags) : _title(title),
                                                 _width(width),
                                                 _height(height),
                                                 _position_x(position_x),
                                                 _position_y(position_y),
                                                 _renderer_flags(renderer_flags) {
}

Window::~Window() {
  if(this->_renderer) {
    SDL_DestroyRenderer(this->_renderer);
  }

  if(this->_window) {
    SDL_DestroyWindow(this->_window);
  }

  SDL_Quit();// goodbye SDL!
}

void Window::init_window() noexcept {
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Engine error: SDL initialization is failed!\n";
    // SDL_getError, initialization of window is failed.
    return;
  }

  this->_window = SDL_CreateWindow(this->_title.data(),
                                   this->_position_x,
                                   this->_position_y,
                                   this->_width,
                                   this->_height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);// TODO: flags will be added later.

  if(!this->_window) {
    // window initialization failed!
    std::cout << "Engine error: Window initialization is failed!\n";
    return;
  }

  this->_renderer = SDL_CreateRenderer(this->_window, -1, this->_renderer_flags);

  if(!this->_renderer) {
    // renderer initialization failed!
    std::cout << "Engine error: Renderer initialization is failed! Use Window::get_renderer() to retry.\n";
    return;
  }

  SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
}

__idk_nodiscard
  SDL_Renderer*&
  Window::get_renderer() noexcept {
  if(!this->_window) {// no initialization made up.
    std::cout << "Engine error: Initialize window first! Then call Window::get_renderer().\n";
  }

  if(this->_window) {
    if(!this->_renderer) {// window is initialized somehow, but renderer is not.
      this->_renderer = SDL_CreateRenderer(this->_window, -1, 0);
      std::cout << "Engine info: Window is initialized but renderer is not. Use Window::init_window() for sync.\n";
    }
  }

  return this->_renderer;
}

__idk_nodiscard
  idk::u32&
  Window::get_renderer_flags() noexcept {
  if(this->_renderer) {
    std::cout << "Engine warning: Renderer already initialized. Use get_renderer_flags() before init_window().\n";
  }

  return this->_renderer_flags;
}

__idk_nodiscard bool
Window::set_icon(const idk::StringViewChar& icon_path) noexcept {
  if(this->_window) {
    SDL_Surface* icon_surface = IMG_Load(icon_path.data());
    if(icon_surface) {
      SDL_SetWindowIcon(this->_window, icon_surface);
      SDL_FreeSurface(icon_surface);
      return true;
    } else {
      std::cout << "Engine error: Window::set_icon() cannot set icon properly, surface cannot be initialized now.\n";
    }
  } else {
    std::cout << "Engine error: Window is not initialized, yet using set_icon makes no sense.\n";
  }

  return false;
}

__idk_nodiscard bool
Window::set_icon(idk::StringViewChar&& icon_path) noexcept {
  if(this->_window) {
    SDL_Surface* icon_surface = IMG_Load(idk::move(icon_path).data());
    if(icon_surface) {
      SDL_SetWindowIcon(this->_window, icon_surface);
      SDL_FreeSurface(icon_surface);
      return true;
    } else {
      std::cout << "Engine error: Window::set_icon() cannot set icon properly, surface cannot be initialized now.\n";
    }
  } else {
    std::cout << "Engine error: Window is not initialized, yet using set_icon makes no sense.\n";
  }

  return false;
}

__idk_nodiscard bool
Window::set_title(const idk::StringViewChar& title) noexcept {
  if(this->_window) {
    SDL_SetWindowTitle(this->_window, title.data());
    return true;
  } else {
    std::cout << "Engine error: Window is not initialized, yet using set_title makes no sense.\n";
  }

  return false;
}

__idk_nodiscard bool
Window::set_title(idk::StringViewChar&& title) noexcept {
  if(this->_window) {
    SDL_SetWindowTitle(this->_window, idk::move(title).data());
    return true;
  } else {
    std::cout << "Engine error: Window is not initialized, yet using set_title makes no sense.\n";
  }

  return false;
}

__idk_nodiscard
  SDL_Color&
  Window::get_default_clear_color() noexcept {
  return this->_default_clear_color;
}
}// namespace fresh