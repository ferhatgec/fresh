// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <resources/color_resource.hpp>
#include <resources/polygon_resource.hpp>
#include "base_object.hpp"
#include "polygon_object.hpp"
#include "rectangle.hpp"
#include "shader_object.hpp"

namespace fresh {
class RectangleObject : public BaseObject, public ShaderObject {
public:
  friend class FesLoaderResource;

  explicit RectangleObject(bool is_filled = true);
  RectangleObject(BBoxResource info, ColorResource color, bool is_filled = true);
  ~RectangleObject() override = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

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
  void set_flip_vertically(bool flip_vertically) noexcept override;
  void set_flip_horizontally(bool flip_horizontally) noexcept override;

  [[nodiscard]] const bool& get_flip_vertically() const noexcept override;
  [[nodiscard]] const bool& get_flip_horizontally() const noexcept override;

  void notify_x() noexcept override;
  void notify_y() noexcept override;
  void notify_w() noexcept override;
  void notify_h() noexcept override;
protected:
  void _base_notify_xy() noexcept;
  void _base_notify_wh() noexcept;
  bool _is_filled;
  fre2d::Rectangle _rectangle;
};
} // namespace fresh