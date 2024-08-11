#pragma once

#include "base_object.hpp"
#include <resources/color_resource.hpp>

namespace fresh {
class RectangleObject : public BaseObject {
public:
  friend class FesLoaderResource;

  RectangleObject(bool is_filled = true);
  RectangleObject(SDL_FRect info, ColorResource color, bool is_filled = true);
  ~RectangleObject() = default;

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "rectangleobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  // TODO: we need Drawable class that gives get_position_resource(), get_color_resource()
  // and draw() function. so, that will change the definition of BaseObject.
  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;

  __idk_nodiscard
  bool& get_is_filled() noexcept;
protected:
  bool _is_filled;
  ColorResource _color;
};
} // namespace fresh