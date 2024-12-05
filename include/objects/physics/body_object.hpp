// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "world_object.hpp"
#include <objects/base_object.hpp>

namespace fresh {
constexpr static idk::f32 ptm_ratio { 32.f };

class BodyObject : public BaseObject {
public:
  static constexpr bool IsStaticBodyDefault { false };

  explicit BodyObject(bool is_static_body = false);
  virtual ~BodyObject() = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "bodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] const bool& get_is_static_body() const noexcept;
  [[nodiscard]] const b2BodyId& get_body_id() const noexcept;

  virtual void set_is_static_body(bool is_static_body) noexcept;

  [[nodiscard]] static idk::f32 to_physics(idk::f32 pixels) noexcept;
  [[nodiscard]] static idk::f32 to_renderer(idk::f32 meters) noexcept;
  [[nodiscard]] static idk::f32 to_box2d_angle(idk::f32 angle_rad) noexcept;
  [[nodiscard]] static idk::f32 to_sdl_angle(idk::f32 angle_rad) noexcept;
  [[nodiscard]] static BBoxResource to_sdl(b2Vec2 vec, idk::f32 w, idk::f32 h) noexcept;
  [[nodiscard]] static b2Vec2 to_box2d(BBoxResource rect) noexcept;
protected:
  bool _is_static_body;
  b2BodyId _body_id;
  b2WorldId _world_id;
};
} // namespace fresh