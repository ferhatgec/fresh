#include "log/log.hpp"

#include <fescript/fescript_array.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <render_objects.hpp>
#include <resources/polygon_resource.hpp>

namespace fresh {
// FIXME: spawn in certain positions gives NaN.
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
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  auto position = b2Body_GetPosition(this->_body_id);
  if(!b2Vec2_IsValid(position)) {
    log_error(fresh::src(), "b2Vec2_IsValid false for object '{}'!", this->get_name().data());
    this->_disabled = true; // disabling a node will also disable its child nodes; no code execution; either enable using another node; or manually enable.
    this->_visible = false;
    b2DestroyBody(this->_body_id);
    this->_body_id = b2_nullBodyId;
    return;
  }
  // auto rotation = b2Body_GetRotation(this->_body_id); // TODO: we don't have rotation yet, but we essentially need it since any child
                                                         // of CircleBodyObject may contain SpriteObject or smth where rotation makes difference?
  this->get_position_info() = to_sdl(position, to_renderer(this->_pos_info.w), to_renderer(this->_pos_info.h));
  APPLY_DELTAS()
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
  body_def.position = to_box2d(this->_pos_info);
  body_def.type = this->_is_static_body ? b2_staticBody : b2_dynamicBody;
  this->_body_id = b2CreateBody(this->_world_id, &body_def);
  b2Circle circle;
  circle.radius = to_physics(this->_radius);
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