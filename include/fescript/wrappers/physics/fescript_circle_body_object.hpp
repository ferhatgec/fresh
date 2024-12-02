// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define CIRCLE_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, CircleBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, CircleBodyObjectMember, 1, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, CircleBodyObjectMember, 0, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleBodyObjectMember, 0, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleBodyObjectMember, 1, fresh::CircleBodyObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, CircleBodyObject, -1, FescriptBodyObjectWrapper)
} // namespace fescript