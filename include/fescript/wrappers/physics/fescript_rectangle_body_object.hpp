// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define RECTANGLE_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, RectangleBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, RectangleBodyObject, -1, FescriptBodyObjectWrapper)
} // namespace fescript