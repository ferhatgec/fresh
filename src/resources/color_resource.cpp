#include <resources/color_resource.hpp>
#include <cmath>

namespace fresh {
ColorResource::ColorResource(idk::u8 r, idk::u8 g, idk::u8 b, idk::u8 a) noexcept
  : _r(r), _g(g), _b(b), _a(a) {
}

ColorResource::~ColorResource() {
}

__idk_nodiscard
idk::u8& ColorResource::get_red() noexcept {
  return this->_r;
}

__idk_nodiscard
idk::u8& ColorResource::get_green() noexcept {
  return this->_g;
}

__idk_nodiscard
idk::u8& ColorResource::get_blue() noexcept {
  return this->_b;
}

__idk_nodiscard
idk::u8& ColorResource::get_alpha() noexcept {
  return this->_a;
}
} // namespace fresh