#include <freshengine.hpp>

namespace fresh {
GuiBaseObject::GuiBaseObject() {
  this->_object_def = "guibaseobject";
}

GuiBaseObject::~GuiBaseObject() {
}

__idk_nodiscard bool
GuiBaseObject::is_mouse_hover() noexcept {
  if(this->_disabled)
    return false;

  idk::Pair<idk::i32, idk::i32> coords = Engine::get_instance()->get_mouse_input().get_current_coordinates();

  // we take cursor as 1 pixel block, 1 width - 1 height, then using AABB on it.
  return (_pos_info.x < coords._first + 1 && _pos_info.x + _pos_info.w > coords._first && _pos_info.y < coords._second + 1 && _pos_info.y + _pos_info.h > coords._second);
}

__idk_nodiscard
  std::function<void()>&
  GuiBaseObject::get_mouse_hover_callback() noexcept {
  return this->_mouse_hover_cb;
}

void GuiBaseObject::sync(bool is_sync_with_camera) noexcept {
}
}// namespace fresh