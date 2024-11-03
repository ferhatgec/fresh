#pragma once

#include <resources/font_resource.hpp>
#include <resources/sprite_resource.hpp>
#include "base_object.hpp"

#include "label.hpp"

namespace fresh {
class LabelObject : public BaseObject {
public:
  friend class FesLoaderResource;

  LabelObject() noexcept = default;
  ~LabelObject() override = default;

  void initialize_text(
    const std::string& label_text,
    ColorResource fg,
    ColorResource bg
  ) noexcept;

  void sync() noexcept override;

  [[nodiscard]] const std::string& get_label_text() const noexcept;
  void set_label_text(const std::string& text) noexcept;

  [[nodiscard]] FontResource& get_label_font_resource() noexcept;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "labelobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;

  void set_rotation(idk::f32 rad_degrees) noexcept override;

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
  fre2d::Shader _shader;
  fre2d::Label _label;
};
} // namespace fresh