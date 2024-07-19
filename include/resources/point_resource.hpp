#pragma once

#include <types/predefined.hpp>

namespace fresh {
class PointResource {
public:
  PointResource(idk::f32 x = 0.0f, idk::f32 y = 0.0f) noexcept;
  ~PointResource();

  __idk_nodiscard
  idk::f32& get_x() noexcept;

  __idk_nodiscard
  idk::f32& get_y() noexcept;

  __idk_nodiscard
  idk::f32 distance_from(const PointResource& point) noexcept;
protected:
  idk::f32 _x, _y;
};
} // namespace fresh