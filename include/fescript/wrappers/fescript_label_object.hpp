// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(InitFont, LabelObjectMember, 0, fresh::LabelObject)
DEFINE_MEMBER_MODULE_CLASS(InitText, LabelObjectMember, 0, fresh::LabelObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, LabelObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript