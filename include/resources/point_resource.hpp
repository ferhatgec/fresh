#pragma once

#include <types/predefined.hpp>
#include <limits>
#include <iostream>

namespace fresh {
// no constexpr right at the moment, needs compile time sqrt (achievable using Newton-Raphson method)
// and control over getters and setters.
class PointResource {
public:
  friend class PolygonResource;
  friend class AreaObject;

  explicit PointResource(idk::f32 x = 0.0f, idk::f32 y = 0.0f) noexcept;
  ~PointResource() = default;

  [[nodiscard]] PointResource operator-(const PointResource& vec2d) const noexcept;
  [[nodiscard]] PointResource operator+(const PointResource& vec2d) const noexcept;
  [[nodiscard]] PointResource operator*(idk::f32 scalar) const noexcept;

  [[nodiscard]] idk::f32 dot(const PointResource& vec2d) const noexcept;
  [[nodiscard]] idk::f32 cross(const PointResource& vec2d) const noexcept;
  [[nodiscard]] idk::f32 length_squared() const noexcept;
  [[nodiscard]] idk::f32 length() const noexcept;
  [[nodiscard]] PointResource normalize() const noexcept;
  [[nodiscard]] idk::f32 distance_from(const PointResource& point) const noexcept;

  [[nodiscard]] idk::f32& get_x() noexcept;
  [[nodiscard]] idk::f32& get_y() noexcept;
private:
  [[nodiscard]] idk::f32 _sqrt_newton_raphson(idk::f32 x, idk::f32 curr, idk::f32 prev) const noexcept;
  [[nodiscard]] idk::f32 _sqrt(idk::f32 x) const noexcept;
protected:
  idk::f32 _x, _y;
};
} // namespace fresh