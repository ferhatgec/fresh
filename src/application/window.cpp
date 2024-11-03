#include <stb_image.h>

#include <application/window.hpp>
#include <helper_funcs.hpp>
#include <log/log.hpp>

#include "freshengine.hpp"

#define CHECK_WINDOW() \
  if(!this->_window) { \
   fresh::log_error(src(), "window has not been initialized."); \
   return; \
  }

#define CHECK_WINDOW(ret_val) \
  if(!this->_window) { \
    fresh::log_error(src(), "window has not been initialized."); \
    return ret_val; \
  }

namespace fresh {
Window::Window() noexcept
  : _width{800},
    _height{600},
    _position_x{0},
    _position_y{0},
    _title("freshEngine Project"),
    _window{nullptr},
    _clear_color{defaults::clear_color},
    _window_mode{WindowMode::Windowed},
    _vsync_status{true} {
}

Window::Window(
  const std::string& title,
  idk::i32 width,
  idk::i32 height,
  idk::i32 position_x,
  idk::i32 position_y
) noexcept
  : _width{width},
    _height{height},
    _position_x{position_x},
    _position_y{position_y},
    _title{title},
    _window{nullptr},
    _clear_color{defaults::clear_color},
    _window_mode{WindowMode::Windowed},
    _vsync_status{true} {
}

Window::~Window() {
  if(this->_window) {
    glfwTerminate();
  }
}

void Window::init_window() noexcept {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->_window = glfwCreateWindow(
    this->_width,
    this->_height,
    this->_title.data(),
    nullptr,
    nullptr
  );

  if(!this->_window) {
    log_error(src(), "cannot initialize GLFW window.");
    return;
  }
  glfwMakeContextCurrent(this->_window);
  this->set_vsync_on(this->is_vsync_on());
  
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    log_error(src(), "cannot initialize GLAD.");
    return;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->_fb.initialize(this->_width, this->_height);

  glfwSetFramebufferSizeCallback(
    FreshInstance->get_window()->get_raw_window(),
    Window::framebuffer_resize_cb
  );
  glfwSetWindowCloseCallback(
    FreshInstance->get_window()->get_raw_window(),
    Window::window_close_cb
  );
  glfwSetWindowSizeCallback(
    FreshInstance->get_window()->get_raw_window(),
    Window::window_resize_cb
  );
  glfwSetWindowPosCallback(
    FreshInstance->get_window()->get_raw_window(),
    Window::window_pos_cb
  );

  FreshInstance->get_keyboard_input().init();
  FreshInstance->get_mouse_input().init();
}

[[nodiscard]] GLFWwindow*& Window::get_raw_window() noexcept {
  return this->_window;
}

void Window::set_icon(const std::string& icon_path) noexcept {
  CHECK_WINDOW()
  stbi_set_flip_vertically_on_load(true);
  idk::i32 width, height, channels;
  auto* pixels = stbi_load(icon_path.c_str(), &width, &height, &channels, 0);
  if(!pixels) {
    log_error(src(), "cannot load icon. file: '{}'", icon_path);
    return;
  }
  if (channels != 4) {
    log_error(src(),
              "icon must be rgba, 4 channelled by default.\n"
              "-- file: '{}', width: '{}', height: '{}', channels: '{}'",
              icon_path, width, height, channels);
    stbi_image_free(pixels);
    return;
  }
  const GLFWimage img[1] {
    width, height, pixels
  };
  glfwSetWindowIcon(this->_window, 1, img);
}

void Window::set_title(const std::string& title) noexcept {
  CHECK_WINDOW()
  glfwSetWindowTitle(this->_window, title.c_str());
  this->_title = title;
}

void Window::set_vsync_on(bool vsync_on) noexcept {
  CHECK_WINDOW()
  glfwSwapInterval(vsync_on ? 1 : 0);
  this->_vsync_status = vsync_on;
}

[[nodiscard]] const bool& Window::is_vsync_on() const noexcept {
  return this->_vsync_status;
}

[[nodiscard]] const std::string& Window::get_title() const noexcept {
  return this->_title;
}

void Window::set_size(idk::i32 width, idk::i32 height) noexcept {
  CHECK_WINDOW()
  glfwSetWindowSize(this->_window, width, height);
  this->_width = width;
  this->_height = height;
  FreshInstance->get_camera()->resize_camera(
    static_cast<idk::f32>(width),
    static_cast<idk::f32>(height)
  );
  this->get_framebuffer().resize(width, height);
}

[[nodiscard]] const ColorResource& Window::get_clear_color() const noexcept {
  return this->_clear_color;
}

void Window::set_clear_color(const ColorResource& colorres) noexcept {
  this->_clear_color = colorres;
}

[[nodiscard]] std::pair<idk::i32, idk::i32> Window::get_window_size() noexcept {
  return { this->_width, this->_height };
}

[[nodiscard]] std::pair<idk::i32, idk::i32> Window::get_window_position() noexcept {
  glfwGetWindowPos(this->_window, &this->_position_x, &this->_position_y);
  return {this->_position_x, this->_position_y};
}

void Window::fullscreen() noexcept {
  auto* monitor = glfwGetPrimaryMonitor();
  const auto* video_mode = glfwGetVideoMode(monitor);
  glfwSetWindowMonitor(
    this->_window,
    monitor,
    0,
    0,
    video_mode->width,
    video_mode->height,
    video_mode->refreshRate
  );
  this->_position_x = this->_position_y = 0;
  this->_width = video_mode->width;
  this->_height = video_mode->height;
  this->_window_mode = WindowMode::Fullscreen;
}

void Window::fullscreen_windowed() noexcept {
  auto* monitor = glfwGetPrimaryMonitor();
  const auto* video_mode = glfwGetVideoMode(monitor);
  glfwSetWindowAttrib(this->_window, GLFW_DECORATED, GLFW_FALSE);
  glfwSetWindowMonitor(
    this->_window,
    nullptr,
    0,
    0,
    video_mode->width,
    video_mode->height,
    video_mode->refreshRate
  );
  glfwSetWindowPos(this->_window, 0, 0);
  this->_position_x = this->_position_y = 0;
  this->_width = video_mode->width;
  this->_height = video_mode->height;
  this->_window_mode = WindowMode::FullscreenWindowed;
}

void Window::windowed() noexcept {
  const auto& [x, y] = this->get_window_position();
  glfwSetWindowMonitor(this->_window, nullptr, x, y, this->_width,
                       this->_height, 0);
  this->_window_mode = WindowMode::Windowed;
}

[[nodiscard]] bool Window::is_fullscreen() const noexcept {
  return this->_window_mode == WindowMode::Fullscreen;
}

[[nodiscard]] bool Window::is_fullscreen_windowed() const noexcept {
  return this->_window_mode == WindowMode::FullscreenWindowed;
}

[[nodiscard]] bool Window::is_windowed() const noexcept {
  return this->_window_mode == WindowMode::Windowed;
}

[[nodiscard]] const WindowMode& Window::get_window_mode() const noexcept {
  return this->_window_mode;
}

void Window::maximize() noexcept {
  glfwSetWindowAttrib(this->_window, GLFW_MAXIMIZED, GLFW_TRUE);
}

void Window::minimize() noexcept {
  glfwIconifyWindow(this->_window);
}

void Window::restore() noexcept {
  glfwRestoreWindow(this->_window);
}

[[nodiscard]] bool Window::maximized() const noexcept {
  return glfwGetWindowAttrib(this->_window, GLFW_MAXIMIZED) == GLFW_TRUE;
}

[[nodiscard]] bool Window::minimized() const noexcept {
  return glfwGetWindowAttrib(this->_window, GLFW_ICONIFIED) == GLFW_TRUE;
}

[[nodiscard]] bool Window::initialized() const noexcept {
  return this->_window && this->_fb.is_complete();
}

void Window::set_opacity(idk::f32 opacity) noexcept {
  glfwSetWindowOpacity(this->_window, opacity);
}

idk::f32 Window::get_opacity() noexcept {
  return glfwGetWindowOpacity(this->_window);
}

[[nodiscard]] fre2d::Framebuffer& Window::get_framebuffer() noexcept {
  return this->_fb;
}

[[nodiscard]] const idk::i32& Window::get_width() const noexcept {
  return this->_width;
}

[[nodiscard]] const idk::i32& Window::get_height() const noexcept {
  return this->_height;
}

[[nodiscard]] const idk::i32& Window::get_x() const noexcept {
  return this->_position_x;
}

[[nodiscard]] const idk::i32& Window::get_y() const noexcept {
  return this->_position_y;
}

void Window::framebuffer_resize_cb(
  [[maybe_unused]] GLFWwindow* window,
  idk::i32 width,
  idk::i32 height
) noexcept {
  FreshInstance->get_window()->get_framebuffer().resize(width, height);
  FreshInstance->get_window()->_width = width;
  FreshInstance->get_window()->_height = height;
}

void Window::window_close_cb([[maybe_unused]] GLFWwindow* window) noexcept {
  Engine::get_instance()->set_engine_running(false);
}

void Window::window_resize_cb([[maybe_unused]] GLFWwindow* window,
                              idk::i32 width,
                              idk::i32 height) noexcept {
 FreshInstance->get_window()->set_size(width, height);
}

void Window::window_pos_cb([[maybe_unused]] GLFWwindow* window, idk::i32 x, idk::i32 y) noexcept {
  FreshInstance->get_window()->_position_x = x;
  FreshInstance->get_window()->_position_y = y;
}
}  // namespace fresh