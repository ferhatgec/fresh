#include <resources/font_resource.hpp>

namespace fresh {
FontResource::FontResource() {
  TTF_Init();
}

FontResource::FontResource(const idk::StringViewChar& font_path, idk::u32 default_size) {
  TTF_Init();
  this->_font = TTF_OpenFont(font_path.data(), default_size);
  this->_font_size = default_size;
  this->_font_path = font_path;
}

FontResource::FontResource(idk::StringViewChar&& font_path, idk::u32 default_size) {
  TTF_Init();
  this->_font_path = idk::move(font_path);
  this->_font = TTF_OpenFont(this->_font_path.data(), default_size);
  this->_font_size = default_size;
}

FontResource::~FontResource() {
  if(this->_font) {
    TTF_Quit();
    TTF_CloseFont(this->_font);
  } else {
    std::cout << "Engine info: FontResource is not initialized with a font.\n";
  }
}

void FontResource::load_font(const idk::StringViewChar& font_path) noexcept {
  if(this->_font) {
    TTF_Quit();
    TTF_CloseFont(this->_font);
  }

  TTF_Init();
  this->_font_path = font_path;
  this->_font = TTF_OpenFont(this->_font_path.data(), this->_font_size);

  if(!this->_font) {
    std::cout << "Engine error: Cannot initialize new font: " << SDL_GetError() << '\n';
  }
}

void FontResource::load_font(idk::StringViewChar&& font_path) noexcept {
  if(this->_font) {
    TTF_Quit();
    TTF_CloseFont(this->_font);
  }

  TTF_Init();
  this->_font_path = idk::move(font_path);
  this->_font = TTF_OpenFont(this->_font_path.data(), this->_font_size);

  if(!this->_font) {
    std::cout << "Engine error: Cannot initialize new font: " << SDL_GetError() << '\n';
  }
}

__idk_nodiscard
  TTF_Font*&
  FontResource::get_font() noexcept {
  return this->_font;
}

__idk_nodiscard
  idk::StringViewChar&
  FontResource::get_font_path() noexcept {
  this->_previous_font_path = this->_font_path;
  return this->_font_path;
}

__idk_nodiscard
  idk::i32&
  FontResource::get_font_size() noexcept {
  return this->_font_size;
}

void FontResource::sync_font_size() noexcept {
  if(!this->_font) {
    std::cout << "Engine error: FontResource is not initialized, trying to sync font size is not possible.\n";
    return;
  }

  if(TTF_SetFontSize(this->_font, this->_font_size) < 0) {
    std::cout << "Engine error: FontResource::sync_font_size() failed!\n";
  }
}
}// namespace fresh