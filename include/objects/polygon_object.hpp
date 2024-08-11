#pragma once

#include "base_object.hpp"
#include <resources/polygon_resource.hpp>
#include <resources/color_resource.hpp>
#include <resources/edge_resource.hpp>

namespace fresh {
class PolygonObject : public BaseObject {
public:
  friend class FesLoaderResource;

  PolygonObject();
  PolygonObject(PolygonResource resource, ColorResource color);
  ~PolygonObject();

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "polygonobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  __idk_nodiscard
  PolygonResource& get_polygon_resource() noexcept;

  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;
private:
  void _draw_polygon() noexcept;
  void _draw_filled_polygon() noexcept;
  void _draw_unfilled_polygon() noexcept;
  void _build_edge_resource_table() noexcept;
protected:
  PolygonResource _resource;
  ColorResource _color;
  std::vector<EdgeResource> _edges, _active_edges;
};
} // namespace fresh