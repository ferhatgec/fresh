#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, AreaObjectMember, 1, fresh::AreaObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, AreaObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript