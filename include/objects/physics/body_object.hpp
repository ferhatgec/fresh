// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <objects/base_object.hpp>
#include "world_object.hpp"

#include "box2d/id.h"

namespace fresh {
constexpr static idk::f32 ptm_ratio { 32.f };

class BodyObject : public BaseObject {
public:
  static constexpr bool IsStaticBodyDefault { false },
                        IsFixedRotationDefault { false };

  explicit BodyObject(bool is_static_body = IsStaticBodyDefault, bool is_fixed_rotation = IsFixedRotationDefault);
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
  [[nodiscard]] const bool& get_fixed_rotation() const noexcept;
  void set_fixed_rotation(bool fixed_rotation) noexcept;
  void set_linear_velocity(const PointResource& pt) const noexcept;
  [[nodiscard]] PointResource get_linear_velocity() const noexcept;
  void apply_force_center(const PointResource& pt) const noexcept;
  void apply_linear_impulse_center(const PointResource& pt) const noexcept;

  [[nodiscard]] static idk::f32 to_physics(idk::f32 pixels) noexcept;
  [[nodiscard]] static idk::f32 to_renderer(idk::f32 meters) noexcept;
protected:
  bool _is_static_body, _is_fixed_rotation;
  b2BodyId _body_id;
  b2WorldId _world_id;
};
} // namespace fresh