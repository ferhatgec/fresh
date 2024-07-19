#include <resources/polygon_resource.hpp>

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
} // namespace fresh