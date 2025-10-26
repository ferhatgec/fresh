// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <resources/color_resource.hpp>
#include <resources/edge_resource.hpp>
#include <resources/polygon_resource.hpp>
#include "base_object.hpp"
#include "polygon.hpp"
#include "shader_object.hpp"

namespace fresh {
class PolygonObject : public BaseObject, public ShaderObject {
public:
  friend class FesLoaderResource;
  friend class RectangleObject;

  PolygonObject();
  PolygonObject(PolygonResource resource, ColorResource color);
  ~PolygonObject() override;

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "polygonobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;

  [[nodiscard]]
  PolygonResource& get_polygon_resource() noexcept;

  [[nodiscard]]
  ColorResource& get_color_resource() noexcept;

  void set_rotation(idk::f32 rad_degrees) noexcept override;
  void set_flip_vertically(bool flip_vertically) noexcept override;
  void set_flip_horizontally(bool flip_horizontally) noexcept override;
  void set_ignore_zoom(bool ignore_zoom) noexcept override;
  void set_affected_by_light(bool affected_by_light) noexcept override;

  [[nodiscard]] const bool& get_flip_vertically() const noexcept override;
  [[nodiscard]] const bool& get_flip_horizontally() const noexcept override;
  [[nodiscard]] bool get_ignore_zoom() const noexcept override;
  [[nodiscard]] bool get_affected_by_light() const noexcept override;
protected:
  PolygonResource _resource;
  fre2d::Polygon _polygon;
  BBoxResource _cache_pos;
};
} // namespace fresh