#include <fescript/wrappers/physics/fescript_world_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/world_object.hpp>

namespace fescript {
/// WorldObject.get_substep_count()
[[nodiscard]] Object FescriptWorldObjectMemberGetSubstepCount::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_substep_count()")
  return static_cast<idk::f80>(this->_self->get_substep_count());
}

/// CircleBodyObject.get_physics_frame()
[[nodiscard]] Object FescriptWorldObjectMemberGetPhysicsFrame::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_physics_frame()")
  return static_cast<idk::f80>(this->_self->get_physics_frame());
}

/// CircleBodyObject.get_timestep()
[[nodiscard]] Object FescriptWorldObjectMemberGetTimestep::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_timestep()")
  return static_cast<idk::f80>(this->_self->get_timestep());
}

/// CircleBodyObject.set_substep_count(count: decimal)
[[nodiscard]] Object FescriptWorldObjectMemberSetSubstepCount::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("WorldObject.set_substep_count()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  const auto& arg = std::get<LongDoubleIndex>(arguments.front());
  if(arg < 0.f) {
    std::cout << "Engine info: WorldObject.set_substep_count(count: decimal): count must satisfy >= 0.\n";
  } else {
    this->_self->set_substep_count(static_cast<idk::u32>(std::floorl(arg)));
  }
  return nullptr;
}

/// CircleBodyObject.set_physics_frame(frame: decimal)
[[nodiscard]] Object FescriptWorldObjectMemberSetPhysicsFrame::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("WorldObject.set_physics_frame()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  const auto& arg = std::get<LongDoubleIndex>(arguments.front());
  if(arg < 0.f) {
    std::cout << "Engine info: WorldObject.set_physics_frame(frame: decimal): frame must satisfy >= 0.\n";
  } else {
    this->_self->set_physics_frame(static_cast<idk::u32>(std::floorl(arg)));
  }
  return nullptr;
}

[[nodiscard]] Object FescriptWorldObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto world_object = std::make_shared<fresh::WorldObject>();
  this->_object_id = world_object->get_id();
  return std::move(world_object);
}
} // namespace fescript