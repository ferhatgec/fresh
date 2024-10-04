#pragma once

// do not forget that this is fontresource not label etc.
// labels are taking fontresource to render text in which font they want.
// resource classes handles allocated memory, wraps existing structures with RAII.
// makes easier to access things without reallocating them so much.

#include <types/stringview.hpp>
#include <SDL_ttf.h>

namespace fresh {
class FontResource {
public:
  friend class LabelObject;

  FontResource();
  FontResource(const idk::StringViewChar& font_path, idk::u32 default_size = 16); // size can be changed later.
  FontResource(idk::StringViewChar&& font_path, idk::u32 default_size = 16);

  ~FontResource();
  
  void
  load_font(const idk::StringViewChar& font_path) noexcept;

  void
  load_font(idk::StringViewChar&& font_path) noexcept;

  __idk_nodiscard
  TTF_Font*&
  get_font() noexcept;

  __idk_nodiscard
  idk::StringViewChar&
  get_font_path() noexcept;

  __idk_nodiscard
  idk::i32&
  get_font_size() noexcept;

  void
  sync_font_size() noexcept;
private:
  TTF_Font* _font = nullptr;
  idk::i32 _font_size { 16_i32 };
  idk::StringViewChar _font_path = "";
  idk::StringViewChar _previous_font_path = "";
};
} // namespace fresh