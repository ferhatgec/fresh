// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <algorithm>
#include <iostream>
#include <resources/polygon_resource.hpp>

#include "log/log.hpp"

namespace fresh {
PolygonResource::PolygonResource(bool is_filled) noexcept
    : _is_filled{is_filled} {}

PolygonResource::PolygonResource(const std::vector<PointResource>& vertices,
                                 bool is_filled) noexcept {
  this->_polygons = vertices;
  this->_is_filled = is_filled;
}

void PolygonResource::push_polygon(const PointResource& polygon) noexcept {
  this->_polygons.push_back(polygon);
}

void PolygonResource::push_polygon(idk::f32 x, idk::f32 y) noexcept {
  this->_polygons.emplace_back(x, y);
}

void PolygonResource::push_polygons(std::initializer_list<std::pair<idk::f32, idk::f32>> polygons) noexcept {
  for(const auto& [x, y]: polygons) {
    this->_polygons.emplace_back(x, y);
  }
}

void PolygonResource::delete_all_polygons() noexcept {
  this->_polygons.clear();
}

[[nodiscard]] std::vector<PointResource>& PolygonResource::get_polygons() noexcept {
  return this->_polygons;
}

[[nodiscard]] const bool& PolygonResource::get_filled() const noexcept {
  return this->_is_filled;
}

[[nodiscard]] bool PolygonResource::point_in_polygon(const PointResource& point) const noexcept {
  return PolygonResource::_is_point_in_polygon(point._x, point._y);
}

[[nodiscard]] bool PolygonResource::point_in_polygon(const BBoxResource& point) const noexcept {
  return PolygonResource::_is_point_in_polygon(point.get_x(), point.get_y());
}

[[nodiscard]] idk::f32 PolygonResource::project(const PointResource& axis) const noexcept {
  if(this->_polygons.empty()) {
    log_warning(src(), "polygon projection is not possible since no vertex is assigned to it.");
    return 0.f;
  }
  const auto& projection = this->project_min_max(axis);
  return std::get<ProjectionMax>(projection) - std::get<ProjectionMin>(projection);
}

[[nodiscard]] std::tuple<idk::f32, idk::f32> PolygonResource::project_min_max(const PointResource& axis) const noexcept {
  idk::f32 min = std::numeric_limits<idk::f32>::max();
  idk::f32 max = std::numeric_limits<idk::f32>::min();
  for(const auto& vert : this->_polygons) {
    const auto& proj = vert.dot(axis);
    if(proj < min) {
      min = proj;
    }
    if(proj > max) {
      max = proj;
    }
  }
  return std::make_tuple(min, max);
}

[[nodiscard]] PointResource PolygonResource::center() const noexcept {
  PointResource center(0.f, 0.f);
  if(this->_polygons.empty()) {
    return center;
  }
  for(const auto& v: this->_polygons) {
    center = center + v;
  }
  return center * (1.f / static_cast<idk::f32>(this->_polygons.size()));
}

[[nodiscard]] PolygonResource PolygonResource::rotate(idk::f32 rad_degrees) const noexcept {
  PolygonResource vertices(this->_polygons);
  const auto& center_point = vertices.center();
  for(auto& vert: vertices.get_polygons()) {
    vert = vert.rotate_with_pivot_clockwise(center_point, rad_degrees);
  }
  return vertices;
}

// Shoelace formula
[[nodiscard]] idk::f32 PolygonResource::area() const noexcept {
  const auto& size = this->_polygons.size();
  idk::f32 area { 0.f };
  for(std::size_t i = 0; i < size; ++i) {
    const auto& vert_i = this->_polygons[i];
    const auto& vert_i_plus_1 = this->_polygons[(i + 1) % size];
    area += (vert_i._x * vert_i_plus_1._y) - (vert_i_plus_1._x * vert_i._y);
  }
  return fabsf(area) / 2.f;
}

[[nodiscard]] bool PolygonResource::separating_axis_with(const PolygonResource& poly, const PointResource& axis) const noexcept {
  auto min_a = std::numeric_limits<idk::f32>::max();
  auto max_a = std::numeric_limits<idk::f32>::lowest();
  auto min_b = std::numeric_limits<idk::f32>::max();
  auto max_b = std::numeric_limits<idk::f32>::lowest();
  for(const auto& point : this->_polygons) {
    const idk::f32 projection = point.dot(axis);
    min_a = std::min(min_a, projection);
    max_a = std::max(max_a, projection);
  }
  for(const auto& point: poly._polygons) {
    const idk::f32 projection = point.dot(axis);
    min_b = std::min(min_b, projection);
    max_b = std::max(max_b, projection);
  }
  return max_a < min_b || max_b < min_a;
}

// this uses even odd rule algorithm to find if given point is inside the polygon (including corners)
[[nodiscard]] bool PolygonResource::_is_point_in_polygon(const idk::f32& point_x, const idk::f32& point_y) const noexcept {
  bool inside { false };
  const auto polygon_size = this->_polygons.size();

  for(std::size_t i = 0; i < polygon_size; ++i) {
    const auto& current_vertex = this->_polygons[i];
    const auto& previous_vertex = this->_polygons[(i - 1 + polygon_size) % polygon_size];

    if(point_x == current_vertex._x && point_y == current_vertex._y)
      return true;

    if((current_vertex._y > point_y) != (previous_vertex._y > point_y)) {
      const idk::f32 slope = (point_x - current_vertex._x) * (previous_vertex._y - current_vertex._y) -
                              (previous_vertex._x - current_vertex._x) * (point_y - current_vertex._y);

      if(f32_nearly_equals(fabsf(slope), 0.f))
        return true;

      if(slope < 0.f != (previous_vertex._y < current_vertex._y)) {
        inside = !inside;
      }
    }
  }
  return inside;
}
} // namespace fresh