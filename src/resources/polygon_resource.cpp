#include <resources/polygon_resource.hpp>
#include <algorithm>
#include <iostream>

namespace fresh {
PolygonResource::PolygonResource(bool is_filled) noexcept
  : _is_filled{is_filled} {
}

void PolygonResource::push_polygon(PointResource&& polygon) noexcept {
  this->_polygons.push_back(std::move(polygon));
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

__idk_nodiscard
std::vector<PointResource>& PolygonResource::get_polygons() noexcept {
  return this->_polygons;
}

__idk_nodiscard
bool& PolygonResource::get_is_filled() noexcept {
  return this->_is_filled;
}

__idk_nodiscard
bool PolygonResource::is_point_in_polygon(const PointResource& point) const noexcept {
  return PolygonResource::_is_point_in_polygon(point._x, point._y);
}

__idk_nodiscard
bool PolygonResource::is_point_in_polygon(const SDL_FRect& point) const noexcept {
  return PolygonResource::_is_point_in_polygon(point.x, point.y);
}

__idk_nodiscard
idk::f32 PolygonResource::project(const PointResource& axis) const noexcept {
  if(this->_polygons.empty()) {
    std::cout << "Engine error: Polygon projection is failed due no polygon is available!\n";
    std::exit(1);
  }

  auto projection = this->project_min_max(axis);
  return std::get<ProjectionMax>(projection) - std::get<ProjectionMin>(projection);
}

__idk_nodiscard
std::tuple<idk::f32, idk::f32> PolygonResource::project_min_max(const PointResource& axis) const noexcept {
  idk::f32 min = std::numeric_limits<idk::f32>::max();
  idk::f32 max = std::numeric_limits<idk::f32>::min();

  for(std::size_t i = 0; i < this->_polygons.size(); ++i) {
    const auto& vert = this->_polygons[i];
    idk::f32 proj = vert.dot(axis);

    if(proj < min)
      min = proj;
    if(proj > max)
      max = proj;
  }
  return std::make_tuple(min, max);
}

__idk_nodiscard
PointResource PolygonResource::center() const noexcept {
  PointResource center(0.f, 0.f);
  if(this->_polygons.empty())
    return center;
  for(const auto& v: this->_polygons) {
    center = center + v;
  }
  return center * (1.f / this->_polygons.size());
}

__idk_nodiscard
PolygonResource PolygonResource::rotate(idk::f32 rad_degrees) const noexcept {
  PolygonResource vertices;
  vertices.get_polygons() = this->_polygons;
  auto center_point = vertices.center();

  for(auto& vert: vertices.get_polygons()) {
    vert = vert.rotate_by_radians_with_pivot(center_point, rad_degrees);
  }
  return vertices;
}

// Shoelace formula
__idk_nodiscard
idk::f32 PolygonResource::area() const noexcept {
  const auto& size = this->_polygons.size();
  idk::f32 area { 0.f };
  for(std::size_t i = 0; i < size; ++i) {
    const auto& vert_i = this->_polygons[i];
    const auto& vert_i_plus_1 = this->_polygons[(i + 1) % size];
    area += (vert_i._x * vert_i_plus_1._y) - (vert_i_plus_1._x * vert_i._y);
  }
  return fabsf(area) / 2.f;
}

__idk_nodiscard
bool PolygonResource::is_separating_axis_with(const PolygonResource& poly, const PointResource& axis) const noexcept {
  idk::f32 min_a = std::numeric_limits<idk::f32>::max(), max_a = std::numeric_limits<idk::f32>::lowest();
  idk::f32 min_b = std::numeric_limits<idk::f32>::max(), max_b = std::numeric_limits<idk::f32>::lowest();

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

// this uses even odd rule algorithm to find if given point is inside of the polygon (including corners)
__idk_nodiscard
bool PolygonResource::_is_point_in_polygon(const idk::f32& point_x, const idk::f32& point_y) const noexcept {
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