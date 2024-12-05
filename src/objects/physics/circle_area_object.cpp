// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/physics/circle_area_object.hpp>
#include <objects/camera_object.hpp>

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <algorithm>

namespace fresh {
CircleAreaObject::CircleAreaObject() {
}

CircleAreaObject::CircleAreaObject(BBoxResource pos_info) {
  this->_pos_info = pos_info;
}

CircleAreaObject::CircleAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to CircleAreaObject ctor.\n";
    return;
  }
  this->_pos_info = object->get_position();
}

void CircleAreaObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();

  this->apply_changes();
}

// circle to rectangle (this crap will probably be removed later because it's nonsense. jUsT uSe ReCtAngLeAreAoBjeCt)
__idk_nodiscard
bool CircleAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  if(!object || this->get_disabled() || object->get_disabled())
    return false;

  const auto closest_x = std::clamp(this->_pos_info.get_x(), object->_pos_info.get_x(), object->_pos_info.get_x() + object->_pos_info.get_w());
  const auto closest_y = std::clamp(this->_pos_info.get_y(), object->_pos_info.get_y(), object->_pos_info.get_y() + object->_pos_info.get_h());

  return std::powf(this->_pos_info.get_x() - closest_x, 2.f) + std::powf(this->_pos_info.get_y() - closest_y, 2.f) < std::powf(this->_resource.get_radius(), 2.f);
}

// circle to circle (not ellipse, not supported rn)
__idk_nodiscard
bool CircleAreaObject::is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

// circle to rectangle
__idk_nodiscard
bool CircleAreaObject::is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(object, shared_from_this());
}

// circle to polygon
__idk_nodiscard
bool CircleAreaObject::is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

void CircleAreaObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CircleAreaObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

[[nodiscard]]
CircleResource& CircleAreaObject::get_circle_resource() noexcept {
  return this->_resource;
}
} // namespace fresh