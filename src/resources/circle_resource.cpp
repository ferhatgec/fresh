#include <resources/circle_resource.hpp>
#include <cmath>
#include <iostream>

namespace fresh {
CircleResource::CircleResource(idk::f32 radius, idk::i32 segments, bool is_filled) noexcept {
  if(radius < 0.f)
    std::cout << "Engine warning: CircleResource radius must be equal or greater than 0.";
  if(segments <= 0.f)
    std::cout << "Engine warning: CircleResource segments must be greater than 0.";
  this->_radius = fabsf(radius);
  this->_segments = abs(segments);
  this->_is_filled = is_filled;
}

CircleResource::~CircleResource() noexcept {
}

__idk_nodiscard
idk::f32& CircleResource::get_radius() noexcept {
  return this->_radius;
}

__idk_nodiscard
idk::i32& CircleResource::get_segments() noexcept {
  return this->_segments;
}

__idk_nodiscard
bool& CircleResource::get_is_filled() noexcept {
  return this->_is_filled;
}
} // namespace fresh