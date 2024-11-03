#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(PushPolygon, PolygonObjectMember, 2, fresh::PolygonObject)
DEFINE_MEMBER_MODULE_CLASS(DeleteAllPolygons, PolygonObjectMember, 0, fresh::PolygonObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsFilled, PolygonObjectMember, 0, fresh::PolygonObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, PolygonObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript