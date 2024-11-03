#pragma once

#include <resources/color_resource.hpp>
#include <resources/polygon_resource.hpp>
#include "base_object.hpp"
#include "polygon_object.hpp"

#include "rectangle.hpp"

namespace fresh {
class RectangleObject : public BaseObject {
public:
  friend class FesLoaderResource;

  explicit RectangleObject(bool is_filled = true);
  RectangleObject(BBoxResource info, ColorResource color, bool is_filled = true);
  ~RectangleObject() override = default;

  void
  sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "rectangleobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;

  // TODO: we need Drawable class that gives get_position_resource(), get_color_resource()
  // and draw() function. so, that will change the definition of BaseObject.
  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;

  __idk_nodiscard
  bool& get_is_filled() noexcept;

  void set_rotation(idk::f32 rad_degrees) noexcept override;
protected:
  bool _is_filled;
  fre2d::Rectangle _rectangle;
  fre2d::Shader _shader;
  ColorResource _color;
};
} // namespace fresh