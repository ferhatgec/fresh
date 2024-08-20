#pragma once

#include "point_resource.hpp"

#include <SDL_rect.h>
#include <types/predefined.hpp>
#include <vector>
#include <tuple>
#include <limits>

namespace fresh {
__idk_nodiscard
inline bool f32_nearly_equals(const idk::f32 a, const idk::f32 b, const idk::f32& epsilon = std::numeric_limits<idk::f32>::epsilon()) noexcept {
  return a + epsilon >= b && a - epsilon <= b;
}

// for now, no support for concaves.
class PolygonResource {
public:
  enum : std::uint8_t {
    ProjectionMin,
    ProjectionMax
  };

  friend class AreaObject;

  PolygonResource(bool is_filled = false) noexcept;
  ~PolygonResource() = default;

  void push_polygon(PointResource&& polygon) noexcept;
  void push_polygon(idk::f32 x, idk::f32 y) noexcept;

  void push_polygons(std::initializer_list<std::pair<idk::f32, idk::f32>> polygons) noexcept;

  void delete_all_polygons() noexcept;

  __idk_nodiscard
  std::vector<PointResource>& get_polygons() noexcept;

  __idk_nodiscard
  bool& get_is_filled() noexcept;

  __idk_nodiscard
  bool is_point_in_polygon(const PointResource& point) const noexcept;

  __idk_nodiscard
  bool is_point_in_polygon(const SDL_FRect& point) const noexcept;

  __idk_nodiscard
  idk::f32 project(const PointResource& axis) const noexcept;

  __idk_nodiscard
  std::tuple<idk::f32, idk::f32> project_min_max(const PointResource& axis) const noexcept;

  __idk_nodiscard
  PointResource center() const noexcept; // TODO: we need getters and setters, calculating center only when polygons are changed.

  __idk_nodiscard
  PolygonResource rotate(idk::f32 rad_degrees) const noexcept;

  __idk_nodiscard
  bool is_separating_axis_with(const PolygonResource& poly, const PointResource& axis) const noexcept;

  __idk_nodiscard
  idk::f32 area() const noexcept;
private:
  __idk_nodiscard
  bool _is_point_in_polygon(const idk::f32& point_x, const idk::f32& point_y) const noexcept;
protected:
  std::vector<PointResource> _polygons;
  bool _is_filled;
};
} // namespace fresh