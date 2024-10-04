#include <SDL_image.h>
#include <log/log.hpp>
#include <freshengine.hpp>
#include <string>
#include <types/predefined.hpp>

namespace fresh {
std::unique_ptr<Engine> Engine::_instance;
SDL_Event Engine::_event_instance;

Engine::Engine()
  : _scale_mode{Scaling::None} {
}

Engine::Engine(std::shared_ptr<fresh::Window> window) {
  this->_window = std::move(window);
}

Engine::~Engine() {
}

__idk_nodiscard
std::unique_ptr<Engine>&
Engine::get_instance() noexcept {
  if(!Engine::_instance.get())
    Engine::_instance = std::make_unique<Engine>();
  return Engine::_instance;
}

__idk_nodiscard
SDL_Event&
Engine::get_event_instance() noexcept {
  return Engine::_event_instance;
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
  this->init();
  Engine::get_instance()->get_cursor_resource().init_cursor();

  if(Engine::get_instance()->_fps == 0) {
    Engine::get_instance()->_fps = 60;
  }

  Uint64 delta_now = SDL_GetPerformanceCounter();
  Uint64 delta_prev = 0;

  // "2" or "best"; currently same as "linear" in SDL2.
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  while(Engine::get_instance()->_engine_running) {
    if(Engine::_event_instance.type == SDL_QUIT) {
      Engine::get_instance()->_engine_running = false;
      break;
    }

    // checks if window size changed.
    if((Engine::_event_instance.type == SDL_WINDOWEVENT) && (Engine::_event_instance.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {
      if(Engine::get_instance()->_scale_mode == Engine::Scaling::None) {
        Engine::get_instance()->set_scaling_mode(Engine::Scaling::None); // it will update window size.
      }
    }

    delta_prev = delta_now;
    delta_now = SDL_GetPerformanceCounter();

    RenderObjects::delta_ms = static_cast<idk::f80>((delta_now - delta_prev) * 1000) / static_cast<idk::f80>(SDL_GetPerformanceFrequency());

    // update current window width/height.
    SDL_GetWindowSize(Engine::get_instance()->get_window()->_window,
                      &Engine::get_instance()->get_window()->_width,
                      &Engine::get_instance()->get_window()->_height);

    SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                           Engine::get_instance()->get_window()->get_default_clear_color().r,
                           Engine::get_instance()->get_window()->get_default_clear_color().g,
                           Engine::get_instance()->get_window()->get_default_clear_color().b,
                           Engine::get_instance()->get_window()->get_default_clear_color().a);

    SDL_RenderClear(Engine::get_instance()->get_window()->get_renderer());
    SDL_PollEvent(&Engine::_event_instance);

    Engine::get_instance()->get_cursor_resource().sync_position();

    this->update();

    for(std::size_t i = 0; i < fresh::RenderObjects::objects_to_render.size(); ++i) {
      const auto& sptr = fresh::RenderObjects::objects_to_render[i];
      if(sptr) { // object is not empty
        sptr->sync();
        continue;
      }
      log_warning(fresh::src(), "Engine::run() iterated object is invalid, index is {}.", i);
    }

    if(Engine::get_instance()->_camera_object) {
      Engine::get_instance()->_camera_object->sync();
    }

    Engine::get_instance()->get_cursor_resource().sync_sprite(); // it's synced before everything passed to framebuffer.
                                                                 // to bypass render priority.

    SDL_RenderPresent(Engine::get_instance()->get_window()->get_renderer());

    // update camera width/height.
    // if(Engine::get_instance()->_camera_object) {
    //  Engine::get_instance()->_camera_object->get_position_info().w = static_cast<idk::f32>(Engine::get_instance()->get_window()->_width);
    //  Engine::get_instance()->_camera_object->get_position_info().h = static_cast<idk::f32>(Engine::get_instance()->get_window()->_height);
    //}
  }
  this->last(); // it's not that much necessary.
}

/// Engine::get_fps returns current FPS cap.
/// TODO: it does nothing for now.
__idk_nodiscard
idk::u32& Engine::get_fps() noexcept {
  return this->_fps;
}

/// Engine::is_engine_running returns _engine_running variable.
/// which used for checking if engine encountered any error. to exit safely; set _engine_running as false,
/// do not force-call std::exit which may leak memory.
__idk_nodiscard bool&
Engine::is_engine_running() noexcept {
  return this->_engine_running;
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
__idk_nodiscard
ClipboardResource& Engine::get_clipboard_resource() noexcept {
  return this->_clipboard_resource;
}

/// Engine::get_objects_to_render returns RenderObjects::objects_to_render reference.
/// you should not use it directly. use RenderObjects:: functions.
__idk_nodiscard
auto& Engine::get_objects_to_render() noexcept {
  return fresh::RenderObjects::objects_to_render;
}

/// Engine::link_camera assigns given camera object with its own CameraObject instance.
/// it used for checking rendered base object can be seen by borders of camera or not.
/// if it is not; then object won't be rendered, but still do sync.
/// pass your camera using shared_ptr, it does not need ownership.
void Engine::link_camera(const std::shared_ptr<CameraObject>& camera_object) noexcept {
  Engine::get_instance()->_camera_object = camera_object;
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

/// Engine::set_scaling_mode sets renderer scale mode.
/// if scaling mode set to KeepAspectRatio; it would keep resolution ratio
/// when resizing the window. None would cover whole window, depends on having CameraObject or not.
void Engine::set_scaling_mode(Engine::Scaling mode, idk::i32 width, idk::i32 height) noexcept {
  const auto size = Engine::get_instance()->get_window()->get_window_size();
  if(width > std::get<0>(size) || height > std::get<1>(size)) {
    height = std::get<0>(size) * width / height;
    width = std::get<0>(size);
  }
  switch(mode) {
    case Scaling::KeepAspectRatio: {
      idk::i32 scaling_width, scaling_height;
      scaling_width = (width <= 0) ? std::get<0>(size)
                                   : width;
      scaling_height = (height <= 0) ? std::get<1>(size)
                                     : height;
      SDL_RenderSetLogicalSize(Engine::get_instance()->get_window()->get_renderer(),
                               scaling_width, scaling_height);
      break;
    }
    case Scaling::None: {
      Engine::get_instance()->set_scaling_mode(Engine::Scaling::KeepAspectRatio);
      break;
    }
  }
  this->_scale_mode = mode;
}

/// Engine::sin calculates sin(theta) -where theta is radian degrees- and memoize it in a hash map.
[[nodiscard]]
const idk::f32& Engine::sin(const idk::f32& rad_angle) noexcept {
  if(fresh::Engine::_sin.contains(rad_angle)) {
    return std::ref(fresh::Engine::_sin[rad_angle]);
  }
  fresh::Engine::_sin[rad_angle] = std::sinf(rad_angle);
  return std::ref(fresh::Engine::_sin[rad_angle]);
}

/// Engine::cos calculates cos(theta) -where theta is radian degrees- and memoize it in a hash map.
[[nodiscard]]
const idk::f32& Engine::cos(const idk::f32& rad_angle) noexcept {
  if(fresh::Engine::_cos.contains(rad_angle)) {
    return std::ref(fresh::Engine::_cos[rad_angle]);
  }
  fresh::Engine::_cos[rad_angle] = std::cosf(rad_angle);
  return std::ref(fresh::Engine::_cos[rad_angle]);
}

/// Engine::get_global_id returns current id which is associated with
/// how many BaseObjects have been created; currently it's not thread safe;
/// fresh isn't thread safe either.
__idk_nodiscard
idk::u32 Engine::get_global_id() noexcept {
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