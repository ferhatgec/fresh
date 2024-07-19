#pragma once

#include <types/predefined.hpp>

namespace fresh {
class EdgeResource {
public:
  EdgeResource(idk::f32 y1, idk::f32 y2, idk::f32 x1, idk::f32 x2) noexcept;
  ~EdgeResource() = default;

  __idk_nodiscard
  idk::f32& get_y_min() noexcept;

  __idk_nodiscard
  idk::f32& get_y_max() noexcept;

  __idk_nodiscard
  idk::f32& get_x_min() noexcept;

  __idk_nodiscard
  idk::f32& get_slope() noexcept;
protected:
  idk::f32 _y_min, _y_max, _x_min, _slope;
};
} // namespace fresh