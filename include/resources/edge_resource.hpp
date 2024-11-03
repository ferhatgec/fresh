#pragma once

#include <types/predefined.hpp>
#include <helper_funcs.hpp>

namespace fresh {
template<std::floating_point Fp>
constexpr const Fp& fp_min(const Fp& y1, const Fp& y2) noexcept {
  if(y1 > y2) {
    return y2;
  }
  return y1;
}

template<std::floating_point Fp>
constexpr const Fp& fp_max(const Fp& y1, const Fp& y2) noexcept {
  if(y1 < y2) {
    return y2;
  }
  return y1;
}

template<std::floating_point Fp>
constexpr Fp fp_abs(const Fp& y1) noexcept {
  if(y1 > static_cast<Fp>(0)
    || fre2d::detail::nearly_equals(y1, static_cast<Fp>(0))) {
    return y1;
  }
  return -y1;
}

class EdgeResource {
public:
  constexpr EdgeResource(idk::f32 y1, idk::f32 y2, idk::f32 x1, idk::f32 x2) noexcept {
    this->init(y1, y2, x1, x2);
  }

  constexpr ~EdgeResource() = default;

  constexpr void init(idk::f32 y1, idk::f32 y2, idk::f32 x1, idk::f32 x2) noexcept {
    this->_y_min = fp_min(y1, y2);
    this->_y_max = fp_max(y1, y2);
    if(y1 < y2) {
      this->_x_min = x1;
      this->_slope = (x2 - x1) / (y2 - y1);
    } else {
      this->_x_min = x2;
      this->_slope = (x1 - x2) / (y1 - y2);
    }
  }

  [[nodiscard]] constexpr const idk::f32& get_y_min() const noexcept {
    return this->_y_min;
  }

  [[nodiscard]] constexpr const idk::f32& get_y_max() const noexcept {
    return this->_y_max;
  }

  [[nodiscard]] constexpr const idk::f32& get_x_min() const noexcept {
    return this->_x_min;
  }

  [[nodiscard]] constexpr const idk::f32& get_slope() const noexcept {
    return this->_slope;
  }
protected:
  idk::f32 _y_min, _y_max, _x_min, _slope;
};
} // namespace fresh