// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "body_object.hpp"

namespace fresh {
class RectangleBodyObject : public BodyObject {
public:
  RectangleBodyObject(const b2WorldId& world_id, BBoxResource pos, bool is_static_body = false);
  ~RectangleBodyObject() override = default;

  void sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "rectanglebodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  void set_is_static_body(bool is_static_body) noexcept override;

  void set_rotation(idk::f32 rad_degrees) noexcept override;
private:
  void _create_body() noexcept;

  [[nodiscard]] BBoxResource _convert_box2d_pos() noexcept;
};
} // namespace fresh