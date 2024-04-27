#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"

#define ENGINEWINDOW_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, EngineWindow, arg_count)

namespace fescript {
ENGINEWINDOW_MODULE(GetCurrentWindowSize, 0)
ENGINEWINDOW_MODULE(GetCurrentWindowPos, 0)
ENGINEWINDOW_MODULE(SetWindowIcon, 1)
ENGINEWINDOW_MODULE(SetWindowTitle, 1)
} // namespace fescript

#undef ENGINEWINDOW_MODULE