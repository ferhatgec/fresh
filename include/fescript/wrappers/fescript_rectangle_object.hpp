#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, RectangleObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript