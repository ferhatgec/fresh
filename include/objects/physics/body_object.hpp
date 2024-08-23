#pragma once

#include "world_object.hpp"
#include <objects/base_object.hpp>

namespace fresh {
constexpr static idk::f32 ptm_ratio = 1.f;

class BodyObject : public BaseObject {
public:
  static constexpr bool IsStaticBodyDefault { false };

  explicit BodyObject(bool is_static_body = false);
  virtual ~BodyObject() = default;

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
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
  [[nodiscard]] static SDL_FRect to_sdl(b2Vec2 vec, idk::f32 w, idk::f32 h) noexcept;
  [[nodiscard]] static b2Vec2 to_box2d(SDL_FRect rect) noexcept;
protected:
  bool _is_static_body;
  b2BodyId _body_id;
  b2WorldId _world_id;
};
} // namespace fresh