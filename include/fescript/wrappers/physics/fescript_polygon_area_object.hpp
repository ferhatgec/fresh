// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define POLYGON_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, PolygonAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, PolygonAreaObjectMember, 1, fresh::PolygonAreaObject)
DEFINE_MEMBER_MODULE_CLASS(PushPolygon, PolygonAreaObjectMember, 2, fresh::PolygonAreaObject)
DEFINE_MEMBER_MODULE_CLASS(DeleteAllPolygons, PolygonAreaObjectMember, 0, fresh::PolygonAreaObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, PolygonAreaObject, -1, FescriptAreaObjectWrapper)
} // namespace fescript