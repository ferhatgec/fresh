// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <cmath>
#include <types/predefined.hpp>

#include "edge_resource.hpp"
#include <format>

namespace fresh {
enum : idk::u8 {
  RedIndex,
  GreenIndex,
  BlueIndex,
  AlphaIndex // 3
};

class ColorResource {
public:
  constexpr explicit ColorResource(
    idk::f32 r = 0.f, idk::f32 g = 0.f, idk::f32 b = 0.f, idk::f32 a = 1.f
  ) noexcept : _r{r}, _g{g}, _b{b}, _a{a} {}

  constexpr ColorResource(
    glm::vec4 rgba
  ) noexcept : ColorResource(rgba.x, rgba.y, rgba.z, rgba.w) {}

  ~ColorResource() noexcept = default;

  [[nodiscard]] constexpr const idk::f32& get_red() const noexcept {
    return this->_r;
  }

  [[nodiscard]] constexpr const idk::f32& get_green() const noexcept {
    return this->_g;
  }

  [[nodiscard]] constexpr const idk::f32& get_blue() const noexcept {
    return this->_b;
  }

  [[nodiscard]] constexpr const idk::f32& get_alpha() const noexcept {
    return this->_a;
  }

  constexpr void set_red(idk::f32 red) noexcept {
    this->_r = fp_min(fp_abs(red), 1.f);
  }

  constexpr void set_green(idk::f32 green) noexcept {
    this->_g = fp_min(fp_abs(green), 1.f);
  }

  constexpr void set_blue(idk::f32 blue) noexcept {
    this->_b = fp_min(fp_abs(blue), 1.f);
  }

  constexpr void set_alpha(idk::f32 alpha) noexcept {
    this->_a = fp_min(fp_abs(alpha), 1.f);
  }

  friend std::ostream& operator<<(std::ostream& ostr, const ColorResource& color) noexcept {
    ostr << std::format("r, g, b, a = {}, {}, {}, {}", color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
    return ostr;
  }

  // TODO: compute HSV, CMYK, HSL values of RGBA; implement
  // seamless conversion between them
protected:
  friend class LabelObject;
  idk::f32 _r, _g, _b, _a;
};
} // namespace fresh