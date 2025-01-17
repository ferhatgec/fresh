// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <resources/circle_resource.hpp>
#include <resources/color_resource.hpp>
#include <circle.hpp>
#include <shader.hpp>
#include "base_object.hpp"
#include "shader_object.hpp"

namespace fresh {
class CircleObject : public BaseObject, public ShaderObject {
public:
  friend class FesLoaderResource;

  CircleObject() = default;
  CircleObject(BBoxResource info, CircleResource resource, ColorResource color);
  ~CircleObject() = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "circleobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  __idk_nodiscard
  CircleResource& get_circle_resource() noexcept;

  __idk_nodiscard
  ColorResource& get_color_resource() noexcept;

  void set_flip_vertically(bool flip_vertically) noexcept override;
  void set_flip_horizontally(bool flip_horizontally) noexcept override;

  [[nodiscard]] const bool& get_flip_vertically() const noexcept override;
  [[nodiscard]] const bool& get_flip_horizontally() const noexcept override;

  void init_signal() noexcept override;

  void notify_x() noexcept override;
  void notify_y() noexcept override;
  void notify_w() noexcept override;
  void notify_h() noexcept override;
protected:
  void _base_notify_xy() noexcept;
  void _base_notify_wh() noexcept;
  CircleResource _resource;
  fre2d::Circle _circle;
};
} // namespace fresh