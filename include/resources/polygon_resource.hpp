#pragma once

#include "point_resource.hpp"

#include <SDL_rect.h>
#include <array>
#include <types/predefined.hpp>
#include <vector>

namespace fresh {
__idk_nodiscard
inline bool f32_nearly_equals(const idk::f32 a, const idk::f32 b, const idk::f32 epsilon = 1e-6) noexcept {
  return a + epsilon >= b && a - epsilon <= b;
}

class PolygonResource {
public:
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
  PointResource center() const noexcept;

  __idk_nodiscard
  bool is_separating_axis_with(const PolygonResource& poly, const PointResource& axis) const noexcept;
private:
  __idk_nodiscard
  bool _is_point_in_polygon(const idk::f32& point_x, const idk::f32& point_y) const noexcept;
protected:
  std::vector<PointResource> _polygons;
  bool _is_filled;
};
} // namespace fresh