#include <objects/circle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
CircleObject::CircleObject(BBoxResource info, CircleResource resource, ColorResource color)
  : _resource{resource}, _color{color} {
  this->_pos_info = info;
}

void CircleObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_circle.set_position({this->get_x(), this->get_y()});
  }
  if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
    this->_circle.set_rotation(this->get_rotation());
  }
  if(!fre2d::detail::nearly_equals(this->get_delta_w(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_h(), 0.f)) {
    this->_circle.set_scale({this->get_w(), this->get_h(), 1.f});
  }
  if(this->_visible) {
    this->_circle.draw(this->_shader, FreshInstance->get_camera()->get_camera());
  }
  this->apply_changes();
}

void CircleObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CircleObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
CircleResource& CircleObject::get_circle_resource() noexcept {
  return this->_resource;
}

__idk_nodiscard ColorResource& CircleObject::get_color_resource() noexcept {
  return this->_color;
}

void CircleObject::init_signal() noexcept {
  this->_circle.initialize_circle(
    this->_resource.get_radius(),
    this->_resource.get_radius(),
    glm::vec2{this->get_x(), this->get_y()},
    glm::vec4{
      this->_color.get_red(),
      this->_color.get_green(),
      this->_color.get_blue(),
      this->_color.get_alpha()
    },
    this->_resource.get_thickness()
  );
  if(this->_shader.get_program_id() == 0) {
    this->_shader.initialize(
      fre2d::detail::circle::default_vertex,
      fre2d::detail::circle::default_fragment
    );
  }
  this->_initialized = true;
}
} // namespace fresh