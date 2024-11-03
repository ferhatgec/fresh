#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define RECTANGLE_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, RectangleAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, RectangleAreaObjectMember, 1, fresh::RectangleAreaObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, RectangleAreaObject, -1, FescriptAreaObjectWrapper)
} // namespace fescript