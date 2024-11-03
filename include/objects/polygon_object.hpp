#pragma once

#include <resources/color_resource.hpp>
#include <resources/edge_resource.hpp>
#include <resources/polygon_resource.hpp>
#include "base_object.hpp"

#include "polygon.hpp"

namespace fresh {
class PolygonObject : public BaseObject {
public:
  friend class FesLoaderResource;
  friend class RectangleObject;

  PolygonObject();
  PolygonObject(PolygonResource resource, ColorResource color);
  ~PolygonObject();

  void
  sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "polygonobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;

  __idk_nodiscard
  PolygonResource& get_polygon_resource() noexcept;

  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;

  void set_rotation(idk::f32 rad_degrees) noexcept override;
private:
  void _draw_polygon() noexcept;
  void _draw_filled_polygon() noexcept;
  void _draw_unfilled_polygon() noexcept;
  void _add_render_objects() noexcept;
  void _sub_render_objects() noexcept;
protected:
  PolygonResource _resource;
  ColorResource _color;
  fre2d::Polygon _polygon;
  fre2d::Shader _shader;
  BBoxResource _cache_pos;
};
} // namespace fresh