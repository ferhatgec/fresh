#pragma once

#include "module_helpers.hpp"
#include "../../../libs/SDL/include/SDL_video.h"
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/predefined.hpp>


#define ENGINEWINDOW_GLOBAL_CONSTANT(name, value) this->globals->define(name, static_cast<idk::f80>(value));
#define ENGINEWINDOW_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, EngineWindow, arg_count)
#define ENGINEWINDOW_GLOBAL_CONSTANTS() \
ENGINEWINDOW_GLOBAL_CONSTANT("EngineWindow_Fullscreen", SDL_WINDOW_FULLSCREEN) \
ENGINEWINDOW_GLOBAL_CONSTANT("EngineWindow_FullscreenWindowed", SDL_WINDOW_FULLSCREEN_DESKTOP) \
ENGINEWINDOW_GLOBAL_CONSTANT("EngineWindow_Windowed", 0)

namespace fescript {
ENGINEWINDOW_MODULE(GetCurrentWindowSize, 0)
ENGINEWINDOW_MODULE(GetCurrentWindowPos, 0)
ENGINEWINDOW_MODULE(GetCurrentCursorPos, 0)
ENGINEWINDOW_MODULE(SetWindowIcon, 1)
ENGINEWINDOW_MODULE(SetWindowTitle, 1)
ENGINEWINDOW_MODULE(GetWindowTitle, 0)
ENGINEWINDOW_MODULE(SetWindowCursor, 3)
ENGINEWINDOW_MODULE(SetWindowMode, 1)
ENGINEWINDOW_MODULE(GetWindowMode, 0)
ENGINEWINDOW_MODULE(SetDefaultClearColor, 4)
ENGINEWINDOW_MODULE(SetVSync, 1)
ENGINEWINDOW_MODULE(CloseWindow, 0)
ENGINEWINDOW_MODULE(MaximizeWindow, 0)
ENGINEWINDOW_MODULE(MinimizeWindow, 0)
ENGINEWINDOW_MODULE(RestoreWindow, 0)
ENGINEWINDOW_MODULE(IsWindowMaximized, 0)
ENGINEWINDOW_MODULE(IsWindowMinimized, 0)
ENGINEWINDOW_MODULE(SetWindowOpacity, 1)
ENGINEWINDOW_MODULE(GetWindowOpacity, 0)
} // namespace fescript

#undef ENGINEWINDOW_MODULE