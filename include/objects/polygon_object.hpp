#pragma once

#include "base_object.hpp"
#include <resources/polygon_resource.hpp>
#include <resources/color_resource.hpp>
#include <resources/edge_resource.hpp>

namespace fresh {
class PolygonObject : public BaseObject {
public:
  friend class FesLoaderResource;
  friend class RectangleObject;

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

  void set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept override;
private:
  void _draw_polygon() noexcept;
  void _draw_filled_polygon() noexcept;
  void _draw_unfilled_polygon() noexcept;
  void _add_render_objects() noexcept;
  void _sub_render_objects() noexcept;
protected:
  PolygonResource _resource;
  ColorResource _color;
  SDL_FRect _cache_pos;
};

inline bool operator==(const SDL_FRect& lhs, const SDL_FRect& rhs) noexcept {
  return f32_nearly_equals(lhs.x, rhs.x) && f32_nearly_equals(lhs.y, rhs.y) && f32_nearly_equals(lhs.w, rhs.w) && f32_nearly_equals(lhs.h, rhs.h);
}
} // namespace fresh