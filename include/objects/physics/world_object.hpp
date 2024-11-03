#pragma once

#include <box2d/box2d.h>
#include <objects/base_object.hpp>
#include <resources/point_resource.hpp>

namespace fresh {
class WorldObject : public BaseObject {
public:
  enum : std::uint8_t {
    DefaultPhysicsFPS = 60,
    DefaultSubstepCount = 4
  };

  WorldObject(PointResource gravity = {0.f, -40.f}, idk::u32 physics_frame = DefaultPhysicsFPS, idk::u32 substep_count = DefaultSubstepCount) noexcept;
  ~WorldObject() override;

  void
  sync() noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "worldobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] const b2WorldId& get_world_id() const noexcept;
  [[nodiscard]] const idk::u32& get_substep_count() const noexcept;
  [[nodiscard]] const idk::u32& get_physics_frame() const noexcept;
  [[nodiscard]] const idk::f32& get_timestep() const noexcept;

  void set_substep_count(idk::u32 substep_count) noexcept;
  void set_physics_frame(idk::u32 physics_frame) noexcept;
protected:
  b2WorldId _world_id;
  idk::u32 _substep_count;
  idk::u32 _physics_frame;

  idk::f32 _timestep;
};
} // namespace fresh