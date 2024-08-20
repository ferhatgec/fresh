#include "freshengine.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <numbers>
#include <objects/base_object.hpp>
#include <resources/point_resource.hpp>
#include <resources/polygon_resource.hpp>

namespace fresh {
PointResource::PointResource(idk::f32 x, idk::f32 y) noexcept
    : _x{x}, _y{y}
{}

[[nodiscard]] PointResource PointResource::operator-(const PointResource& vec2d) const noexcept {
  return PointResource(this->_x - vec2d._x, this->_y - vec2d._y);
}

[[nodiscard]] PointResource PointResource::operator+(const PointResource& vec2d) const noexcept {
  return PointResource(this->_x + vec2d._x, this->_y + vec2d._y);
}

[[nodiscard]] PointResource PointResource::operator*(idk::f32 scalar) const noexcept {
  return PointResource(scalar * this->_x, scalar * this->_y);
}

PointResource PointResource::operator/(idk::f32 scalar) const noexcept {
  if(f32_nearly_equals(scalar, 0.f)) {
    std::cout << "Engine error: PointResource cannot get scalar ~= 0.f.\n";
    std::exit(1); // TODO: we need log functions, where error will just set _engine_running as false.
                       // then engine loop will break, later than nothing to worry about memory allocations.
                       // since RAII will do the magic.
  }
  return PointResource(this->_x / scalar, this->_y / scalar);
}


PointResource& PointResource::operator-=(const PointResource& vec2d) noexcept {
  *this = this->operator-(vec2d);
  return *this;
}

PointResource& PointResource::operator+=(const PointResource& vec2d) noexcept {
  *this = this->operator+(vec2d);
  return *this;
}

PointResource& PointResource::operator*=(idk::f32 scalar) noexcept {
  *this = this->operator*(scalar);
  return *this;
}

PointResource& PointResource::operator/=(idk::f32 scalar) noexcept {
  *this = this->operator/(scalar);
  return *this;
}

bool PointResource::operator==(const PointResource& rhs) noexcept {
  return f32_nearly_equals(this->_x, rhs._x) && f32_nearly_equals(this->_y, rhs._y);
}

bool PointResource::operator!=(const PointResource& rhs) noexcept {
  return !this->operator==(rhs);
}

[[nodiscard]] idk::f32 PointResource::dot(const PointResource& vec2d) const noexcept {
  return this->_x * vec2d._x + this->_y * vec2d._y;
}

[[nodiscard]] idk::f32 PointResource::cross(const PointResource& vec2d) const noexcept {
  return this->_x * vec2d._y - this->_y * vec2d._x;
}

[[nodiscard]] idk::f32 PointResource::length_squared() const noexcept {
  return this->_x * this->_x + this->_y * this->_y;
}

[[nodiscard]] idk::f32 PointResource::length() const noexcept {
  return this->_sqrt(this->length_squared());
}

[[nodiscard]] idk::f32 PointResource::magnitude() const noexcept {
  return this->length();
}

[[nodiscard]] PointResource PointResource::normalize() const noexcept {
  const idk::f32 vec_len = this->length();
  return PointResource(this->_x / vec_len, this->_y / vec_len);
}

[[nodiscard]] idk::f32 PointResource::distance_from(const PointResource& point) const noexcept {
  return this->operator-(point).length();
}

[[nodiscard]] idk::f32& PointResource::get_x() noexcept {
  return this->_x;
}

[[nodiscard]] idk::f32& PointResource::get_y() noexcept {
  return this->_y;
}

// 2d rotation matrix clockwise, theta as radian degrees:
// [x']    [cos(theta) sin(theta) ]   [x]
// [y']  = [-sin(theta) cos(theta)] * [y]
//
// by multiplicate right hand side, we get:
// x' = x * cos(theta) + y * sin(theta)
// y' = -x * sin(theta) + y * cos(theta)
//
// to rotate around a position, firstly substract your pivot, then use this function, and last, add your pivot.
// or just use PointResource::rotate_by_radians_with_pivot()
[[nodiscard]] PointResource PointResource::rotate_by_radians(idk::f32 rad_degrees) noexcept {
  // TODO: we might create an unordered_map, that caches cos and sin of given angles so we don't calculate it every single time.
  rad_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  return this->rotate_by_cs(
    Engine::get_instance()->cos(BaseObject::counter_clockwise_to_clockwise(rad_degrees)),
    Engine::get_instance()->sin(BaseObject::counter_clockwise_to_clockwise(rad_degrees))
    );
}

[[nodiscard]] PointResource PointResource::rotate_by_cs(idk::f32 c, idk::f32 s) noexcept {
  // we currently use atan(s, c) to convert given sin and cos to radian angle, but
  // box2d gives us cosine and sine values directly, so we can use that directly.
  return {
    this->_x * c + this->_y * s,
    -this->_x * s + this->_y * c
  };
}

[[nodiscard]] PointResource PointResource::rotate_by_radians_with_pivot(const PointResource& pivot, idk::f32 rad_degrees) noexcept {
  return (*this - pivot).rotate_by_radians(rad_degrees) + pivot;
}

[[nodiscard]] PointResource PointResource::rotate_by_cs_with_pivot(const PointResource& pivot, idk::f32 c, idk::f32 s) noexcept {
  return (*this - pivot).rotate_by_cs(c, s) + pivot;
}

[[nodiscard]]
PointResource PointResource::cross(const PointResource& vec2d, idk::f32 scalar) noexcept {
  return PointResource::cross(scalar, vec2d) * -1.f;
}

[[nodiscard]]
PointResource PointResource::cross(idk::f32 scalar, const PointResource& vec2d) noexcept {
  return PointResource(-scalar * vec2d._y, scalar * vec2d._x);
}

[[nodiscard]]
idk::f32 PointResource::cross(const PointResource& vec2d_1, const PointResource& vec2d_2) noexcept {
  return vec2d_1.cross(vec2d_2);
}

[[nodiscard]] idk::f32 PointResource::_sqrt_newton_raphson(idk::f32 x, idk::f32 curr, idk::f32 prev) const noexcept {
  return curr == prev ? curr : PointResource::_sqrt_newton_raphson(x, (curr + x / curr) / 2, curr);
}

[[nodiscard]] idk::f32 PointResource::_sqrt(idk::f32 x) const noexcept {
  if(x >= 0.f && x < std::numeric_limits<idk::f32>::infinity()) {
    std::cout << "Engine info: _sqrt(x) | x >= 0.f && x < inf fails.\n";
    return std::numeric_limits<idk::f32>::quiet_NaN();
  }
  return PointResource::_sqrt_newton_raphson(x, x, 0.f);
}
} // namespace fresh