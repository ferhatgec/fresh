#pragma once

#include "body_object.hpp"

namespace fresh {
class RectangleBodyObject : public BodyObject {
public:
  RectangleBodyObject(const b2WorldId& world_id, SDL_FRect pos, bool is_static_body = false);
  ~RectangleBodyObject() override = default;

  void sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "rectanglebodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  virtual void set_is_static_body(bool is_static_body) noexcept;

  void set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept override;
private:
  void _create_body() noexcept;

  [[nodiscard]] SDL_FRect _convert_box2d_pos() noexcept;
};
} // namespace fresh