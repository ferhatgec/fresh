// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/rectangle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>
#include <numbers>

namespace fresh {
RectangleObject::RectangleObject(bool is_filled)
  : _is_filled{is_filled} {}

RectangleObject::RectangleObject(BBoxResource info, ColorResource color, bool is_filled)
  : _is_filled{is_filled} {
  this->_pos_info = info;
  this->set_color(color);
}

void RectangleObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
    this->_rectangle.set_rotation(this->get_rotation());
  }
  if(this->_visible) {
    this->_rectangle.draw(this->_shader, FreshInstance->get_camera()->get_camera());
  }
  this->apply_changes(this->_member_of_camera);
}

void RectangleObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout
        << "Engine [language] error: RectangleObject has no field named as '"
        << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void RectangleObject::init_signal() noexcept {
  // TODO: check if Window and Framebuffer initialized correctly.
  this->_rectangle.initialize_rectangle(
    this->_pos_info.get_w(),
    this->_pos_info.get_h(),
    glm::vec2{this->_pos_info.get_x(), this->_pos_info.get_y()},
    glm::vec4 {
      this->_color.get_red(),
      this->_color.get_green(),
      this->_color.get_blue(),
      this->_color.get_alpha()
    }
  );
  this->init_shader(generic_shader_key);
  this->_initialized = true;
}

__idk_nodiscard ColorResource& RectangleObject::get_color_resource() noexcept {
  return this->_color;
}

__idk_nodiscard
bool& RectangleObject::get_is_filled() noexcept {
  return this->_is_filled;
}

void RectangleObject::set_rotation(idk::f32 rad_degrees) noexcept {
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = rad_degrees;
  this->_rectangle.set_rotation(rad_degrees);
}

void RectangleObject::set_flip_vertically(bool flip_vertically) noexcept {
  this->_rectangle.set_flip_vertically(flip_vertically);
}

void RectangleObject::set_flip_horizontally(bool flip_horizontally) noexcept {
  this->_rectangle.set_flip_horizontally(flip_horizontally);
}

[[nodiscard]] const bool& RectangleObject::get_flip_vertically() const noexcept {
  return this->_rectangle.get_flip_vertically();
}

[[nodiscard]] const bool& RectangleObject::get_flip_horizontally() const noexcept {
  return this->_rectangle.get_flip_horizontally();
}

void RectangleObject::notify_x() noexcept {
  this->_base_notify_xy();
}

void RectangleObject::notify_y() noexcept {
  this->_base_notify_xy();
}

void RectangleObject::notify_w() noexcept {
  this->_base_notify_wh();
}

void RectangleObject::notify_h() noexcept {
  this->_base_notify_wh();
}

void RectangleObject::_base_notify_xy() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_rectangle.set_position({this->get_x(), this->get_y()});
  }
}

void RectangleObject::_base_notify_wh() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_w(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_h(), 0.f)) {
    this->_rectangle.set_scale({this->get_w(), this->get_h(), 1.f});
  }
}
} // namespace fresh