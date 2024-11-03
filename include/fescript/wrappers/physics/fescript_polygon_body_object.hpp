#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define POLYGON_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, PolygonBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, PolygonBodyObjectMember, 1, fresh::PolygonBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, PolygonBodyObjectMember, 0, fresh::PolygonBodyObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, PolygonBodyObject, -1, FescriptBodyObjectWrapper)
} // namespace fescript