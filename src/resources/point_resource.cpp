#include <resources/point_resource.hpp>
#include <cmath>

namespace fresh {
PointResource::PointResource(idk::f32 x, idk::f32 y) noexcept
  : _x(x), _y(y) {
}

PointResource::~PointResource() {
}

__idk_nodiscard
idk::f32& PointResource::get_x() noexcept {
  return this->_x;
}

__idk_nodiscard
idk::f32& PointResource::get_y() noexcept {
  return this->_y;
}

__idk_nodiscard
idk::f32 PointResource::distance_from(const PointResource& point) noexcept {
  return sqrtf(powf(this->_x - point._x, 2.0f) + powf(this->_y - point._y, 2.0f));
}
} // namespace fresh