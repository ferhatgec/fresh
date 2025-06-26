// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <freshengine.hpp>
#include <objects/physics/body_object.hpp>
#include <box2d/box2d.h>

namespace fresh {
BodyObject::BodyObject(bool is_static_body, bool is_fixed_rotation)
  : _is_static_body{is_static_body}, _is_fixed_rotation{is_fixed_rotation} {}

void BodyObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes();
}

void BodyObject::set(const fescript::Token& name, fescript::Object value) {
  // TODO: fescript integration.
}

[[nodiscard]] const bool& BodyObject::get_is_static_body() const noexcept {
  return this->_is_static_body;
}

[[nodiscard]] const b2BodyId& BodyObject::get_body_id() const noexcept {
  return this->_body_id;
}

void BodyObject::set_is_static_body(bool is_static_body) noexcept {
  this->_is_static_body = is_static_body;
  std::cout << "Engine info: Do not use BodyObject and its member functions directly.\n"
               "             Use RectangleBodyObject if you want rectangle physics body.\n";
}

[[nodiscard]] const bool& BodyObject::get_fixed_rotation() const noexcept {
  return this->_is_fixed_rotation;
}

void BodyObject::set_fixed_rotation(bool fixed_rotation) noexcept {
  this->_is_fixed_rotation = fixed_rotation;
  b2Body_SetMotionLocks(this->_body_id, b2MotionLocks { false, false, this->_is_fixed_rotation });
}

void BodyObject::set_linear_velocity(const PointResource& pt) const noexcept {
  b2Body_SetLinearVelocity(this->get_body_id(), b2Vec2 { pt.get_x() * ptm_ratio, pt.get_y() * ptm_ratio });
}

[[nodiscard]] PointResource BodyObject::get_linear_velocity() const noexcept {
  return b2Body_GetLinearVelocity(this->get_body_id());
}

void BodyObject::apply_force_center(const PointResource& pt) const noexcept {
  b2Body_ApplyForceToCenter(this->get_body_id(), b2Vec2{pt.get_x() * ptm_ratio, pt.get_y() * ptm_ratio}, true);
}

void BodyObject::apply_linear_impulse_center(const PointResource& pt) const noexcept {
  b2Body_ApplyLinearImpulseToCenter(this->get_body_id(), b2Vec2{pt.get_x() * ptm_ratio, pt.get_y() * ptm_ratio}, true);
}

[[nodiscard]] idk::f32 BodyObject::to_physics(idk::f32 pixels) noexcept {
  return pixels / ptm_ratio;
}

[[nodiscard]] idk::f32 BodyObject::to_renderer(idk::f32 meters) noexcept {
  return meters * ptm_ratio;
}
} // namespace fresh