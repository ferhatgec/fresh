#include "log/log.hpp"

#include <fescript/fescript_array.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <render_objects.hpp>
#include <resources/polygon_resource.hpp>

namespace fresh {
// FIXME: spawn in certain positions gives NaN.
CircleBodyObject::CircleBodyObject(const b2WorldId& world_id, BBoxResource pos, idk::f32 radius, bool is_static_body)
  : _radius{radius} {
  this->_world_id = world_id;
  this->_pos_info = pos;
  this->_is_static_body = is_static_body;
  this->_rotation_degrees = this->_last_rotation_degrees = 0.f;
  this->_create_body();
  this->reset_delta();
}

void CircleBodyObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  auto position = b2Body_GetPosition(this->_body_id);
  auto rotation = BaseObject::counter_clockwise_to_clockwise(b2Rot_GetAngle(b2Body_GetRotation(this->_body_id)));
  this->set_position(BBoxResource { to_renderer(position.x), to_renderer(position.y), this->get_w(), this->get_h() });
  this->set_rotation(rotation);
  this->apply_changes();
}

void CircleBodyObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CircleBodyObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void CircleBodyObject::set_is_static_body(bool is_static_body) noexcept {
  if(this->_is_static_body == is_static_body)
    return;
  b2DestroyBody(this->_body_id);
  this->_body_id = b2_nullBodyId;
  this->_is_static_body = is_static_body;
  this->_create_body();
}

void CircleBodyObject::_create_body() noexcept {
  b2BodyDef body_def = b2DefaultBodyDef();
  body_def.position = b2Vec2 { .x = this->get_x() / ptm_ratio, .y = this->get_y() / ptm_ratio };
  body_def.type = this->_is_static_body ? b2_staticBody : b2_dynamicBody;
  this->_body_id = b2CreateBody(this->_world_id, &body_def);
  b2Circle circle;
  circle.center = b2Vec2 { 0.f, 0.f };
  circle.radius = to_physics(this->_radius) * 0.5f;
  b2ShapeDef const shape_def = b2DefaultShapeDef();
  b2CreateCircleShape(this->_body_id, &shape_def, &circle);
}

[[nodiscard]] const idk::f32& CircleBodyObject::get_radius() const noexcept {
  return this->_radius;
}

void CircleBodyObject::set_radius(idk::f32 r) noexcept {
  if(r > 0.f || f32_nearly_equals(r, 0.f)) [[likely]] {
    this->_radius = r;
    b2DestroyBody(this->_body_id);
    this->_body_id = b2_nullBodyId;
    this->_create_body();
  } else [[unlikely]] {
    std::cout << "Engine info: CircleBodyObject::set_radius(f32 r = " << r << "): r must satisfy >= 0.\n";
  }
}
} // namespace fresh