#include "point_resource.hpp"
#include <vector>
#include <array>
#include <types/predefined.hpp>

namespace fresh {
class PolygonResource {
public:
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
protected:
  std::vector<PointResource> _polygons;
  bool _is_filled;
};
} // namespace fresh