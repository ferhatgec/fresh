// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_base_object.hpp"
#include <objects/point_light_object.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(GetAmbient, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(GetDiffuse, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(GetAttenuationConstant, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(GetAttenuationLinear, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(GetAttenuationQuadratic, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(SetAmbient, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(SetDiffuse, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(SetAttenuationConstant, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(SetAttenuationLinear, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MEMBER_MODULE_CLASS(SetAttenuationQuadratic, PointLightObjectMember, 0, fresh::PointLightObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, PointLightObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript