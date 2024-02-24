#include "../../include/freshengine.hpp"
#include "../../libs/SDL/include/SDL.h"

namespace fresh {
CursorResource::CursorResource() {
}

CursorResource::CursorResource(const SpriteResource& cursor_sprite) {
  this->_cursor_sprite = const_cast<SpriteResource&>(cursor_sprite);
}

CursorResource::CursorResource(SpriteResource&& cursor_sprite) {
  this->_cursor_sprite = idk::move(cursor_sprite);
}

CursorResource::~CursorResource() {
}

void CursorResource::init_cursor() noexcept {
  if(this->_cursor_sprite.get_texture()) {// if cursor sprite has not been changed,
                                          // then not showing the cursor is probably bad idea.
                                          // this function (init_cursor) can be overridden by anyone.
    this->show_cursor(false);
  }
}

__idk_nodiscard
  SpriteResource&
  CursorResource::get_cursor_sprite() noexcept {
  return this->_cursor_sprite;
}

__idk_nodiscard
  SDL_Rect&
  CursorResource::get_position_info() noexcept {
  return this->_pos_info;
}

void CursorResource::sync_position() noexcept {
  SDL_GetMouseState(&this->_pos_info.x, &this->_pos_info.y);
}

void CursorResource::sync_sprite() noexcept {
  SDL_RenderCopy(Engine::get_instance()->get_window()->get_renderer(), this->_cursor_sprite.get_texture(), NULL, &this->_pos_info);
}

void CursorResource::show_cursor(bool show) noexcept {
  SDL_ShowCursor(show);
}

__idk_nodiscard
  CursorResource&
  CursorResource::operator=(const CursorResource& right) noexcept {
  this->_cursor_sprite = right._cursor_sprite;
  this->_pos_info = right._pos_info;
  return *this;
}

__idk_nodiscard
  CursorResource&
  CursorResource::operator=(CursorResource&& right) noexcept {
  this->_cursor_sprite = idk::move(right._cursor_sprite);
  this->_pos_info = idk::move(right._pos_info);
  return *this;
}
}// namespace fresh