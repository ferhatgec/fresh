#include <objects/camera_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <resources/polygon_resource.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <numbers>
#include <format>

namespace fresh {
RectangleBodyObject::RectangleBodyObject(const b2WorldId& world_id, BBoxResource pos, bool is_static_body) {
  this->_world_id = world_id;
  this->_is_static_body = is_static_body;
  this->_pos_info = pos;
  this->_create_body();
  this->reset_delta();
}

void RectangleBodyObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  auto position = b2Body_GetPosition(this->_body_id);
  auto rotation = BaseObject::counter_clockwise_to_clockwise(b2Rot_GetAngle(b2Body_GetRotation(this->_body_id))); // TODO: we don't have rotation for BaseObject (update: we may have now).
  this->set_position(BBoxResource { to_renderer(position.x), to_renderer(position.y), this->get_w(), this->get_h() });
  this->set_rotation(rotation);
  this->apply_changes();
}

void RectangleBodyObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: PolygonBodyObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void RectangleBodyObject::set_is_static_body(bool is_static_body) noexcept {
  if(this->_is_static_body == is_static_body)
    return;
  b2DestroyBody(this->_body_id);
  this->_body_id = b2_nullBodyId;
  this->_is_static_body = is_static_body;
  this->_create_body();
}

void RectangleBodyObject::_create_body() noexcept {
  b2BodyDef body_def = b2DefaultBodyDef();
  body_def.position = b2Vec2 { .x = this->_pos_info.get_x() / ptm_ratio, .y = this->_pos_info.get_y() / ptm_ratio };
  body_def.rotation = b2MakeRot(BaseObject::counter_clockwise_to_clockwise(this->_rotation_degrees));
  body_def.type = this->_is_static_body ? b2_staticBody : b2_dynamicBody;
  this->_body_id = b2CreateBody(this->_world_id, &body_def);
  b2Polygon const rect = b2MakeBox(
    to_physics(this->_pos_info.get_w()) / 2.f,
    to_physics(this->_pos_info.get_h()) / 2.f
  ); // box2d takes half width; half height so we divide it by 2.
  b2ShapeDef const shape_def = b2DefaultShapeDef();
  b2CreatePolygonShape(this->_body_id, &shape_def, &rect);
}

void RectangleBodyObject::set_rotation(idk::f32 rad_degrees) noexcept {
  const auto rad_fresh = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  if(f32_nearly_equals(this->_rotation_degrees, rad_fresh))
    return;
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = rad_fresh;
  // FIXME: we are actually overriding positions using atypical way, directly forcing it. which is actually
  // wrong. to rotate static body with that way, other bodies will not directly interact with each other.
  // but if you do not rotate your static body, then it will be fine.
  // we may use angular velocity but we need to keep its track since it can overflow limits.
  // TODO: we may add at least option to recreate body at every xth operation, creating body do cost very much.
  b2Body_SetTransform(this->_body_id, b2Body_GetPosition(this->_body_id), b2MakeRot(BaseObject::counter_clockwise_to_clockwise(this->_rotation_degrees)));
}
} // namespace fresh