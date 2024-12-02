// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(InitSprite, SpriteObjectMember, 0, fresh::SpriteObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, SpriteObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript