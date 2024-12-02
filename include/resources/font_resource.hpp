// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

// do not forget that this is fontresource not label etc.
// labels are taking fontresource to render text in which font they want.
// resource classes handles allocated memory, wraps existing structures with RAII.
// makes easier to access things without reallocating them so much.

#include <string>
#include <types/predefined.hpp>
#include <font.hpp>

namespace fresh {
class FontResource {
public:
  friend class LabelObject;

  FontResource() noexcept;
  explicit FontResource(const std::string& font_path, idk::u32 default_size = 16) noexcept;
  ~FontResource() noexcept = default;

  /// FontResource::load_font(std::string) loads given font using FreeType
  /// via fre2d::Font class.
  void load_font(const std::string& font_path) noexcept;

  /// FontResource::get_font_path() is read-only access to _font_path property.
  /// by default, it's  "".
  [[nodiscard]] const std::string& get_font_path() noexcept;

  /// FontResource::get_font_size() is read-only access to _font_size property.
  /// by default, it's 16.
  [[nodiscard]] const idk::u32& get_font_size() const noexcept;

  /// FontResource::set_font_size(unsigned) is write-only access to _font_size property.
  /// it will reconstruct current font.
  void set_font_size(idk::u32 font_size) noexcept;

  /// FontResource::get_font() returns mutable fre2d::Font reference so you can
  /// access fre2d::Font class directly.
  [[nodiscard]] fre2d::Font& get_font() noexcept;
private:
  std::shared_ptr<fre2d::Font> _font;
  idk::u32 _font_size;
  std::string _font_path;
};
} // namespace fresh