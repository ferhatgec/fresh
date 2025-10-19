// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <format>
#include <types/predefined.hpp>
#include <helper_funcs.hpp>

namespace fresh {
/// BBoxResource stores x, y, w, h values with operator overloading support.
class PointResource;
class BBoxResource {
public:
  constexpr BBoxResource(
    idk::f32 x = 0.f,
    idk::f32 y = 0.f,
    idk::f32 w = 0.f,
    idk::f32 h = 0.f
  ) noexcept : _x{x}, _y{y}, _w{w}, _h{h}
  {}

  constexpr BBoxResource(glm::vec2 pos, glm::vec2 size = glm::vec2 { 0.f, 0.f }) noexcept
      : _x{pos.x}, _y{pos.y}, _w{size.x}, _h{size.y}
  {}

  constexpr BBoxResource(glm::vec4 pos_size) noexcept
      : BBoxResource(glm::vec2 { pos_size.x, pos_size.y }, glm::vec2 { pos_size.z, pos_size.w})
  {}

  ~BBoxResource() = default;

  [[nodiscard]] constexpr const idk::f32& get_x() const noexcept {
    return this->_x;
  }

  [[nodiscard]] constexpr const idk::f32& get_y() const noexcept {
    return this->_y;
  }

  [[nodiscard]] constexpr const idk::f32& get_w() const noexcept {
    return this->_w;
  }

  [[nodiscard]] constexpr const idk::f32& get_h() const noexcept {
    return this->_h;
  }

  constexpr void set_x(idk::f32 x) noexcept {
    this->_x = x;
  }

  constexpr void set_y(idk::f32 y) noexcept {
    this->_y = y;
  }

  constexpr void set_w(idk::f32 w) noexcept {
    this->_w = w;
  }

  constexpr void set_h(idk::f32 h) noexcept {
    this->_h = h;
  }

  friend constexpr BBoxResource operator+(const BBoxResource& lhs, const BBoxResource& rhs) noexcept {
    return {
    lhs.get_x() + rhs.get_x(),
      lhs.get_y() + rhs.get_y(),
      lhs.get_w() + rhs.get_w(),
      lhs.get_h() + rhs.get_h()
    };
  }

  friend constexpr BBoxResource operator*(const BBoxResource& lhs, const BBoxResource& rhs) noexcept {
    return {
      lhs.get_x() * rhs.get_x(),
        lhs.get_y() * rhs.get_y(),
        lhs.get_w() * rhs.get_w(),
        lhs.get_h() * rhs.get_h()
      };
  }

  friend constexpr BBoxResource operator/(const BBoxResource& lhs, const BBoxResource& rhs) {
    if(fre2d::detail::nearly_equals(rhs.get_x(), 0.f) ||
       fre2d::detail::nearly_equals(rhs.get_y(), 0.f) ||
       fre2d::detail::nearly_equals(rhs.get_w(), 0.f) ||
       fre2d::detail::nearly_equals(rhs.get_h(), 0.f)) {
      throw std::exception("cannot divide by 0");
    }
    return {
      lhs.get_x() / rhs.get_x(),
        lhs.get_y() / rhs.get_y(),
        lhs.get_w() / rhs.get_w(),
        lhs.get_h() / rhs.get_h()
      };
  }

  constexpr BBoxResource& operator+=(const BBoxResource& rhs) noexcept {
    *this = *this + rhs;
    return *this;
  }

  friend constexpr BBoxResource operator-(const BBoxResource& lhs, const BBoxResource& rhs) noexcept {
    return {
    lhs.get_x() - rhs.get_x(),
      lhs.get_y() - rhs.get_y(),
      lhs.get_w() - rhs.get_w(),
      lhs.get_h() - rhs.get_h()
    };
  }

  constexpr BBoxResource& operator-=(const BBoxResource& rhs) noexcept {
    *this = *this - rhs;
    return *this;
  }

  friend constexpr bool operator==(const BBoxResource& lhs, const BBoxResource& rhs) noexcept {
    return fre2d::detail::nearly_equals(lhs.get_x(), rhs.get_x()) &&
      fre2d::detail::nearly_equals(lhs.get_y(), rhs.get_y()) &&
      fre2d::detail::nearly_equals(lhs.get_w(), rhs.get_w()) &&
      fre2d::detail::nearly_equals(lhs.get_h(), rhs.get_h());
  }

  friend constexpr bool operator!=(const BBoxResource& lhs, const BBoxResource& rhs) noexcept {
    return !operator==(lhs, rhs);
  }

  friend constexpr bool operator==(const BBoxResource& lhs, idk::f32 rhs) noexcept {
    return lhs == BBoxResource{rhs, rhs, rhs, rhs};
  }

  friend constexpr bool operator!=(const BBoxResource& lhs, idk::f32 rhs) noexcept {
    return !operator==(lhs, rhs);
  }

  friend std::ostream& operator<<(std::ostream& ostr, const BBoxResource& res) noexcept {
    return ostr << std::format("x, y, w, h = {}, {}, {}, {}", res.get_x(), res.get_y(), res.get_w(), res.get_h());;
  }
private:
  idk::f32 _x, _y, _w, _h;
};
} // namespace fresh