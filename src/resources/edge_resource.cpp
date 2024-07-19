#include <resources/edge_resource.hpp>
#include <cmath>

namespace fresh {
EdgeResource::EdgeResource(idk::f32 y1, idk::f32 y2, idk::f32 x1, idk::f32 x2) noexcept
  : _y_min{std::fmin(y1, y2)}, _y_max{std::fmax(y1, y2)} {
  if(y1 < y2) {
    this->_x_min = x1;
    this->_slope = (x2 - x1) / (y2 - y1);
  } else {
    this->_x_min = x2;
    this->_slope = (x1 - x2) / (y1 - y2);
  }
}

__idk_nodiscard
idk::f32& EdgeResource::get_y_min() noexcept {
  return this->_y_min;
}

__idk_nodiscard
idk::f32& EdgeResource::get_y_max() noexcept {
  return this->_y_max;
}

__idk_nodiscard
idk::f32& EdgeResource::get_x_min() noexcept {
  return this->_x_min;
}

__idk_nodiscard
idk::f32& EdgeResource::get_slope() noexcept {
  return this->_slope;
}
} // namespace fresh