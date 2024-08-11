#include <resources/polygon_resource.hpp>
#include <algorithm>

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

  idk::f32 min = axis.dot(this->_polygons.front());
  idk::f32 max = min;

  for(std::size_t i = 1; i < this->_polygons.size(); ++i) {
    idk::f32 p = axis.dot(this->_polygons[i]);
    if(p < min)
      min = p;
    else if(p > max)
      max = p;
  }
  return max - min;
}

__idk_nodiscard
PointResource PolygonResource::center() const noexcept {
  PointResource center(0.f, 0.f);
  for(const auto& v: this->_polygons) {
    center = center + v;
  }
  return center * (1.f / this->_polygons.size());
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