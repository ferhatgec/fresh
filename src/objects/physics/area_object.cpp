#include <objects/physics/area_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/camera_object.hpp>

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <resources/circle_resource.hpp>
#include <resources/polygon_resource.hpp>

#include <iostream>
#include <algorithm>

namespace fresh {
AreaObject::AreaObject() {
  std::cout << "Engine info: Do not use AreaObject directly!\n"
               " * Use PolygonAreaObject, CircleObject, RectangleObject or whatever that fill your needs.\n"
               " * But due compability, AreaObject is doing same thing with RectangleObject.\n"
               " * AreaObject is only able to detect collision between rectangles.\n";
  this->_color = { 0, 200, 0, 100 };
}

AreaObject::AreaObject(SDL_FRect pos_info) {
  this->_object_def = "areaobject";
  this->_pos_info = pos_info;
  this->_color = { 0, 200, 0, 100 };
}

AreaObject::AreaObject(std::shared_ptr<BaseObject> base_object) {
  if(!base_object) {
    std::cout << "Engine error: Passed null pointer to AreaObject ctor.\n";
    return;
  }

  this->_object_def = "areaobject";
  this->_pos_info = base_object->_pos_info;
  this->_color = { 0, 200, 0, 100 };
}

void AreaObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  for(auto& object : this->_sub_objects) {
    object->sync(is_sync_with_camera);
  }
  APPLY_DELTAS()
}

__idk_nodiscard bool
AreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {
  if(this->_disabled)
    return false;

  // simple 2D AABB collision detection for rectangles.
  return (_pos_info.x < object->_pos_info.x + object->_pos_info.w &&
          _pos_info.x + _pos_info.w > object->_pos_info.x &&
          _pos_info.y < object->_pos_info.y + object->_pos_info.h &&
          _pos_info.y + _pos_info.h > object->_pos_info.y);
}

__idk_nodiscard bool
AreaObject::is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept {
  std::cout << "Engine error: Use RectangleAreaObject for rectangle to circle collision detections.\n";
  std::exit(1); // FIXME: Set Engine::is_running = false instead of abnormally exit from program.
}

__idk_nodiscard bool
AreaObject::is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept {
  if(!object)
    return false;
  return this->is_colliding_with(std::dynamic_pointer_cast<BaseObject>(object));
}

__idk_nodiscard
bool AreaObject::is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept {
  std::cout << "Engine error: Use RectangleAreaObject for rectangle to polygon collision detections.\n";
  std::exit(1);
}

void AreaObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AreaObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

// rectangle to rectangle collision detection
[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj_1,
                                   const std::shared_ptr<RectangleAreaObject>& rect_obj_2) noexcept {
  if(!rect_obj_1 || !rect_obj_2 || rect_obj_1->get_is_disabled() || rect_obj_2->get_is_disabled())
    return false;

  const SDL_FRect& rect_pos_1 = rect_obj_1->get_raw_position_info();
  const SDL_FRect& rect_pos_2 = rect_obj_2->get_raw_position_info();

  return rect_pos_1.x < rect_pos_2.x + rect_pos_2.w &&
         rect_pos_1.x + rect_pos_1.w > rect_pos_2.x &&
         rect_pos_1.y < rect_pos_2.y + rect_pos_2.h &&
         rect_pos_1.y + rect_pos_1.h > rect_pos_2.y;
}

// rectangle to circle collision detection
[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj,
                                   const std::shared_ptr<CircleAreaObject>& circle_obj) noexcept {
  if(!rect_obj || !circle_obj || rect_obj->get_is_disabled() || circle_obj->get_is_disabled())
    return false;

  const SDL_FRect& rect_pos = rect_obj->get_raw_position_info();
  const SDL_FRect& circle_pos = circle_obj->get_raw_position_info();

  const auto closest_x = std::clamp(circle_pos.x, rect_pos.x,
                                    rect_pos.x + rect_pos.w);
  const auto closest_y = std::clamp(circle_pos.y, rect_pos.y, rect_pos.y + rect_pos.h);

  return std::powf(circle_pos.x - closest_x, 2.f) + std::powf(circle_pos.y - closest_y, 2.f) < std::powf(circle_obj->get_circle_resource().get_radius(), 2.f);
}

// circle to circle collision detection
[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<CircleAreaObject>& circle_obj_1,
                                   const std::shared_ptr<CircleAreaObject>& circle_obj_2) noexcept {
  return (!circle_obj_1 || !circle_obj_2 || circle_obj_1->get_is_disabled() || circle_obj_2->get_is_disabled())
    ? false
    : (
      std::powf(circle_obj_1->get_raw_position_info().x - circle_obj_2->get_raw_position_info().x, 2.f)
        + std::powf(circle_obj_1->get_raw_position_info().y - circle_obj_2->get_raw_position_info().y, 2.f)
      ) <= std::powf(circle_obj_1->get_circle_resource().get_radius() + circle_obj_2->get_circle_resource().get_radius(), 2.f);
}

[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj,
                                   const std::shared_ptr<PolygonAreaObject>& poly_obj) noexcept {
  const auto& rect_pos = rect_obj->get_raw_position_info();
  for(const auto& vert: poly_obj->get_polygon_resource().get_polygons()) {
    // checks if given point is in rectangle.
    // TODO: we need pointobject, lineobject, pointareaobject and lineareaobject.
    // pointobject is same as rectangleobject which has 1x1 width & height.
    // lineobject has begin and end pointresources and contains signed slope.
    if(vert._x >= rect_pos.x && vert._x <= rect_pos.x + rect_pos.w && vert._y >= rect_pos.y && vert._y <= rect_pos.y + rect_pos.h)
      return true;
  }
  return false;
}

[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<CircleAreaObject>& circle_obj,
                                   const std::shared_ptr<PolygonAreaObject>& poly_obj) noexcept {
  const auto& poly_size = poly_obj->get_polygon_resource().get_polygons().size();
  for(std::size_t i = 0; i < poly_size; ++i) {
    const auto& v = poly_obj->get_polygon_resource().get_polygons()[i];
    const auto& w = poly_obj->get_polygon_resource().get_polygons()[(i + 1) % poly_size];
    if(AreaObject::_point_to_line_segment_distance(circle_obj->get_raw_position_info().x, circle_obj->get_raw_position_info().y, v, w)
        <= circle_obj->get_circle_resource().get_radius())
      return true;
  }
  return false;
}

[[nodiscard]]
bool AreaObject::is_colliding_with(const std::shared_ptr<PolygonAreaObject>& poly_obj_1,
                                   const std::shared_ptr<PolygonAreaObject>& poly_obj_2) noexcept {
  const auto& poly_1_size = poly_obj_1->get_polygon_resource().get_polygons().size();
  const auto& poly_2_size = poly_obj_2->get_polygon_resource().get_polygons().size();

  for(std::size_t i = 0; i < poly_1_size; ++i) {
    const auto& v = poly_obj_1->get_polygon_resource().get_polygons()[i];
    const auto& w = poly_obj_1->get_polygon_resource().get_polygons()[(i + 1) % poly_1_size];

    const PointResource axis(w._y - v._y, -(w._x - v._x)); // perpendicular of w and v

    if(poly_obj_1->get_polygon_resource().is_separating_axis_with(poly_obj_2->get_polygon_resource(), axis))
      return false;
  }

  for(std::size_t i = 0; i < poly_2_size; ++i) {
    const auto& v = poly_obj_2->get_polygon_resource().get_polygons()[i];
    const auto& w = poly_obj_2->get_polygon_resource().get_polygons()[(i + 1) % poly_2_size];

    const PointResource axis(w._y - v._y, -(w._x - v._x)); // perpendicular of w and v

    if(poly_obj_2->get_polygon_resource().is_separating_axis_with(poly_obj_2->get_polygon_resource(), axis))
      return false;
  }

  return true;
}

[[nodiscard]]
idk::f32 AreaObject::_point_to_line_segment_distance(const idk::f32& p_x, const idk::f32& p_y, const PointResource& v, const PointResource& w) noexcept {
  idk::f32 l2 = (w._x - v._x) * (w._x - v._x) + (w._y - v._y) * (w._y - v._y);

  if(f32_nearly_equals(l2, 0.f))
    return std::sqrtf((p_x - v._x) * (p_x - v._x) + (p_y - v._y) * (p_y - v._y));

  const idk::f32 t = std::clamp(((p_x - v._x) * (w._x - v._x) + (p_y - v._y) * (w._y - v._y)) / l2, 0.f, 1.f);
  const PointResource projection(v._x + t * (w._x - v._x), v._y + t * (w._y - v._y));

  return std::sqrtf((p_x - projection._x) * (p_x - projection._x) + (p_y - projection._y) * (p_y - projection._y));
}
}// namespace fresh