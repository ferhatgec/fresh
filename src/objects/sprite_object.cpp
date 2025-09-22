// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>
#include <objects/physics/circle_area_object.hpp>

namespace fresh {
SpriteObject::SpriteObject() : _cache_degrees{0.f} {
  this->_object_id = FreshInstance->get_id();
  FreshInstance->increase_global_id();
}

// disable gizmos etc when exporting the project. it's easy to make with some booleans or different function
// that being called in exporting process?
void SpriteObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
    this->_rectangle.set_rotation(this->get_rotation());
  }
  if(this->_visible) {
    this->_rectangle.draw(this->_shader, FreshInstance->get_camera()->get_camera(), FreshInstance->get_light_manager());
  }
  this->apply_changes();
}

__idk_nodiscard
SpriteResource& SpriteObject::get_sprite_resource() noexcept {
  return this->_sprite_resource;
}

void SpriteObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else if (name.lexeme == "sprite_resource")
    this->get_sprite_resource().set_path(std::get<StringIndex>(value));
  else {
    std::cout << "Engine [language] error: SpriteObject has no field named as '"
              << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void SpriteObject::init_signal() noexcept {
  this->_rectangle.initialize_rectangle(
    this->_pos_info.get_w(),
    this->_pos_info.get_h(),
    glm::vec2{this->_pos_info.get_x(), this->_pos_info.get_y()},
    glm::vec4 {1.f, 1.f, 1.f, 1.f},
    this->_sprite_resource.get_texture()
  );
  this->init_shader(generic_shader_key);
  this->_initialized = true;
}

void SpriteObject::set_rotation(idk::f32 rad_degrees) noexcept {
  if (f32_nearly_equals(rad_degrees, this->_rotation_degrees)) {
    return;
  }
  this->_rotation_degrees = rad_degrees;
  // radians to degrees (SDL uses degrees and clockwise winding)
  // fresh uses radian degrees and clockwise winding.
  this->_cache_degrees = this->_rotation_degrees * 180.f / std::numbers::pi_v<idk::f32>;
}

void SpriteObject::set_flip_vertically(bool flip_vertically) noexcept {
  this->_rectangle.set_flip_vertically(flip_vertically);
}

void SpriteObject::set_flip_horizontally(bool flip_horizontally) noexcept {
  this->_rectangle.set_flip_horizontally(flip_horizontally);
}

[[nodiscard]] const bool& SpriteObject::get_flip_vertically() const noexcept {
  return this->_rectangle.get_flip_vertically();
}

[[nodiscard]] const bool& SpriteObject::get_flip_horizontally() const noexcept {
  return this->_rectangle.get_flip_horizontally();
}

void SpriteObject::notify_x() noexcept {
  this->_base_notify_xy();
}

void SpriteObject::notify_y() noexcept {
  this->_base_notify_xy();
}

void SpriteObject::notify_w() noexcept {
  this->_base_notify_wh();
}

void SpriteObject::notify_h() noexcept {
  this->_base_notify_wh();
}

[[nodiscard]] const fre2d::Rectangle& SpriteObject::get_rectangle() const noexcept {
  return this->_rectangle;
}

[[nodiscard]] fre2d::Rectangle& SpriteObject::get_rectangle_mutable() noexcept {
  return this->_rectangle;
}

void SpriteObject::_base_notify_xy() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_rectangle.set_position({this->get_x(), this->get_y()});
  }
}

void SpriteObject::_base_notify_wh() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_w(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_h(), 0.f)) {
    this->_rectangle.set_scale({this->get_w(), this->get_h(), 1.f});
  }
}
}  // namespace fresh