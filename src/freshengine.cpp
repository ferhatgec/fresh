#include <log/log.hpp>
#include <freshengine.hpp>
#include <string>
#include <types/predefined.hpp>
#include <utility>

namespace fresh {
std::unique_ptr<Engine> Engine::_instance;

Engine::Engine() noexcept {
  this->_font_manager.initialize();
  // we never use C I/O functions such as printf, vprintf, puts etc.
  std::ios_base::sync_with_stdio(false);
}

[[nodiscard]] std::unique_ptr<Engine>& Engine::get_instance() noexcept {
  if(!Engine::_instance) {
    Engine::_instance = std::make_unique<Engine>();
  }
  return Engine::_instance;
}

__idk_nodiscard
std::shared_ptr<Window>&
Engine::get_window() noexcept {
  return this->_window;
}

void Engine::update() {
  log_info(fresh::src(), "you should override Engine::update().");
}

void Engine::init() {
  log_info(fresh::src(), "you should override Engine::init().");
}

void Engine::last() {
  log_info(fresh::src(), "you should override Engine::last().");
}

void Engine::run() {
  if(!Engine::get_instance()->_camera_object) {
    Engine::get_instance()->_camera_object = std::make_shared<CameraObject>(
      Engine::get_instance()->get_window()->get_width(),
      Engine::get_instance()->get_window()->get_height()
    );
  }
  // make sure objects are initialized since FesLoaderResource will create
  // them in-place so we don't want them evaluated at the time.
  // that gives us lazy-evaluated-till-the-run objects.
  for(auto& objects: RenderObjects::objects_to_render) {
    objects->sync_init();
  }
  this->init();

  idk::u64 delta_now = TimerResource::get_universal_tick();
  idk::u64 delta_prev { 0 };

  while(Engine::get_instance()->get_engine_running()) {
    FreshInstance->get_keyboard_input().reset_states();
    FreshInstance->get_mouse_input().reset_states();
    glfwPollEvents();
    delta_prev = delta_now;
    delta_now = TimerResource::get_universal_tick();
    RenderObjects::delta_ms = static_cast<idk::f80>((delta_now - delta_prev) * 1000) / static_cast<idk::f80>(TimerResource::get_universal_tick());
    this->update();
    this->_window->_fb.call([&] {
      const auto& color = Engine::get_instance()->get_window()->get_clear_color();
      this->_window->_fb.clear_color(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
      for(std::size_t i = 0; i < fresh::RenderObjects::objects_to_render.size(); ++i) {
        const auto& sptr = fresh::RenderObjects::objects_to_render[i];
        if(sptr) {
          sptr->sync();
          continue;
        }
        log_warning(fresh::src(), "iterated object is invalid, index is {}.", i);
      }
      if(Engine::get_instance()->_camera_object) {
        Engine::get_instance()->_camera_object->sync();
      }
    });
    this->_window->_fb.clear_color(1.f, 1.f, 1.f, 1.f);
    this->_window->_fb.render_texture();
    glfwSwapBuffers(this->_window->_window);
  }
  this->last(); // it's not that much necessary.
}

[[nodiscard]] const bool& Engine::get_engine_running() const noexcept {
  return this->_engine_running;
}

void Engine::set_engine_running(bool engine_running) noexcept {
  this->_engine_running = engine_running;
}

/// Engine::get_keyboard_input returns KeyboardInput instance.
/// used for handling keyboard inputs, no Unicode support.
__idk_nodiscard
KeyboardInput& Engine::get_keyboard_input() noexcept {
  return this->_keyboard_input;
}

/// Engine::get_mouse_input returns MouseInput instance.
/// used for handling mouse inputs, limited support.
__idk_nodiscard
MouseInput& Engine::get_mouse_input() noexcept {
  return this->_mouse_input;
}

/// Engine::get_cursor_resource returns CursorResource instance.
/// used for changing cursor sprite.
__idk_nodiscard
CursorResource& Engine::get_cursor_resource() noexcept {
  return this->_cursor_resource;
}

/// Engine::get_clipboard_resource returns ClipboardResource instance.
/// used for manipulating clipboard.
__idk_nodiscard ClipboardResource& Engine::get_clipboard_resource() noexcept {
  return this->_clipboard_resource;
}

[[nodiscard]] fre2d::FontManager& Engine::get_font_manager() noexcept {
  if(!this->_font_manager.is_initialized()) {
    this->_font_manager.initialize();
  }
  return this->_font_manager;
}

/// Engine::link_camera assigns given camera object with its own CameraObject
/// instance. it used for checking rendered base object can be seen by borders
/// of camera or not. if it is not; then object won't be rendered, but still do
/// sync. pass your camera using shared_ptr, it does not need ownership.
void Engine::link_camera(std::shared_ptr<CameraObject> camera_object) noexcept {
  if(!camera_object) {
    log_error(src(), "invalid camera object passed.");
    return;
  }
  Engine::get_instance()->_camera_object = std::move(camera_object);
}

/// Engine::get_camera returns CameraObject* as immutable pointer and immutable value.
/// *but* you should never use get_camera() since you pass the CameraObject right, so you know where
/// your object is.
[[nodiscard]]
const std::shared_ptr<CameraObject>& Engine::get_camera() noexcept {
  if(!Engine::get_instance()->_camera_object) {
    log_error(fresh::src(), "_camera_object is nullptr");
    return nullptr;
  }
  return Engine::get_instance()->_camera_object;
}

/// Engine::get_global_id returns current id which is associated with
/// how many BaseObjects have been created; currently it's not thread safe;
/// fresh isn't thread safe either.
[[nodiscard]] const idk::u32& Engine::get_id() noexcept {
  return fresh::Engine::_id;
}

/// Engine::increase_global_id increases current id by 1.
void Engine::increase_global_id() noexcept {
  ++fresh::Engine::_id;
}

/// Engine::reset_global_id sets current id to 0.
void Engine::reset_global_id() noexcept {
  fresh::Engine::_id = 0;
}
}// namespace fresh