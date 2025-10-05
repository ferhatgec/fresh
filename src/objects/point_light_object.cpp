// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/point_light_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
PointLightObject::PointLightObject() noexcept
  : _pt(
      glm::vec2{0.f, 0.f},
      fre2d::detail::point_light::default_ambient,
      fre2d::detail::point_light::default_diffuse,
      fre2d::detail::point_light::default_att_constant,
      fre2d::detail::point_light::default_att_linear,
      fre2d::detail::point_light::default_att_quadratic
    ), _lm_index{-1} {
  this->_pos_info = BBoxResource(this->_pt.get_position());
}

PointLightObject::PointLightObject(
  PointResource pos,
  glm::vec3 ambient,
  glm::vec3 diffuse,
  float constant,
  float linear,
  float quadratic
) noexcept
  : _pt(
      glm::vec2{pos.get_x(), pos.get_y()},
      ambient,
      diffuse,
      constant,
      linear,
      quadratic
  ), _lm_index{-1} {
  this->_pos_info = BBoxResource(this->_pt.get_position());
}

void PointLightObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes(this->_member_of_camera);
}

void PointLightObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout
        << "Engine [language] error: PointLightObject has no field named as '"
        << name.lexeme << "'.\n";
    std::exit(1);
  }
}

[[nodiscard]] fre2d::PointLight& PointLightObject::get_point_light() noexcept {
  return this->_pt;
}

[[nodiscard]] int PointLightObject::get_point_light_index() const noexcept {
  return this->_lm_index;
}

void PointLightObject::notify_x() noexcept {
  this->_base_notify_xy();
}

void PointLightObject::notify_y() noexcept {
  this->_base_notify_xy();
}

void PointLightObject::notify_disabled() noexcept {
  this->_pt.set_disabled(this->_disabled);
  FreshInstance->get_light_manager()->update_buffers();
}

void PointLightObject::notify_visible() noexcept {
  this->_pt.set_disabled(this->_disabled);
  FreshInstance->get_light_manager()->update_buffers();
}

void PointLightObject::_base_notify_xy() noexcept {
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_pt.set_position({this->get_x(), this->get_y()});
    FreshInstance->get_light_manager()->get_point_light_mutable(this->_lm_index) = this->get_point_light();
    FreshInstance->get_light_manager()->update_buffers();
  }
}

void PointLightObject::init_signal() noexcept {
  if(this->get_point_light_index() == -1) {
    this->_pt.set_position({this->get_x(), this->get_y()});
    FreshInstance->get_light_manager()->push_point_light(this->get_point_light());
    this->_lm_index = FreshInstance->get_light_manager()->get_point_lights().size() - 1;
  }
}
} // namespace fresh