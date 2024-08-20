#include <objects/physics/body_object.hpp>
#include <numbers>

namespace fresh {
BodyObject::BodyObject(bool is_static_body)
  : _is_static_body{is_static_body} {
  this->_object_def = "bodyobject";
}

void BodyObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_disabled)
    return;
  APPLY_DELTAS()
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

[[nodiscard]] idk::f32 BodyObject::to_physics(idk::f32 pixels) noexcept {
  return pixels / ptm_ratio;
}

[[nodiscard]] idk::f32 BodyObject::to_renderer(idk::f32 meters) noexcept {
  return meters * ptm_ratio;
}

// converts [-2pi, +2pi] range to box2d [-pi, +pi] range.
[[nodiscard]] idk::f32 BodyObject::to_box2d_angle(idk::f32 angle_rad) noexcept {
  if(angle_rad < std::numbers::pi_v<idk::f32>)
    return angle_rad + 2.f * std::numbers::pi_v<idk::f32>;
  if(angle_rad > std::numbers::pi_v<idk::f32>)
    return angle_rad - 2.f * std::numbers::pi_v<idk::f32>;
  return angle_rad;
}

// converts [-pi, +pi] range to fresh [-2pi, +2pi] range.
[[nodiscard]] idk::f32 BodyObject::to_sdl_angle(idk::f32 angle_rad) noexcept {
  return angle_rad < 0.f ? angle_rad + 2.f * std::numbers::pi_v<idk::f32>: angle_rad;
}

[[nodiscard]] SDL_FRect BodyObject::to_sdl(b2Vec2 vec, idk::f32 w, idk::f32 h) noexcept {
  return SDL_FRect {
    ptm_ratio * vec.x,
    static_cast<idk::f32>(std::get<1>(Engine::get_instance()->get_window()->get_window_size())) - ptm_ratio * vec.y,
    w,
    h
  };
}

[[nodiscard]] b2Vec2 BodyObject::to_box2d(SDL_FRect rect) noexcept {
  return b2Vec2 {
    rect.x / ptm_ratio,
    (static_cast<idk::f32>(std::get<1>(Engine::get_instance()->get_window()->get_window_size())) - rect.y) / ptm_ratio
  };
}
} // namespace fresh