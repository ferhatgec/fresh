// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "module_helpers.hpp"
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/predefined.hpp>

#define ENGINE_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Engine, arg_count)

namespace fescript {
ENGINE_MODULE(GetObject, 1)
ENGINE_MODULE(RenderObjectsPush, 1)
ENGINE_MODULE(LoadFes, 1)
ENGINE_MODULE(LinkCamera, 1)
} // namespace fescript

#undef ENGINE_MODULE