// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/camera_object.hpp>

#include <resources/polygon_resource.hpp>

namespace fresh {
PolygonAreaObject::PolygonAreaObject() {
}

PolygonAreaObject::PolygonAreaObject(BBoxResource pos_info) {
  this->_pos_info = pos_info;
}

PolygonAreaObject::PolygonAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to PolygonAreaObject ctor.\n";
    return;
  }
  this->_pos_info = object->get_position();
}

void PolygonAreaObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();

  #ifdef __FRESH_DEBUG
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_polygon_resource().get_polygons() = this->_resource.get_polygons();
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_raw_position_info() = this->get_raw_position_info();
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_color_resource() = this->_color;
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->sync();
  #endif // __FRESH_DEBUG

  this->apply_changes();
}

[[nodiscard]]
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  std::cout << "Engine error: Do not use BaseObject. Use RectangleAreaObject directly.\n";
  std::exit(1);
}

[[nodiscard]]
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(object, shared_from_this());
}

[[nodiscard]]
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(object, shared_from_this());
}

[[nodiscard]]
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(shared_from_this(), object);
}

void PolygonAreaObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: PolygonAreaObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

[[nodiscard]] PolygonResource& PolygonAreaObject::get_polygon_resource() noexcept {
  return this->_resource;
}
} // namespace fresh