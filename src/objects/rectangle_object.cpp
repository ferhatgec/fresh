#include <objects/rectangle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>
#include <numbers>

namespace fresh {
RectangleObject::RectangleObject(bool is_filled)
  : _is_filled{is_filled} {
  this->_vertices.get_polygons().reserve(4);
  this->_object_def = "rectangleobject";
}

RectangleObject::RectangleObject(SDL_FRect info, ColorResource color, bool is_filled)
  : _color{color}, _is_filled{is_filled} {
  this->_object_def = "rectangleobject";
  this->_pos_info = info;

  // store plain, not rotated 4 vertices; then we can apply given rotation.
  this->_vertices.get_polygons().resize(4);
  this->_vertices.get_polygons()[0] = BaseObject::_rectangle_convert_to_top_left({ 0.f, 0.f, this->_pos_info.w, this->_pos_info.h });
  this->_vertices.get_polygons()[1] = BaseObject::_rectangle_convert_to_top_right({ 0.f, 0.f, this->_pos_info.w, this->_pos_info.h });
  this->_vertices.get_polygons()[2] = BaseObject::_rectangle_convert_to_bottom_right({ 0.f, 0.f, this->_pos_info.w, this->_pos_info.h });
  this->_vertices.get_polygons()[3] = BaseObject::_rectangle_convert_to_bottom_left({ 0.f, 0.f, this->_pos_info.w, this->_pos_info.h });

  // we copy plain polygon.
  this->_angle_generated_vertices.get_polygon_resource() = this->_vertices;

  // don't rotate if rotation is same or nearly equal to 0.
  if(!f32_nearly_equals(this->get_rotation_by_radian_degrees(), 0.f)) {
    this->_angle_generated_vertices.set_rotation_by_radian_degrees(this->_rotation_degrees);
  }

  this->_angle_generated_vertices.get_color_resource() = this->get_color_resource();
  this->_angle_generated_vertices.get_raw_position_info() = this->get_raw_position_info();
  this->_angle_generated_vertices.get_polygon_resource().get_is_filled() = this->_is_filled;

  // we store current version of rotated polygon; guarantee to not change it later.
  this->_angle_generated_vertices_first = this->_angle_generated_vertices;
}

void RectangleObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_visible) {
    SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                           this->get_color_resource().get_red(),
                           this->get_color_resource().get_green(),
                           this->get_color_resource().get_blue(),
                           this->get_color_resource().get_alpha());
    if(f32_nearly_equals(this->get_rotation_by_radian_degrees(), 0.f)) {
      this->_render_pos_info = BaseObject::_center_to_top_left_pivot(this->_render_pos_info);
      if(this->get_is_filled()) {
        SDL_RenderFillRectF(Engine::get_instance()->get_window()->get_renderer(),
                            &this->_render_pos_info);
      } else {
        SDL_RenderDrawRectF(Engine::get_instance()->get_window()->get_renderer(),
                            &this->_render_pos_info);
      }
    } else {
      this->_angle_generated_vertices.get_raw_position_info() = this->get_raw_position_info();
      this->_angle_generated_vertices._render_pos_info = this->_render_pos_info;
      this->_angle_generated_vertices._draw_polygon();
    }
  }
  APPLY_DELTAS()
}

void RectangleObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: RectangleObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
ColorResource& RectangleObject::get_color_resource() noexcept {
  return this->_color;
}

__idk_nodiscard
bool& RectangleObject::get_is_filled() noexcept {
  return this->_is_filled;
}

void RectangleObject::set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept {
  const auto rad_mod = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  if(f32_nearly_equals(this->_rotation_degrees, rad_mod))
    return;
  this->_angle_generated_vertices.get_polygon_resource().get_polygons() = this->_angle_generated_vertices_first.get_polygon_resource().get_polygons();
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = rad_mod;
  this->_angle_generated_vertices.set_rotation_by_radian_degrees(this->_rotation_degrees);
  this->_angle_generated_vertices.get_polygon_resource().get_is_filled() = this->get_is_filled();
}
} // namespace fresh