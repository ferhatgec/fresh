#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/polygon_object.hpp>
#include <freshengine.hpp>
#include <algorithm>

namespace fresh {
PolygonObject::PolygonObject() {}

PolygonObject::PolygonObject(PolygonResource resource, ColorResource color)
    : _resource{std::move(resource)}, _color{std::move(color)} {}

PolygonObject::~PolygonObject() {
}

void PolygonObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(this->_visible) {
    this->_polygon.draw(this->_shader, Engine::get_instance()->get_camera()->get_camera());
  }
  this->apply_changes();
}

void PolygonObject::_draw_polygon() noexcept {

}

// very slow way to draw polygon, we may do some optimizations here, but for now it's okay for prototype.
// update: SDL2 seems got SDL_RenderGeometry in 2022, we can use it later but we may need to change
// pointresource a bit.
void PolygonObject::_draw_filled_polygon() noexcept {

}

void PolygonObject::_draw_unfilled_polygon() noexcept {

}

void PolygonObject::_add_render_objects() noexcept {
  //const auto& render_pos = this->get_render_position_info();
  //for(auto& vert: this->get_polygon_resource().get_polygons()) {
  //  vert += PointResource(render_pos._x, render_pos._y);
  //}
}

void PolygonObject::_sub_render_objects() noexcept {
  //const auto& render_pos = this->get_render_position_info();
  //for(auto& vert: this->get_polygon_resource().get_polygons()) {
  //  vert -= PointResource(render_pos._x, render_pos._y);
  //}
}

void PolygonObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout
        << "Engine [language] error: PolygonObject has no field named as '"
        << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void PolygonObject::init_signal() noexcept {
  if(!this->_initialized) {
    // TODO:
    // i am kinda lazy for now but PolygonResource will be based on Vertex2 and Vertex3.
    // so that's unnecessary.
    std::vector<fre2d::Vertex2> convert;

    for(auto& vert: this->_resource.get_polygons()) {
      convert.emplace_back(
        glm::vec2{ vert.get_x(), vert.get_y() },
        glm::vec4{ this->_color.get_red(), this->_color.get_green(), this->_color.get_blue(), this->_color.get_alpha() }
      );
    }
    this->_polygon.initialize_polygon(
      1, 1, // pixel-sized polygons
      convert,
      glm::vec2 { this->_pos_info.get_x(), this->_pos_info.get_y() }
    );
    this->_shader.initialize(
      fre2d::detail::shader::default_vertex,
      fre2d::detail::shader::default_fragment
    );
    this->_initialized = true;
  }
}

__idk_nodiscard PolygonResource& PolygonObject::get_polygon_resource() noexcept {
  return this->_resource;
}

__idk_nodiscard
ColorResource& PolygonObject::get_color_resource() noexcept {
  return this->_color;
}

void PolygonObject::set_rotation(idk::f32 rad_degrees) noexcept {
  if(f32_nearly_equals(this->_rotation_degrees, rad_degrees))
    return;
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  this->get_polygon_resource() = this->get_polygon_resource().rotate(this->_rotation_degrees);
}
} // namespace fresh