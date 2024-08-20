#include <objects/physics/circle_body_object.hpp>

namespace fresh {
CircleBodyObject::CircleBodyObject(const b2WorldId& world_id, SDL_FRect pos, idk::f32 radius, bool is_static_body)
  : _radius{radius} {
  this->_world_id = world_id;
  this->_pos_info = pos;
  this->_is_static_body = is_static_body;
  this->_rotation_degrees = this->_last_rotation_degrees = 0.f;
  this->_object_def = "circlebodyobject";
  this->_create_body();
}

void CircleBodyObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_disabled)
    return;
  auto position = b2Body_GetPosition(this->_body_id);
  // auto rotation = b2Body_GetRotation(this->_body_id); // TODO: we don't have rotation for BaseObject.
  this->get_position_info() = to_sdl(position, to_renderer(this->_pos_info.w), to_renderer(this->_pos_info.h)); // SDL_FRect { to_renderer(position.x), to_renderer(position.y), to_renderer(this->_pos_info.w), to_renderer(this->_pos_info.h) };
  APPLY_DELTAS()
}

void CircleBodyObject::set(const fescript::Token& name, fescript::Object value) {
  // TODO: fescript integration.
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
  body_def.position = to_box2d(this->_pos_info);
  // body_def.position.x = to_physics(this->_pos_info.x);
  // body_def.position.y = to_physics(this->_pos_info.y);
  if(!this->_is_static_body)
    body_def.type = b2_dynamicBody;
  this->_body_id = b2CreateBody(this->_world_id, &body_def);
  b2Circle circle;
  // circle.center = body_def.position;
  // circle.center = {to_physics(this->_pos_info.x), to_physics(this->_pos_info.y)};
  circle.radius = to_physics(this->_radius);
  b2ShapeDef shape_def = b2DefaultShapeDef();
  b2CreateCircleShape(this->_body_id, &shape_def, &circle);
}
} // namespace fresh