// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, BodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetFixedRot, BodyObjectMember, 1, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetFixedRot, BodyObjectMember, 0, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, BodyObjectMember, 1, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, BodyObjectMember, 0, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(SetLinearVelocity, BodyObjectMember, 2, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetLinearVelocity, BodyObjectMember, 0, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(ApplyForceCenter, BodyObjectMember, 1, fresh::BodyObject)
DEFINE_MEMBER_MODULE_CLASS(ApplyLinearImpulseCenter, BodyObjectMember, 2, fresh::BodyObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, BodyObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript