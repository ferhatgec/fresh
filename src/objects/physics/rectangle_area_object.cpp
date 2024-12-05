// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/camera_object.hpp>

namespace fresh {
RectangleAreaObject::RectangleAreaObject() {
}

RectangleAreaObject::RectangleAreaObject(BBoxResource pos_info) {
  this->_pos_info = pos_info;
}

RectangleAreaObject::RectangleAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to RectangleAreaObject ctor.\n";
    return;
  }
  this->_pos_info = object->get_position();
}

void RectangleAreaObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();

  this->apply_changes();
}

// rectangle to rectangle (using directly object's properties, which shouldn't be used in practice)
__idk_nodiscard
bool RectangleAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  return (!object || this->get_disabled() || object->get_disabled())
    ? false
    // simple 2D AABB collision detection for rectangles.
    : (_pos_info.get_x() < object->_pos_info.get_x() + object->_pos_info.get_w() &&
          _pos_info.get_x() + _pos_info.get_w() > object->_pos_info.get_x() &&
          _pos_info.get_y() < object->_pos_info.get_y() + object->_pos_info.get_h() &&
          _pos_info.get_y() + _pos_info.get_h() > object->_pos_info.get_y());
}

// rectangle to circle
__idk_nodiscard
bool RectangleAreaObject::is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

// rectangle to rectangle
__idk_nodiscard
bool RectangleAreaObject::is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

// rectangle to polygon
__idk_nodiscard
bool RectangleAreaObject::is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

void RectangleAreaObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: RectangleAreaObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
} // namespace fresh