#pragma once

#include <types/predefined.hpp>

namespace fresh {
// no constexpr right at the moment, needs compile time sqrt (achievable using Newton-Raphson method)
// and control over getters and setters.
class PointResource {
public:
  friend class PolygonResource;
  friend class AreaObject;

  PointResource(idk::f32 x = 0.0f, idk::f32 y = 0.0f) noexcept;
  PointResource(PointResource&& res) = default;
  PointResource(const PointResource& res) = default;
  ~PointResource() = default;

  PointResource& operator=(PointResource&& rhs) = default;
  PointResource& operator=(const PointResource& rhs) = default;

  [[nodiscard]] PointResource operator-(const PointResource& vec2d) const noexcept;
  [[nodiscard]] PointResource operator+(const PointResource& vec2d) const noexcept;
  [[nodiscard]] PointResource operator*(idk::f32 scalar) const noexcept;
  [[nodiscard]] PointResource operator/(idk::f32 scalar) const noexcept;

  PointResource& operator-=(const PointResource& vec2d) noexcept;
  PointResource& operator+=(const PointResource& vec2d) noexcept;
  PointResource& operator*=(idk::f32 scalar) noexcept;
  PointResource& operator/=(idk::f32 scalar) noexcept;

  bool operator==(const PointResource& rhs) noexcept;
  bool operator!=(const PointResource& rhs) noexcept;

  [[nodiscard]] idk::f32 dot(const PointResource& vec2d) const noexcept;
  [[nodiscard]] idk::f32 cross(const PointResource& vec2d) const noexcept;
  [[nodiscard]] idk::f32 length_squared() const noexcept;
  [[nodiscard]] idk::f32 length() const noexcept;
  [[nodiscard]] idk::f32 magnitude() const noexcept;
  [[nodiscard]] PointResource normalize() const noexcept;
  [[nodiscard]] idk::f32 distance_from(const PointResource& point) const noexcept;

  [[nodiscard]] idk::f32& get_x() noexcept;
  [[nodiscard]] idk::f32& get_y() noexcept;

  [[nodiscard]] PointResource rotate_by_radians /* clockwise */(idk::f32 rad_degrees) noexcept;
  [[nodiscard]] PointResource rotate_by_cs /* clockwise */(idk::f32 c, idk::f32 s) noexcept;

  [[nodiscard]] PointResource rotate_by_radians_with_pivot /* clockwise */(const PointResource& pivot, idk::f32 rad_degrees) noexcept;
  [[nodiscard]] PointResource rotate_by_cs_with_pivot /* clockwise */(const PointResource& pivot, idk::f32 c, idk::f32 s) noexcept;

  [[nodiscard]] static PointResource cross(const PointResource& vec2d, idk::f32 scalar) noexcept;
  [[nodiscard]] static PointResource cross(idk::f32 scalar, const PointResource& vec2d) noexcept;
  [[nodiscard]] static idk::f32 cross(const PointResource& vec2d_1, const PointResource& vec2d_2) noexcept;
private:
  [[nodiscard]] idk::f32 _sqrt_newton_raphson(idk::f32 x, idk::f32 curr, idk::f32 prev) const noexcept;
  [[nodiscard]] idk::f32 _sqrt(idk::f32 x) const noexcept;
protected:
  idk::f32 _x, _y;
};

using Vector2 = PointResource;
} // namespace fresh