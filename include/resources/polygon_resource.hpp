#pragma once

#include "point_resource.hpp"
#include "bbox_resource.hpp"

#include <limits>
#include <tuple>
#include <types/predefined.hpp>
#include <vector>

namespace fresh {
__idk_nodiscard
inline bool f32_nearly_equals(const idk::f32& a, const idk::f32& b, const idk::f32& epsilon = std::numeric_limits<idk::f32>::epsilon()) noexcept {
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

  explicit PolygonResource(bool is_filled = false) noexcept;
  explicit PolygonResource(const std::vector<PointResource>& vertices, bool is_filled = false) noexcept;
  ~PolygonResource() = default;

  /// PolygonResource::push_polygon(PointResource) pushes PointResource
  /// into list counter-clockwise.
  void push_polygon(const PointResource& polygon) noexcept;

  /// PolygonResource::push_polygon(float, float) pushes PointResource into list
  /// counter-clockwise; creates PointResource in-place.
  void push_polygon(idk::f32 x, idk::f32 y) noexcept;

  /// PolygonResource::push_polygon(std::initializer_list<std::pair<float, float>>)
  /// pushes multiple pairs of (float, float) into list counter-clockwise.
  void push_polygons(std::initializer_list<std::pair<idk::f32, idk::f32>> polygons) noexcept;

  /// PolygonResource::delete_all_polygons() removes every element from list.
  /// (at least you cannot access them after)
  void delete_all_polygons() noexcept;

  /// PolygonResource::get_polygons() returns current list reference.
  [[nodiscard]] std::vector<PointResource>& get_polygons() noexcept;

  /// PolygonResource::get_filled() is read-only access to _is_filled property.
  [[nodiscard]] const bool& get_filled() const noexcept;

  /// PolygonResource::point_in_polygon(PointResource) checks if given point
  /// is inside the polygon.
  [[nodiscard]] bool point_in_polygon(const PointResource& point) const noexcept;

  /// PolygonResource::point_in_polygon(BBoxResource) checks if given point
  /// is inside the polygon.
  [[nodiscard]] bool point_in_polygon(const BBoxResource& point) const noexcept;

  /// PolygonResource::project(PointResource) projects current polygon on the
  /// axis.
  [[nodiscard]] idk::f32 project(const PointResource& axis) const noexcept;

  /// PolygonResource::project_min_max(PointResource) projects current polygon on the
  /// axis; and returns minimum and maximum values.
  [[nodiscard]] std::tuple<idk::f32, idk::f32> project_min_max(const PointResource& axis) const noexcept;

  /// PolygonResource::center() calculates center of current polygon.
  /// TODO: we need to cache it to reduce unnecessary operations.
  [[nodiscard]] PointResource center() const noexcept;

  /// PolygonResource::rotate(float) rotates current polygon by its center.
  [[nodiscard]] PolygonResource rotate(idk::f32 rad_degrees) const noexcept;

  /// PolygonResource::separating_axis_with(PolygonResource, PointResource)
  /// does SAT collision test on it.
  [[nodiscard]] bool separating_axis_with(const PolygonResource& poly, const PointResource& axis) const noexcept;

  /// PolygonResource::area() calculates area of current polygon.
  /// TODO: we need to cache it to reduce unnecessary operations.
  [[nodiscard]] idk::f32 area() const noexcept;
private:
  [[nodiscard]] bool _is_point_in_polygon(const idk::f32& point_x, const idk::f32& point_y) const noexcept;
protected:
  std::vector<PointResource> _polygons;
  bool _is_filled;
};
} // namespace fresh