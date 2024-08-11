#include <objects/physics/circle_area_object.hpp>
#include <objects/camera_object.hpp>

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <algorithm>

namespace fresh {
CircleAreaObject::CircleAreaObject() {
  this->_object_def = "circleareaobject";
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<CircleObject>();
  this->_color = { 0, 200, 0, 100 };
  #endif // __FRESH_DEBUG
}

CircleAreaObject::CircleAreaObject(SDL_FRect pos_info) {
  this->_object_def = "circleareaobject";
  this->_pos_info = pos_info;
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<CircleObject>();
  this->_color = { 0, 200, 0, 100 };
  #endif // __FRESH_DEBUG
}

CircleAreaObject::CircleAreaObject(std::shared_ptr<BaseObject> object) {
  if(!object) {
    std::cout << "Engine error: Passed null pointer to CircleAreaObject ctor.\n";
    return;
  }
  this->_object_def = "circleareaobject";
  this->_pos_info = object->get_position_info();
  #ifdef __FRESH_DEBUG
  this->_collider = std::make_shared<CircleObject>();
  this->_color = { 0, 200, 0, 50 };
  #endif // __FRESH_DEBUG
}

void CircleAreaObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(!this->_visible || this->_disabled)
    return;

  #ifdef __FRESH_DEBUG
  // this and other __FRESH_DEBUGs will be removed, just written for quick test of collision detection.
  std::dynamic_pointer_cast<CircleObject>(this->_collider)->get_circle_resource() = this->_resource;
  std::dynamic_pointer_cast<CircleObject>(this->_collider)->get_raw_position_info() = this->get_raw_position_info();
  std::dynamic_pointer_cast<CircleObject>(this->_collider)->get_color_resource() = this->_color;
  std::dynamic_pointer_cast<CircleObject>(this->_collider)->sync(is_sync_with_camera);
  #endif // __FRESH_DEBUG

  APPLY_DELTAS()
}

// circle to rectangle (this crap will probably be removed later because it's nonsense. jUsT uSe ReCtAngLeAreAoBjeCt)
__idk_nodiscard
bool CircleAreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  if(!object || this->get_is_disabled() || object->get_is_disabled())
    return false;

  const auto closest_x = std::clamp(this->_pos_info.x, object->_pos_info.x, object->_pos_info.x + object->_pos_info.w);
  const auto closest_y = std::clamp(this->_pos_info.y, object->_pos_info.y, object->_pos_info.y + object->_pos_info.h);

  return std::powf(this->_pos_info.x - closest_x, 2.f) + std::powf(this->_pos_info.y - closest_y, 2.f) < std::powf(this->_resource.get_radius(), 2.f);
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