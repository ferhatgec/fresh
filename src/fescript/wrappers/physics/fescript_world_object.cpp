#include <fescript/wrappers/physics/fescript_world_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/world_object.hpp>

namespace fescript {
/// WorldObject.get_substep_count()
__idk_nodiscard Object FescriptWorldObjectMemberGetSubstepCount::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_substep_count()")
  return static_cast<idk::f80>(this->_self->get_substep_count());
}

/// CircleBodyObject.get_physics_frame()
__idk_nodiscard Object FescriptWorldObjectMemberGetPhysicsFrame::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_physics_frame()")
  return static_cast<idk::f80>(this->_self->get_physics_frame());
}

/// CircleBodyObject.get_timestep()
__idk_nodiscard Object FescriptWorldObjectMemberGetTimestep::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("WorldObject.get_timestep()")
  return static_cast<idk::f80>(this->_self->get_timestep());
}

/// CircleBodyObject.set_substep_count(count: decimal)
__idk_nodiscard Object FescriptWorldObjectMemberSetSubstepCount::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
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
__idk_nodiscard Object FescriptWorldObjectMemberSetPhysicsFrame::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
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

WorldObjectWrapper::WorldObjectWrapper() {
  this->_object_def = "worldobject";
}

WorldObjectWrapper::~WorldObjectWrapper() {
 }

[[nodiscard]] std::string WorldObjectWrapper::to_string() {
  return "worldobject";
}

[[nodiscard]] Object WorldObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto world_object = std::make_shared<fresh::WorldObject>();
  this->_object_id = world_object->get_object_id();
  return std::move(world_object);
}
} // namespace fescript