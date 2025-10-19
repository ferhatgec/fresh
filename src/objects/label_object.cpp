// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <log/log.hpp>
#include <fescript/fescript_array.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <freshengine.hpp>

namespace fresh {
void LabelObject::initialize_text(const std::string& label_text,
                                  ColorResource fg,
                                  ColorResource bg) noexcept {
  this->_label_text = label_text;
  this->_fg = fg;
  this->_bg = bg;
}

void LabelObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(this->_visible) {
    this->_label.draw(this->_shader, FreshInstance->get_camera()->get_camera(), FreshInstance->get_light_manager());
  }
  this->apply_changes();
}

[[nodiscard]] const std::string& LabelObject::get_label_text() const noexcept {
  return this->_label_text;
}

void LabelObject::set_label_text(const std::string& text) noexcept {
  this->_label_text = text;
}

[[nodiscard]] FontResource& LabelObject::get_label_font_resource() noexcept {
  return this->_label_font_resource;
}

void LabelObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else if (name.lexeme == "background_red") this->_bg._r =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "background_green") this->_bg._g =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "background_blue") this->_bg._b =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "background_alpha") this->_bg._a =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "foreground_red") this->_fg._r =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "foreground_green") this->_fg._g =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "foreground_blue") this->_fg._b =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "foreground_alpha") this->_fg._a =
      static_cast<idk::f32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme == "label_text") this->_label_text =
      std::get<StringIndex>(value);
  else if (name.lexeme == "font_size") this->_label_font_resource._font_size =
      static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if (name.lexeme ==
           "font_resource") this->_label_font_resource._font_path =
      std::get<StringIndex>(value);
  else {
    std::cout << "Engine [language] error: SpriteObject has no field named as '"
              << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void LabelObject::init_signal() noexcept {
  this->_label.initialize_label(
    this->_label_font_resource.get_font(),
    this->_label_text.data(),
    glm::vec2{ this->_pos_info.get_x(), this->_pos_info.get_y() },
    glm::vec4{
      this->_fg.get_red(),
      this->_fg.get_green(),
      this->_fg.get_blue(),
      this->_fg.get_alpha()
    }
  );
  this->init_shader(label_shader_key);
  this->_initialized = true;
}

void LabelObject::set_rotation(idk::f32 rad_degrees) noexcept {
  this->_rotation_degrees = rad_degrees;
}

void LabelObject::set_flip_vertically(bool flip_vertically) noexcept {
  this->_label.set_flip_vertically(flip_vertically);
}

void LabelObject::set_flip_horizontally(bool flip_horizontally) noexcept {
  this->_label.set_flip_horizontally(flip_horizontally);
}

void LabelObject::set_ignore_zoom(bool ignore_zoom) noexcept {
  this->_label.set_ignore_zoom(ignore_zoom);
}

[[nodiscard]] const bool& LabelObject::get_flip_vertically() const noexcept {
  return this->_label.get_flip_vertically();
}

[[nodiscard]] const bool& LabelObject::get_flip_horizontally() const noexcept {
  return this->_label.get_flip_horizontally();
}
}  // namespace fresh