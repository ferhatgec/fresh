#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsVisibleOnCamera, CameraObjectMember, 1, fresh::CameraObject)
DEFINE_MEMBER_MODULE_CLASS(Move, CameraObjectMember, 2, fresh::CameraObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, CameraObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript