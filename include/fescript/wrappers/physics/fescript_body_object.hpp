#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, BodyObjectMember, arg_count)

namespace fescript {
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, BodyObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript