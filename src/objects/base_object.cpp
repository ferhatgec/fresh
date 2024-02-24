#include "../../include/objects/base_object.hpp"
#include <iostream>

namespace fresh {
BaseObject::BaseObject() {
  this->_pos_info.x = 0;
  this->_pos_info.y = 0;
  this->_pos_info.w = 0;
  this->_pos_info.h = 0;
  this->_copy_last_pos_info.x = 0;
  this->_copy_last_pos_info.y = 0;
  this->_object_id = id::object_id;
  this->_object_def = "baseobject";
  ++id::object_id;
}

BaseObject::BaseObject(bool disabled, bool visible, idk::i32 pos_x, idk::i32 pos_y, idk::i32 width, idk::i32 height)
    : _disabled(disabled),
      _visible(visible) {
  this->_pos_info.x = pos_x;
  this->_pos_info.y = pos_y;
  this->_pos_info.w = width;
  this->_pos_info.h = height;
  this->_copy_last_pos_info.x = 0;
  this->_copy_last_pos_info.y = 0;
  this->_object_id = id::object_id;
  this->_object_def = "baseobject";
  ++id::object_id;
}

BaseObject::~BaseObject() {}

__idk_nodiscard bool&
BaseObject::get_is_disabled() noexcept {
  return this->_disabled;
}

__idk_nodiscard bool&
BaseObject::get_is_visible() noexcept {
  return this->_visible;
}

void BaseObject::set_disabled(bool disabled) noexcept {
  this->_disabled = disabled;
}

void BaseObject::set_visible(bool visible) noexcept {
  this->_visible = visible;
}

void BaseObject::sync() noexcept {
//  std::cout << "Engine info: BaseObject::sync() is not overridden, override sync(), otherwise your changes won't be passed to renderer.\n";
}

__idk_nodiscard
  SDL_Rect&
  BaseObject::get_position_info() noexcept {
  if(this->_block_transform) {
    this->_block_transform = false;
    // FIXME: collision resolution is so sh*t. fuck physics.

    if(this->delta_x() >= 0) {
      this->_pos_info.x += (this->delta_x() != 0) ? -1 : 0;
    } else {
      this->_pos_info.x += 1;
    }

    if(this->delta_y() >= 0) {
      this->_pos_info.y += (this->delta_y() != 0) ? -1 : 0;
    } else {
      this->_pos_info.y += 1;
    }

    for(auto& object : this->_sub_objects) {
      if(object) {
        object->get_position_info().x += this->delta_x();
        object->get_position_info().y += this->delta_y();
        object->get_position_info().w += this->delta_w();
        object->get_position_info().h += this->delta_h();
      }
    }

    return this->_blocked_pos_info;
  }

  for(auto& object : this->_sub_objects) {
    if(object) {
      object->get_position_info().x += this->delta_x();
      object->get_position_info().y += this->delta_y();
      object->get_position_info().w += this->delta_w();
      object->get_position_info().h += this->delta_h();
    }
  }

  this->_copy_last_pos_info = this->_pos_info;
  return this->_pos_info;
}

__idk_nodiscard const idk::u64&
BaseObject::get_object_id() noexcept {
  return this->_object_id;
}

__idk_nodiscard
  idk::i64
  BaseObject::delta_x() noexcept {
  return this->_pos_info.x - this->_copy_last_pos_info.x;
}

__idk_nodiscard
  idk::i64
  BaseObject::delta_y() noexcept {
  return this->_pos_info.y - this->_copy_last_pos_info.y;
}

__idk_nodiscard
  idk::i64
  BaseObject::delta_w() noexcept {
  return this->_pos_info.w - this->_copy_last_pos_info.w;
}

__idk_nodiscard
  idk::i64
  BaseObject::delta_h() noexcept {
  return this->_pos_info.h - this->_copy_last_pos_info.h;
}

void BaseObject::push_object(std::shared_ptr<BaseObject> sub_object) noexcept {
  if(!sub_object.get()) {
    std::cout << "Engine warning: push_object argument contains an invalid pointer!\n";
    return;
  }

  this->_sub_objects.push_back(idk::move(sub_object));
}

__idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>&
  BaseObject::get_sub_objects() noexcept {
  return this->_sub_objects;
}

__idk_nodiscard
  idk::StringViewChar&
  BaseObject::get_name() noexcept {
  return this->_name;
}

/*
template<typename KeyType>
KeyType&
BaseObject::get_property() noexcept {
  std::cout << "Engine info: Override BaseObject<KeyType>::get_property() to access animation functionality.\n";
}*/
}// namespace fresh