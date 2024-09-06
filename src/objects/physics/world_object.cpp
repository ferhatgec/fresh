#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/physics/world_object.hpp>
#include <objects/camera_object.hpp>
#include <render_objects.hpp>

namespace fresh {
WorldObject::WorldObject(PointResource gravity, idk::u32 physics_frame, idk::u32 substep_count) noexcept
  : _physics_frame{physics_frame}, _substep_count{substep_count} {
  this->_object_def = "worldobject";
  b2WorldDef world_def = b2DefaultWorldDef();
  world_def.gravity.x = gravity.get_x();
  world_def.gravity.y = gravity.get_y();
  this->_world_id = b2CreateWorld(&world_def);
  this->_timestep = 1.f / ((this->_physics_frame == 0) ? DefaultPhysicsFPS : static_cast<idk::f32>(this->_physics_frame));
}

WorldObject::~WorldObject() {
  b2DestroyWorld(this->_world_id);
}

void WorldObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  b2World_Step(this->_world_id, this->_timestep, this->_substep_count);
  APPLY_DELTAS()
}

void WorldObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CircleBodyObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

[[nodiscard]] const b2WorldId& WorldObject::get_world_id() const noexcept {
  return this->_world_id;
}

[[nodiscard]] const idk::u32& WorldObject::get_substep_count() const noexcept {
  return this->_substep_count;
}

[[nodiscard]] const idk::u32& WorldObject::get_physics_frame() const noexcept {
  return this->_physics_frame;
}

[[nodiscard]] const idk::f32& WorldObject::get_timestep() const noexcept {
  return this->_timestep;
}

void WorldObject::set_substep_count(idk::u32 substep_count) noexcept {
  this->_substep_count = substep_count;
}

void WorldObject::set_physics_frame(idk::u32 physics_frame) noexcept {
  this->_physics_frame = (physics_frame == 0) ? DefaultPhysicsFPS : physics_frame;
  this->_timestep = 1.f / static_cast<idk::f32>(this->_physics_frame);
}
} // namespace fresh