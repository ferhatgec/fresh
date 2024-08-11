#include <resources/point_resource.hpp>
#include <cmath>

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