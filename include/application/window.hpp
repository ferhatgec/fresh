// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>
#include <resources/color_resource.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <framebuffer.hpp>

enum WindowMode : std::uint8_t {
  Fullscreen,
  FullscreenWindowed,
  Windowed
};

namespace fresh {
namespace defaults {
static constexpr ColorResource clear_color { 1.f, 1.f, 1.f, 1.f };
} // namespace fresh::defaults

// FIXME: quick alt-tab makes framebuffer incomplete.
class Window {
public:
  friend class Engine;

  Window() noexcept;

  Window(
    const std::string& title,
    idk::i32 width,
    idk::i32 height,
    idk::i32 position_x,
    idk::i32 position_y
  ) noexcept;

  ~Window() noexcept;

  // delete copy constructors. only one instance of Window is allowed.
  Window& operator=(const Window& wnd) noexcept = delete;
  Window& operator=(Window&& wnd) noexcept = delete;
  Window(const Window& wnd) noexcept = delete;
  Window(Window&& wnd) noexcept = delete;

  void init_window() noexcept;

  [[nodiscard]] GLFWwindow*& get_raw_window() noexcept;

  void set_icon(const std::string& icon_path) noexcept;
  void set_title(const std::string& title) noexcept;

  void set_vsync_on(bool vsync_on) noexcept;
  [[nodiscard]] const bool& is_vsync_on() const noexcept;

  [[nodiscard]] const std::string& get_title() const noexcept;

  void set_size(idk::i32 width, idk::i32 height) noexcept;

  [[nodiscard]] const ColorResource& get_clear_color() const noexcept;
  void set_clear_color(const ColorResource& colorres) noexcept;

  [[nodiscard]] std::pair<idk::i32, idk::i32> get_window_size() noexcept;
  [[nodiscard]] std::pair<idk::i32, idk::i32> get_window_position() noexcept;

  void fullscreen() noexcept;
  void fullscreen_windowed() noexcept;
  void windowed() noexcept;

  [[nodiscard]] bool is_fullscreen() const noexcept;
  [[nodiscard]] bool is_fullscreen_windowed() const noexcept;
  [[nodiscard]] bool is_windowed() const noexcept;
  [[nodiscard]] const WindowMode& get_window_mode() const noexcept;

  void maximize() noexcept;
  void minimize() noexcept;
  void restore() noexcept;

  [[nodiscard]] bool maximized() const noexcept;
  [[nodiscard]] bool minimized() const noexcept;
  [[nodiscard]] bool initialized() const noexcept;

  void set_opacity(idk::f32 opacity) noexcept;

  [[nodiscard]] idk::f32 get_opacity() noexcept;

  [[nodiscard]] fre2d::Framebuffer& get_framebuffer() noexcept;

  [[nodiscard]] const idk::i32& get_width() const noexcept;
  [[nodiscard]] const idk::i32& get_height() const noexcept;

  [[nodiscard]] const idk::i32& get_x() const noexcept;
  [[nodiscard]] const idk::i32& get_y() const noexcept;
private:
  static void framebuffer_resize_cb(GLFWwindow* window, idk::i32 width, idk::i32 height) noexcept;
  static void window_close_cb(GLFWwindow* window) noexcept;
  static void window_resize_cb(GLFWwindow* window, idk::i32 width, idk::i32 height) noexcept;
  static void window_pos_cb(GLFWwindow* window, idk::i32 x, idk::i32 y) noexcept;
  idk::i32 _width, _height;
  idk::i32 _position_x, _position_y;
  std::string _title;
  fre2d::Framebuffer _fb;
  GLFWwindow* _window;
  ColorResource _clear_color;
  WindowMode _window_mode;
  bool _vsync_status;
};
} // namespace fresh