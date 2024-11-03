#include <cmath>
#include <iostream>
#include <log/log.hpp>
#include <resources/circle_resource.hpp>
#include <helper_funcs.hpp>

namespace fresh {
CircleResource::CircleResource(
  idk::f32 radius,
  idk::f32 thickness,
  bool is_filled
) noexcept {
  this->set_thickness(thickness);
  this->set_filled(is_filled);
}

[[nodiscard]] const idk::f32& CircleResource::get_radius() const noexcept {
  return this->_radius;
}

[[nodiscard]] const bool& CircleResource::get_filled() const noexcept {
  return this->_is_filled;
}

[[nodiscard]] const idk::f32& CircleResource::get_thickness() const noexcept {
  return this->_thickness;
}

void CircleResource::set_radius(idk::f32 radius) noexcept {
  if(radius < 0.f) {
    log_warning(src(), "radius must be greater than or equal to 0. got: '{}'", radius);
  }
  this->_radius = fabsf(radius);
}

void CircleResource::set_thickness(idk::f32 thickness) noexcept {
  if(thickness < 0.f) {
    log_warning(src(), "thickness cannot be less than 0. got: '{}'", thickness);
    this->_thickness = 0.f;
    return;
  }
  if(thickness > 1.f) {
    log_warning(src(), "thickness cannot be greater than 1. got: '{}'", thickness);
    this->_thickness = 1.f;
    return;
  }
  this->_thickness = thickness;
}

void CircleResource::set_filled(bool filled) noexcept {
  this->_is_filled = filled;
}
} // namespace fresh