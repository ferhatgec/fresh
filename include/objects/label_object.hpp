// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <resources/font_resource.hpp>
#include "base_object.hpp"
#include "label.hpp"
#include "shader_object.hpp"

namespace fresh {
class LabelObject : public BaseObject, public ShaderObject {
public:
  friend class FesLoaderResource;

  LabelObject() noexcept = default;
  ~LabelObject() override = default;

  void initialize_text(
    const std::string& label_text,
    ColorResource fg,
    ColorResource bg
  ) noexcept;

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] const std::string& get_label_text() const noexcept;
  void set_label_text(const std::string& text) noexcept;

  [[nodiscard]] FontResource& get_label_font_resource() noexcept;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "labelobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;

  void set_rotation(idk::f32 rad_degrees) noexcept override;
  void set_flip_vertically(bool flip_vertically) noexcept override;
  void set_flip_horizontally(bool flip_horizontally) noexcept override;
  void set_ignore_zoom(bool ignore_zoom) noexcept override;

  [[nodiscard]] const bool& get_flip_vertically() const noexcept override;
  [[nodiscard]] const bool& get_flip_horizontally() const noexcept override;

  [[nodiscard]] ColorResource& get_background_color() noexcept {
    return this->_bg;
  }

  [[nodiscard]] ColorResource& get_foreground_color() noexcept {
    return this->_fg;
  }
protected:
  ColorResource _bg, _fg;
  std::string _label_text;
  FontResource _label_font_resource;
  fre2d::Label _label;
};
} // namespace fresh