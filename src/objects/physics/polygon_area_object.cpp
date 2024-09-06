#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/camera_object.hpp>

#include <resources/polygon_resource.hpp>

namespace fresh {
PolygonAreaObject::PolygonAreaObject() {
  this->_object_def = "polygonareaobject";
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<PolygonObject>();
  this->_color = { 0, 200, 0, 50 };
  #endif // __FRESH_DEBUG
}

PolygonAreaObject::PolygonAreaObject(SDL_FRect pos_info) {
  this->_object_def = "polygonareaobject";
  this->_pos_info = pos_info;
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<PolygonObject>();
  this->_color = { 0, 200, 0, 100 };
  #endif // __FRESH_DEBUG
}

PolygonAreaObject::PolygonAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to PolygonAreaObject ctor.\n";
    return;
  }
  this->_object_def = "polygonareaobject";
  this->_pos_info = object->get_position_info();
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<PolygonObject>();
  this->_color = { 0, 200, 0, 100 };
  #endif // __FRESH_DEBUG
}

void PolygonAreaObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);

  #ifdef __FRESH_DEBUG
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_polygon_resource().get_polygons() = this->_resource.get_polygons();
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_raw_position_info() = this->get_raw_position_info();
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->get_color_resource() = this->_color;
  std::dynamic_pointer_cast<PolygonObject>(this->_collider)->sync(is_sync_with_camera);
  #endif // __FRESH_DEBUG

  APPLY_DELTAS()
}

__idk_nodiscard
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  std::cout << "Engine error: Do not use BaseObject. Use RectangleAreaObject directly.\n";
  std::exit(1);
}

__idk_nodiscard
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(object, shared_from_this());
}

__idk_nodiscard
bool PolygonAreaObject::is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept {
  return AreaObject::is_colliding_with(object, shared_from_this());
}

__idk_nodiscard
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