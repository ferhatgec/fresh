#pragma once

#include "base_object.hpp"
#include <resources/circle_resource.hpp>
#include <resources/color_resource.hpp>

namespace fresh {
class CircleObject : public BaseObject {
public:
  friend class FesLoaderResource;

  CircleObject();
  CircleObject(CircleResource resource, ColorResource color);
  ~CircleObject();

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "circleobject";
  }

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;

  __idk_nodiscard
  CircleResource& get_circle_resource() noexcept;

  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;
private:
  void _draw_circle() noexcept;
  void _draw_filled_circle() noexcept;
  void _draw_unfilled_circle() noexcept;
  void _draw_horizontal_line(idk::f32 x1, idk::f32 x2, idk::f32 y) noexcept;
  void _draw_single_point(idk::f32 x, idk::f32 y) noexcept;
protected:
  CircleResource _resource;
  ColorResource _color;
};
} // namespace fresh