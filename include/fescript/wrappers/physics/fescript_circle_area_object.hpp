#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define CIRCLE_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, CircleAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, CircleAreaObjectMember, 1, fresh::CircleAreaObject)
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleAreaObjectMember, 0, fresh::CircleAreaObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleAreaObjectMember, 1, fresh::CircleAreaObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, CircleAreaObject, -1, FescriptAreaObjectWrapper)
} // namespace fescript