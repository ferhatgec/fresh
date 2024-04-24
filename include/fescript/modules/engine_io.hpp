#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"
#include "../../../libs/SDL/include/SDL_scancode.h"
#include <unordered_map>

#define ENGINEIO_GLOBAL_CONSTANT(name, value) this->globals->define(name, static_cast<idk::f80>(value));

#define ENGINEIO_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, EngineIO, arg_count)
#define ENGINEIO_INIT_CONSTANTS() \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_A", SDL_SCANCODE_A) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_B", SDL_SCANCODE_B) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_C", SDL_SCANCODE_C) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_D", SDL_SCANCODE_D) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_E", SDL_SCANCODE_E) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F", SDL_SCANCODE_F) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_G", SDL_SCANCODE_G) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_H", SDL_SCANCODE_H) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_I", SDL_SCANCODE_I) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_J", SDL_SCANCODE_J) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_K", SDL_SCANCODE_K) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_L", SDL_SCANCODE_L) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_M", SDL_SCANCODE_M) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_N", SDL_SCANCODE_N) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_O", SDL_SCANCODE_O) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_P", SDL_SCANCODE_P) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Q", SDL_SCANCODE_Q) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_R", SDL_SCANCODE_R) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_S", SDL_SCANCODE_S) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_T", SDL_SCANCODE_T) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_U", SDL_SCANCODE_U) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_V", SDL_SCANCODE_V) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_W", SDL_SCANCODE_W) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_X", SDL_SCANCODE_X) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Y", SDL_SCANCODE_Y) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Z", SDL_SCANCODE_Z) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_1", SDL_SCANCODE_1) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_2", SDL_SCANCODE_2) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_3", SDL_SCANCODE_3) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_4", SDL_SCANCODE_4) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_5", SDL_SCANCODE_5) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_6", SDL_SCANCODE_6) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_7", SDL_SCANCODE_7) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_8", SDL_SCANCODE_8) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_9", SDL_SCANCODE_9) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_0", SDL_SCANCODE_0) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Return", SDL_SCANCODE_RETURN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Escape", SDL_SCANCODE_ESCAPE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Backspace", SDL_SCANCODE_BACKSPACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Tab", SDL_SCANCODE_TAB) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Space", SDL_SCANCODE_SPACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Minus", SDL_SCANCODE_MINUS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Equals", SDL_SCANCODE_EQUALS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_LeftBracket", SDL_SCANCODE_LEFTBRACKET) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_RightBracket", SDL_SCANCODE_RIGHTBRACKET) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Backslash", SDL_SCANCODE_BACKSLASH) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Semicolon", SDL_SCANCODE_SEMICOLON) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Apostrophe", SDL_SCANCODE_APOSTROPHE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Grave", SDL_SCANCODE_GRAVE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Comma", SDL_SCANCODE_COMMA) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Period", SDL_SCANCODE_PERIOD) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Slash", SDL_SCANCODE_SLASH) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_CapsLock", SDL_SCANCODE_CAPSLOCK) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F1", SDL_SCANCODE_F1) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F2", SDL_SCANCODE_F2) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F3", SDL_SCANCODE_F3) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F4", SDL_SCANCODE_F4) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F5", SDL_SCANCODE_F5) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F6", SDL_SCANCODE_F6) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F7", SDL_SCANCODE_F7) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F8", SDL_SCANCODE_F8) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F9", SDL_SCANCODE_F9) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F10", SDL_SCANCODE_F10) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F11", SDL_SCANCODE_F11) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F12", SDL_SCANCODE_F12) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PrintScreen", SDL_SCANCODE_PRINTSCREEN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_ScrollLock", SDL_SCANCODE_SCROLLLOCK) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pause", SDL_SCANCODE_PAUSE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Insert", SDL_SCANCODE_INSERT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Home", SDL_SCANCODE_HOME) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PageUp", SDL_SCANCODE_PAGEUP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Delete", SDL_SCANCODE_DELETE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_End", SDL_SCANCODE_END) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PageDown", SDL_SCANCODE_PAGEDOWN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Right", SDL_SCANCODE_RIGHT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Left", SDL_SCANCODE_LEFT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Down", SDL_SCANCODE_DOWN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Up", SDL_SCANCODE_UP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_NumLockClear", SDL_SCANCODE_NUMLOCKCLEAR) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadDivide", SDL_SCANCODE_KP_DIVIDE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadMultiply", SDL_SCANCODE_KP_MULTIPLY) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadMinus", SDL_SCANCODE_KP_MINUS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadPlus", SDL_SCANCODE_KP_PLUS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadEnter", SDL_SCANCODE_KP_ENTER) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad1", SDL_SCANCODE_KP_1) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad2", SDL_SCANCODE_KP_2) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad3", SDL_SCANCODE_KP_3) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad4", SDL_SCANCODE_KP_4) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad5", SDL_SCANCODE_KP_5) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad6", SDL_SCANCODE_KP_6) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad7", SDL_SCANCODE_KP_7) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad8", SDL_SCANCODE_KP_8) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Pad9", SDL_SCANCODE_KP_9) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadPeriod", SDL_SCANCODE_KP_PERIOD) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Application", SDL_SCANCODE_APPLICATION) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Power", SDL_SCANCODE_POWER) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadEquals", SDL_SCANCODE_KP_EQUALS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F13", SDL_SCANCODE_F13) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F14", SDL_SCANCODE_F14) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F15", SDL_SCANCODE_F15) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F16", SDL_SCANCODE_F16) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F17", SDL_SCANCODE_F17) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F18", SDL_SCANCODE_F18) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F19", SDL_SCANCODE_F19) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F20", SDL_SCANCODE_F20) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F21", SDL_SCANCODE_F21) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F22", SDL_SCANCODE_F22) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F23", SDL_SCANCODE_F23) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_F24", SDL_SCANCODE_F24) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Execute", SDL_SCANCODE_EXECUTE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Help", SDL_SCANCODE_HELP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Menu", SDL_SCANCODE_MENU) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Select", SDL_SCANCODE_SELECT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Stop", SDL_SCANCODE_STOP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Again", SDL_SCANCODE_AGAIN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Undo", SDL_SCANCODE_UNDO) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Cut", SDL_SCANCODE_CUT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Copy", SDL_SCANCODE_COPY) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Paste", SDL_SCANCODE_PASTE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Find", SDL_SCANCODE_FIND) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Mute", SDL_SCANCODE_MUTE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_VolumeUp", SDL_SCANCODE_VOLUMEUP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_VolumeDown", SDL_SCANCODE_VOLUMEDOWN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadComma", SDL_SCANCODE_KP_COMMA) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadLeftParen", SDL_SCANCODE_KP_LEFTPAREN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadRightParen", SDL_SCANCODE_KP_RIGHTPAREN) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadLeftBrace", SDL_SCANCODE_KP_LEFTBRACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadRightBrace", SDL_SCANCODE_KP_RIGHTBRACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadTab", SDL_SCANCODE_KP_TAB) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadBackspace", SDL_SCANCODE_KP_BACKSPACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadA", SDL_SCANCODE_KP_A) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadB", SDL_SCANCODE_KP_B) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadC", SDL_SCANCODE_KP_C) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadD", SDL_SCANCODE_KP_D) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadE", SDL_SCANCODE_KP_E) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadF", SDL_SCANCODE_KP_F) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadXor", SDL_SCANCODE_KP_XOR) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadPower", SDL_SCANCODE_KP_POWER) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadPercent", SDL_SCANCODE_KP_PERCENT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadLess", SDL_SCANCODE_KP_LESS) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadGreater", SDL_SCANCODE_KP_GREATER) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadAmpersand", SDL_SCANCODE_KP_AMPERSAND) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadVerticalBar", SDL_SCANCODE_KP_VERTICALBAR) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadColon", SDL_SCANCODE_KP_COLON) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadHash", SDL_SCANCODE_KP_HASH) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadSpace", SDL_SCANCODE_KP_SPACE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadAt", SDL_SCANCODE_KP_AT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadExclam", SDL_SCANCODE_KP_EXCLAM) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_PadClear", SDL_SCANCODE_KP_CLEAR) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_LeftControl", SDL_SCANCODE_LCTRL) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_LeftShift", SDL_SCANCODE_LSHIFT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_LeftAlt", SDL_SCANCODE_LALT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_RightControl", SDL_SCANCODE_RCTRL) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_RightShift", SDL_SCANCODE_RSHIFT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_RightAlt", SDL_SCANCODE_RALT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_AudioNext", SDL_SCANCODE_AUDIONEXT) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_AudioPrevious", SDL_SCANCODE_AUDIOPREV) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_AudioStop", SDL_SCANCODE_AUDIOSTOP) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_AudioPlay", SDL_SCANCODE_AUDIOPLAY) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_AudioMute", SDL_SCANCODE_AUDIOMUTE) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_WWW", SDL_SCANCODE_WWW) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Mail", SDL_SCANCODE_MAIL) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Calculator", SDL_SCANCODE_CALCULATOR) \
ENGINEIO_GLOBAL_CONSTANT("EngineIO_Key_Computer", SDL_SCANCODE_COMPUTER)

namespace fescript {
ENGINEIO_MODULE(IsKeyPressed, 1)
ENGINEIO_MODULE(IsKeyJustPressed, 1)
ENGINEIO_MODULE(IsKeyReleased, 1)
ENGINEIO_MODULE(IsMouseButtonPressed, 1)
ENGINEIO_MODULE(IsMouseButtonJustPressed, 1)
}

#undef ENGINEIO_MODULE