#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleObjectMember, 0, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsFilled, CircleObjectMember, 0, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleObjectMember, 1, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(SetIsFilled, CircleObjectMember, 1, fresh::CircleObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, CircleObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript