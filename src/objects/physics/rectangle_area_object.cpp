#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/camera_object.hpp>

namespace fresh {
RectangleAreaObject::RectangleAreaObject() {
  this->_object_def = "rectangleareaobject";
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<RectangleObject>();
  this->_color = { 0, 200, 0, 50 };
  #endif // __FRESH_DEBUG
}

RectangleAreaObject::RectangleAreaObject(SDL_FRect pos_info) {
  this->_object_def = "rectangleareaobject";
  this->_pos_info = pos_info;
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<RectangleObject>();
  this->_color = { 0, 200, 0, 50 };
  #endif // __FRESH_DEBUG
}

RectangleAreaObject::RectangleAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to RectangleAreaObject ctor.\n";
    return;
  }
  this->_object_def = "rectangleareaobject";
  this->_pos_info = object->get_position_info();
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<RectangleObject>();
  this->_color = { 0, 200, 0, 50 };
  #endif // __FRESH_DEBUG
}

void RectangleAreaObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(!this->_visible || this->_disabled)
    return;

  #ifdef __FRESH_DEBUG
  std::dynamic_pointer_cast<RectangleObject>(this->_collider)->get_raw_position_info() = this->get_raw_position_info();
  std::dynamic_pointer_cast<RectangleObject>(this->_collider)->get_color_resource() = this->_color;
  std::dynamic_pointer_cast<RectangleObject>(this->_collider)->sync(is_sync_with_camera);
  #endif // __FRESH_DEBUG

  APPLY_DELTAS()
}

// rectangle to rectangle (using directly object's properties, which shouldn't be used in practice)
__idk_nodiscard
bool RectangleAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  return (!object || this->get_is_disabled() || object->get_is_disabled())
    ? false
    // simple 2D AABB collision detection for rectangles.
    : (_pos_info.x < object->_pos_info.x + object->_pos_info.w &&
          _pos_info.x + _pos_info.w > object->_pos_info.x &&
          _pos_info.y < object->_pos_info.y + object->_pos_info.h &&
          _pos_info.y + _pos_info.h > object->_pos_info.y);
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