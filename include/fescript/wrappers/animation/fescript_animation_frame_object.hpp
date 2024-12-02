// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>
#include <objects/base_object.hpp>

#define ANIMATION_FRAME_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AnimationFrameObjectMember, arg_count)

namespace fescript {
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, AnimationFrameObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript