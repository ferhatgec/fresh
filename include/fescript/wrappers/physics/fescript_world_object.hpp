#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define WORLD_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, WorldObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(GetSubstepCount, WorldObjectMember, 0, fresh::WorldObject)
DEFINE_MEMBER_MODULE_CLASS(GetPhysicsFrame, WorldObjectMember, 0, fresh::WorldObject)
DEFINE_MEMBER_MODULE_CLASS(GetTimestep, WorldObjectMember, 0, fresh::WorldObject)
DEFINE_MEMBER_MODULE_CLASS(SetSubstepCount, WorldObjectMember, 1, fresh::WorldObject)
DEFINE_MEMBER_MODULE_CLASS(SetPhysicsFrame, WorldObjectMember, 1, fresh::WorldObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, WorldObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript