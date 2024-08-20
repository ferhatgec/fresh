#include <freshengine.hpp>

namespace fresh {
MouseInput::MouseInput() {}
MouseInput::~MouseInput() {}

__idk_nodiscard bool
MouseInput::is_button_pressed(idk::u8 button) noexcept {
  if(!(button >= 1 && button <= 5))
    return false;

  if(Engine::get_event_instance().type == SDL_POLLSENTINEL) {// SDL_PollEvent is returns false while mouse
                                                             // held down with no any event performed (moving mouse, clicking keys).
                                                             // so, we check for SDL_POLLSENTINEL, which is gives us the information of
                                                             // there's no actually any event waiting to pull. so, we use our _button_infos
                                                             // table to give last frame change.
    return this->_button_infos.at_without_check_reference(button - 1)._first;
  }

  switch(Engine::get_event_instance().type) {
  case SDL_MOUSEBUTTONDOWN: {
    if(Engine::get_event_instance().button.button == button) {
      this->_button_infos.at_without_check_reference(button - 1)._first = true;
      return true;
    }
    break;
  }

  case SDL_MOUSEBUTTONUP: {
    if(Engine::get_event_instance().button.button == button) {
      this->_button_infos.at_without_check_reference(button - 1)._first = false;
      return true;
    }
    break;
  }
  }

  return false;
}

__idk_nodiscard bool
MouseInput::is_button_just_pressed(idk::u8 button) noexcept {
  switch(Engine::get_event_instance().type) {
  case SDL_MOUSEBUTTONUP: {
    this->_button_infos.at_without_check_reference(button - 1)._first = false;
    return Engine::get_event_instance().button.button == button;
  }
  }

  return false;
}

void MouseInput::sync_current_coordinates() noexcept {
  SDL_GetMouseState(&this->_coords._first, &this->_coords._second);
}

__idk_nodiscard
idk::Pair<idk::i32, idk::i32>&
MouseInput::get_current_coordinates() noexcept {
  this->sync_current_coordinates();
  return this->_coords;
}
}// namespace fresh