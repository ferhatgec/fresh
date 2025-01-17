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

#define OS_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, OS, arg_count)

#ifdef _WIN32
#   define popen _popen
#   define pclose _pclose
#endif

namespace fescript {
OS_MODULE(Platform, 0)
OS_MODULE(Exec, 1)
OS_MODULE(Arch, 0)
OS_MODULE(GetClipboardText, 0)
OS_MODULE(SetClipboardText, 1)
} // namespace fescript

#undef OS_MODULE