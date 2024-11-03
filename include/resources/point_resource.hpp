#pragma once

#include <helper_funcs.hpp>
#include <numbers>
#include <render_objects.hpp>
#include <types/predefined.hpp>

namespace fresh {
template<std::floating_point Fp>
static constexpr Fp mul_2_pi_v = static_cast<Fp>(2) * std::numbers::pi_v<Fp>;

class PointResource {
 public:
  friend class PolygonResource;
  friend class AreaObject;

  constexpr PointResource(idk::f32 x = 0.0f, idk::f32 y = 0.0f) noexcept
      : _x{x}, _y{y} {}
  constexpr PointResource(PointResource&& res) = default;
  constexpr PointResource(const PointResource& res) = default;
  constexpr ~PointResource() = default;

  constexpr PointResource& operator=(PointResource&& rhs) = default;
  constexpr PointResource& operator=(const PointResource& rhs) = default;

  [[nodiscard]] constexpr PointResource operator-(
      const PointResource& vec2d) const noexcept {
    return {this->_x - vec2d._x, this->_y - vec2d._y};
  }

  [[nodiscard]] constexpr PointResource operator+(
      const PointResource& vec2d) const noexcept {
    return {this->_x + vec2d._x, this->_y + vec2d._y};
  }

  [[nodiscard]] constexpr PointResource operator*(
      idk::f32 scalar) const noexcept {
    return {scalar * this->_x, scalar * this->_y};
  }

  [[nodiscard]] constexpr PointResource operator/(idk::f32 scalar) const {
    if (fre2d::detail::nearly_equals(scalar, 0.f)) {
      throw std::logic_error("cannot divide PointResource by 0 (+- epsilon)");
    }
    return {this->_x / scalar, this->_y / scalar};
  }

  constexpr PointResource& operator-=(const PointResource& vec2d) noexcept {
    *this = this->operator-(vec2d);
    return *this;
  }

  constexpr PointResource& operator+=(const PointResource& vec2d) noexcept {
    *this = this->operator+(vec2d);
    return *this;
  }

  constexpr PointResource& operator*=(idk::f32 scalar) noexcept {
    *this = this->operator*(scalar);
    return *this;
  }

  constexpr PointResource& operator/=(idk::f32 scalar) {
    *this = this->operator/(scalar);
    return *this;
  }

  constexpr bool operator==(const PointResource& rhs) const noexcept {
    return fre2d::detail::nearly_equals(this->get_x(), rhs.get_x()) &&
           fre2d::detail::nearly_equals(this->get_y(), rhs.get_y());
  }

  constexpr bool operator!=(const PointResource& rhs) const noexcept {
    return !operator==(rhs);
  }

  [[nodiscard]] constexpr idk::f32 dot(
      const PointResource& vec2d) const noexcept {
    return this->_x * vec2d._x + this->_y * vec2d._y;
  }

  [[nodiscard]] constexpr idk::f32 cross(
      const PointResource& vec2d) const noexcept {
    return this->_x * vec2d._y - this->_y * vec2d._x;
  }

  [[nodiscard]] constexpr idk::f32 length_squared() const noexcept {
    return this->_x * this->_x + this->_y * this->_y;
  }

  [[nodiscard]] constexpr idk::f32 length() const noexcept {
    return PointResource::_sqrt(this->length_squared());
  }

  [[nodiscard]] constexpr idk::f32 magnitude() const noexcept {
    return this->length();
  }

  [[nodiscard]] constexpr PointResource normalize() const {
    return *this / this->length();
  }

  [[nodiscard]] constexpr idk::f32 distance_from(
      const PointResource& point) const noexcept {
    return this->operator-(point).length();
  }

  [[nodiscard]] constexpr const idk::f32& get_x() const noexcept {
    return this->_x;
  }

  [[nodiscard]] constexpr const idk::f32& get_y() const noexcept {
    return this->_y;
  }

  [[nodiscard]] constexpr const idk::f32& get_w() const noexcept {
    return this->get_x();
  }

  [[nodiscard]] constexpr const idk::f32& get_h() const noexcept {
    return this->get_y();
  }

  void set_x(idk::f32 x) noexcept { this->_x = x; }

  void set_y(idk::f32 y) noexcept { this->_y = y; }

  void set_w(idk::f32 w) noexcept { this->set_x(w); }

  void set_h(idk::f32 h) noexcept { this->set_y(h); }

  // 2d rotation matrix clockwise, theta as radian degrees:
  // [x']    [cos(theta) sin(theta) ]   [x]
  // [y']  = [-sin(theta) cos(theta)] * [y]
  //
  // by multiplicate right hand side, we get:
  // x' = x * cos(theta) + y * sin(theta)
  // y' = -x * sin(theta) + y * cos(theta)
  //
  // to rotate around a position, firstly substract your pivot, then use this
  // function, and last, add your pivot. or just use
  // PointResource::rotate_by_radians_with_pivot()
  [[nodiscard]] PointResource rotate_clockwise(idk::f32 rad_degrees) noexcept {
    rad_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
    return this->rotate_clockwise(PointResource::cos(-rad_degrees),
                                  PointResource::sin(-rad_degrees));
  }

  [[nodiscard]] PointResource rotate_clockwise(idk::f32 c,
                                               idk::f32 s) noexcept {
    return {this->_x * c + this->_y * s, -this->_x * s + this->_y * c};
  }

  [[nodiscard]] PointResource rotate_with_pivot_clockwise(
      const PointResource& pivot,
      idk::f32 rad_degrees) noexcept {
    return (*this - pivot).rotate_clockwise(rad_degrees) + pivot;
  }

  [[nodiscard]] PointResource rotate_with_pivot_clockwise(
      const PointResource& pivot,
      idk::f32 c,
      idk::f32 s) noexcept {
    return (*this - pivot).rotate_clockwise(c, s) + pivot;
  }

  [[nodiscard]] static constexpr PointResource cross(const PointResource& vec2d,
                                                     idk::f32 scalar) noexcept {
    return PointResource::cross(scalar, vec2d) * -1.f;
  }

  [[nodiscard]] static constexpr PointResource cross(
      idk::f32 scalar,
      const PointResource& vec2d) noexcept {
    return {-scalar * vec2d._y, scalar * vec2d._x};
  }

  [[nodiscard]] static constexpr idk::f32 cross(
      const PointResource& vec2d_1,
      const PointResource& vec2d_2) noexcept {
    return vec2d_1.cross(vec2d_2);
  }

  /// RenderObjects::sin(float) calculates sin() of given radian angle; then
  /// collects them in hashmap for fast lookups. this prevents unnecessary
  /// calculations.
  /// TODO: Engine class might not be good fit for this method.
  [[nodiscard]] static const idk::f32& sin(const idk::f32& rad_angle) noexcept {
    if (PointResource::_sin.contains(rad_angle)) {
      return PointResource::_sin[rad_angle];
    }
    PointResource::_sin[rad_angle] = std::sinf(rad_angle);
    return PointResource::_sin[rad_angle];
  }

  /// RenderObjects::cos(float) calculates cos() of given radian angle; then
  /// collects them in hashmap for fast lookups.
  /// TODO: Engine class might not be good fit for this method.
  [[nodiscard]] static const idk::f32& cos(const idk::f32& rad_angle) noexcept {
    if (PointResource::_cos.contains(rad_angle)) {
      return PointResource::_cos[rad_angle];
    }
    PointResource::_cos[rad_angle] = std::cosf(rad_angle);
    return PointResource::_cos[rad_angle];
  }

  /// PointResource::center_transform(PointResource, i32, i32) transforms given
  /// top left pivot coordinates into (window_width / 2, window_height / 2) as a
  /// pivot (0, 0) coordinates
  [[nodiscard]] static constexpr PointResource center_transform(
      const PointResource& box,
      idk::i32 window_width,
      idk::i32 window_height) noexcept {
    return {box.get_x(),
            box.get_y()};
  }

  /// PointResource::top_left_transform(PointResource, i32, i32) transforms
  /// given center pivot coordinates into top left as a pivot (0, 0) coordinates
  [[nodiscard]] static constexpr PointResource top_left_transform(
      const PointResource& box,
      idk::i32 window_width,
      idk::i32 window_height) noexcept {
    return {box.get_x() + static_cast<idk::f32>(window_width) / 2.f,
            static_cast<idk::f32>(window_height) / 2.f - box.get_y()};
  }

  static constexpr void check() noexcept;

  /// use custom equality checker as we compare floats; it should compare
  /// a range within +- epsilon so we can sure.
  static inline std::unordered_map<idk::f32,
                                   idk::f32,
                                   std::hash<idk::f32>,
                                   decltype([](const idk::f32& lhs,
                                               const idk::f32& rhs) -> bool {
                                     return fre2d::detail::nearly_equals(lhs,
                                                                         rhs);
                                   })>
      _sin;

  static inline std::unordered_map<idk::f32,
                                   idk::f32,
                                   std::hash<idk::f32>,
                                   decltype([](const idk::f32& lhs,
                                               const idk::f32& rhs) -> bool {
                                     return fre2d::detail::nearly_equals(lhs,
                                                                         rhs);
                                   })>
      _cos;

 private:
  [[nodiscard]] static constexpr idk::f32
  _sqrt_newton_raphson(idk::f32 x, idk::f32 curr, idk::f32 prev) noexcept {
    return curr == prev ? curr
                        : PointResource::_sqrt_newton_raphson(
                              x, (curr + x / curr) / 2.f, curr);
  }

  [[nodiscard]] static constexpr idk::f32 _sqrt(idk::f32 x) noexcept {
    if (x < 0.f) [[unlikely]] {
      return -1.f;
    }
    return PointResource::_sqrt_newton_raphson(x, x, 0.f);
  }

 protected:
  idk::f32 _x, _y;
};

constexpr void PointResource::check() noexcept {
}

using Vector2 = PointResource;
} // namespace fresh