// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "body_object.hpp"
#include <resources/polygon_resource.hpp>

namespace fresh {
class PolygonBodyObject : public BodyObject {
public:
  PolygonBodyObject(
    const b2WorldId& world_id,
    BBoxResource pos,
    const PolygonResource& vertices,
    bool is_static_body = IsStaticBodyDefault,
    bool is_fixed_rotation = IsFixedRotationDefault
  );
  ~PolygonBodyObject() override = default;

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "polygonbodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  void set_is_static_body(bool is_static_body) noexcept override;
private:
  void _create_body() noexcept;
protected:
  PolygonResource _vertices;
};
} // namespace fresh