#include <freshengine.hpp>

namespace fresh {
KeyboardInput::KeyboardInput() {}
KeyboardInput::~KeyboardInput() {}

__idk_nodiscard bool
KeyboardInput::is_key_pressed(idk::u8 key) noexcept {
  switch(Engine::get_event_instance().type) {
  case SDL_KEYDOWN: {
    return Engine::get_event_instance().key.keysym.scancode == key;
  }
  }

  return false;
}

__idk_nodiscard bool
KeyboardInput::is_key_just_pressed(idk::u8 key) noexcept {
  switch(Engine::get_event_instance().type) {
  case SDL_KEYDOWN: {
    if(Engine::get_event_instance().key.repeat != 0)
      return false;

    return Engine::get_event_instance().key.keysym.scancode == key;
  }
  }

  return false;
}

__idk_nodiscard
bool
KeyboardInput::is_key_released(idk::u8 key) noexcept {
  switch(Engine::get_event_instance().type) {
  case SDL_KEYUP: {
    if(Engine::get_event_instance().key.repeat == 0)
      return Engine::get_event_instance().key.keysym.scancode == key;
    break;
  }
  }
  return false;
}
}// namespace fresh