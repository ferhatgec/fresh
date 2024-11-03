#pragma once

#include "body_object.hpp"

namespace fresh {
class CircleBodyObject : public BodyObject {
public:
  CircleBodyObject(const b2WorldId& world_id, BBoxResource pos, idk::f32 radius, bool is_static_body = false);
  ~CircleBodyObject() override = default;

  void sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "circlebodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void set_is_static_body(bool is_static_body) noexcept override;

  [[nodiscard]] const idk::f32& get_radius() const noexcept;
  void set_radius(idk::f32 r) noexcept;
private:
  void _create_body() noexcept;
protected:
  idk::f32 _radius;
};
} // namespace fresh