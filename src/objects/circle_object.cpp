// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/circle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
CircleObject::CircleObject(BBoxResource info, CircleResource resource, ColorResource color)
  : _resource{resource} {
  this->_pos_info = info;
  this->set_color(color);
}

void CircleObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();

  if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
    this->_circle.set_rotation(this->get_rotation());
  }

  if(this->_visible) {
    this->_circle.draw(this->_shader, FreshInstance->get_camera()->get_camera(), FreshInstance->get_light_manager());
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

void CircleObject::set_flip_vertically(bool flip_vertically) noexcept {
  this->_circle.set_flip_vertically(flip_vertically);
}

void CircleObject::set_flip_horizontally(bool flip_horizontally) noexcept {
  this->_circle.set_flip_horizontally(flip_horizontally);
}

[[nodiscard]] const bool& CircleObject::get_flip_vertically() const noexcept {
  return this->_circle.get_flip_vertically();
}

[[nodiscard]] const bool& CircleObject::get_flip_horizontally() const noexcept {
  return this->_circle.get_flip_horizontally();
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
  this->init_shader(circle_shader_key);
  this->_initialized = true;
}

void CircleObject::notify_x() noexcept {
  this->_base_notify_xy();
}

void CircleObject::notify_y() noexcept {
  this->_base_notify_xy();
}

void CircleObject::notify_w() noexcept {
  this->_base_notify_wh();
}

void CircleObject::notify_h() noexcept {
  this->_base_notify_wh();
}

void CircleObject::_base_notify_xy() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_circle.set_position({this->get_x(), this->get_y()});
  }
}

void CircleObject::_base_notify_wh() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_w(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_h(), 0.f)) {
    this->_circle.set_scale({this->get_w(), this->get_h(), 1.f});
  }
}
} // namespace fresh