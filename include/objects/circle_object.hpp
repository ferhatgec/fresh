#pragma once

#include <resources/circle_resource.hpp>
#include <resources/color_resource.hpp>
#include <circle.hpp>
#include <shader.hpp>
#include "base_object.hpp"

namespace fresh {
class CircleObject : public BaseObject {
public:
  friend class FesLoaderResource;

  CircleObject() = default;
  CircleObject(BBoxResource info, CircleResource resource, ColorResource color);
  ~CircleObject() = default;

  void
  sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "circleobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  __idk_nodiscard
  CircleResource& get_circle_resource() noexcept;

  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;

  void init_signal() noexcept override;
protected:
  CircleResource _resource;
  ColorResource _color;
  fre2d::Circle _circle;
  fre2d::Shader _shader;
};
} // namespace fresh