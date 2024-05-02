
#include "../include/freshengine.hpp"

#include "../../libs/SDL_image/include/SDL_image.h"
#include <string>

namespace fresh {
std::unique_ptr<Engine> Engine::_instance;
SDL_Event Engine::_event_instance;

Engine::Engine() {}

Engine::Engine(std::shared_ptr<fresh::Window> window) {
  this->_window = idk::move(window);
}

Engine::~Engine() {

  /*
  for(auto& object: Engine::get_instance()->_objects_to_render) {
    if(!object) {
      std::cout << "Engine info: BaseObject is invalid! It may be deleted before.\n";
      continue;
    }

    delete object;
  }*/
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
  std::cout << "Engine info: You should override Engine::update().\n";
}

void Engine::init() {
  std::cout << "Engine info: You should override Engine::init().\n";
}

void Engine::last() {
  std::cout << "Engine info: You should override Engine::last().\n";
}

void Engine::run() {
  this->init();
  Engine::get_instance()->get_cursor_resource().init_cursor();

  if(Engine::get_instance()->_fps == 0) {
    Engine::get_instance()->_fps = 60;
  }

  idk::u64 _desired_delta = 1000 / Engine::get_instance()->_fps;
  idk::u64 _start_loop;
  Uint64 delta_now = SDL_GetPerformanceCounter();
  Uint64 delta_prev = 0;

  while(Engine::get_instance()->_engine_running) {
    _start_loop = SDL_GetTicks64();
    delta_prev = delta_now;
    delta_now = SDL_GetPerformanceCounter();
    RenderObjects::delta_ms = static_cast<idk::f80>((delta_now - delta_prev) * 1000) / static_cast<idk::f80>(SDL_GetPerformanceFrequency());

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

    if(Engine::_event_instance.type == SDL_QUIT) {
      Engine::get_instance()->_engine_running = false;
      break;
    }

    this->update();

    for(auto& object : fresh::RenderObjects::objects_to_render) {
      // FIXME: sync camera pos_x, pos_y, width and height with window width and height.
      // override pos_x and pos_y as 0.
      if(object.get()) {
        if(Engine::get_instance()->_camera_object.get()) {
          if(Engine::get_instance()->_camera_object->is_visible_on_camera(object)) {
            object->sync();
          }
        } else {
          object->sync();
        }
      } else if(!Engine::get_instance()->_camera_object.get()) {
        object->sync();
      } else {
        std::cout << "Engine error: No camera found and iterated object is invalid.\n";
      }
    }

    if(Engine::get_instance()->_camera_object.get())
      Engine::get_instance()->_camera_object->sync();

    Engine::get_instance()->get_cursor_resource().sync_sprite();// it's synced before everything passed to framebuffer.
                                                                // to bypass render priority.
    SDL_RenderPresent(Engine::get_instance()->get_window()->get_renderer());

    if(Engine::get_instance()->_camera_object.get()) {
      Engine::get_instance()->_camera_object->get_position_info().w = Engine::get_instance()->get_window()->_width;
      Engine::get_instance()->_camera_object->get_position_info().h = Engine::get_instance()->get_window()->_height;
    }

    //if(auto delta = SDL_GetTicks64() - _start_loop; delta < _desired_delta) {
    // SDL_Delay( _desired_delta - delta);
    //}
  }

  this->last();// it's not that much necessary.
}

__idk_nodiscard
  idk::u32&
  Engine::get_fps() noexcept {
  return this->_fps;
}

__idk_nodiscard bool
Engine::is_engine_running() noexcept {
  return this->_engine_running;
}

__idk_nodiscard
  KeyboardInput&
  Engine::get_keyboard_input() noexcept {
  return this->_keyboard_input;
}

__idk_nodiscard
  MouseInput&
  Engine::get_mouse_input() noexcept {
  return this->_mouse_input;
}

__idk_nodiscard
  CursorResource&
  Engine::get_cursor_resource() noexcept {
  return this->_cursor_resource;
}

__idk_nodiscard
  ClipboardResource&
  Engine::get_clipboard_resource() noexcept {
  return this->_clipboard_resource;
}

__idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>&
  Engine::get_objects_to_render() noexcept {
  return fresh::RenderObjects::objects_to_render;
}

void Engine::push_object(std::shared_ptr<BaseObject> object) noexcept {
  if(!object.get()) {
    std::cout << "Engine info: Given BaseObject pointer is invalid.\n";
  } else {
    fresh::RenderObjects::objects_to_render.push_back(idk::move(object));
  }
}

void Engine::link_camera(std::shared_ptr<CameraObject> camera_object) noexcept {
  Engine::get_instance()->_camera_object = idk::move(camera_object);
}
}// namespace fresh