#include <resources/clipboard_resource.hpp>
#include <SDL.h>

namespace fresh {
ClipboardResource::ClipboardResource() {
}

ClipboardResource::~ClipboardResource() {
}

__idk_nodiscard
idk::StringViewChar&
ClipboardResource::get_clipboard_data() noexcept {
  this->sync_clipboard_data();
  return this->_clipboard_data;
}

void ClipboardResource::set_clipboard_data() noexcept {
  if(SDL_SetClipboardText(this->_clipboard_data.data()) < 0) {
    std::cout << "Engine error: ClipboardResource::set_clipboard_data() is failed.\n";
  }
}

void ClipboardResource::sync_clipboard_data() noexcept {
  auto clipboard_text = SDL_GetClipboardText();
  this->_clipboard_data = clipboard_text;
  SDL_free(clipboard_text);
}
}// namespace fresh