// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <resources/clipboard_resource.hpp>
#include <freshengine.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace fresh {
[[nodiscard]] const std::string& ClipboardResource::get_clipboard_data() noexcept {
  this->sync_clipboard_data();
  return this->_clipboard_data;
}

void ClipboardResource::set_clipboard_data(const std::string& text) noexcept {
  glfwSetWindowTitle(
    Engine::get_instance()->get_window()->get_raw_window(),
    text.c_str()
  );
}

void ClipboardResource::sync_clipboard_data() noexcept {
  this->_clipboard_data = glfwGetClipboardString(
    Engine::get_instance()->get_window()->get_raw_window()
  );
}
}// namespace fresh