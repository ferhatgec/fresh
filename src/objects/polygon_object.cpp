// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/polygon_object.hpp>
#include <freshengine.hpp>
#include <algorithm>

namespace fresh {
PolygonObject::PolygonObject() {}

PolygonObject::PolygonObject(PolygonResource resource, ColorResource color)
    : _resource{std::move(resource)} {
  this->set_color(color);
}

PolygonObject::~PolygonObject() {
}

void PolygonObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(!fre2d::detail::nearly_equals(this->get_delta_x(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_y(), 0.f)) {
    this->_polygon.set_position({this->get_x(), this->get_y()});
  }
  if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
    this->_polygon.set_rotation(this->get_rotation());
  }
  if(!fre2d::detail::nearly_equals(this->get_delta_w(), 0.f) || !fre2d::detail::nearly_equals(this->get_delta_h(), 0.f)) {
    this->_polygon.set_scale({this->get_w(), this->get_h(), 1.f});
  }
  if(this->_visible) {
    this->_polygon.draw(this->_shader, FreshInstance->get_camera()->get_camera(), FreshInstance->get_light_manager());
  }
  this->apply_changes();
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
  this->init_shader(generic_shader_key);
  this->_initialized = true;
}

__idk_nodiscard PolygonResource& PolygonObject::get_polygon_resource() noexcept {
  return this->_resource;
}

__idk_nodiscard
ColorResource& PolygonObject::get_color_resource() noexcept {
  return this->_color;
}

/// FIXME: this is from SDL part of fresh, fre2d gives rotation support already.
void PolygonObject::set_rotation(idk::f32 rad_degrees) noexcept {
  if(f32_nearly_equals(this->_rotation_degrees, rad_degrees))
    return;
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  this->get_polygon_resource() = this->get_polygon_resource().rotate(this->_rotation_degrees);
}

void PolygonObject::set_flip_vertically(bool flip_vertically) noexcept {
  this->_polygon.set_flip_vertically(flip_vertically);
}

void PolygonObject::set_flip_horizontally(bool flip_horizontally) noexcept {
  this->_polygon.set_flip_horizontally(flip_horizontally);
}

[[nodiscard]] const bool& PolygonObject::get_flip_vertically() const noexcept {
  return this->_polygon.get_flip_vertically();
}

[[nodiscard]] const bool& PolygonObject::get_flip_horizontally() const noexcept {
  return this->_polygon.get_flip_horizontally();
}
} // namespace fresh