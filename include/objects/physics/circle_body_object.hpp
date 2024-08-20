#pragma once

#include "body_object.hpp"

namespace fresh {
class CircleBodyObject : public BodyObject {
public:
  CircleBodyObject(const b2WorldId& world_id, SDL_FRect pos, idk::f32 radius, bool is_static_body = false);
  ~CircleBodyObject() override = default;

  void sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "circlebodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  void set_is_static_body(bool is_static_body) noexcept override;

  idk::f32 _radius;
private:
  void _create_body() noexcept;
protected:
};
} // namespace fresh