#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
LabelObject::LabelObject() {
  this->_object_def = "labelobject";
  this->_label_render_type = LabelRenderType::Blended;
}

LabelObject::LabelObject(LabelObject* label_object) {
  if(label_object) {
    this->_object_def = "labelobject";
    this->_object_id = label_object->_object_id;
    this->_label_text = label_object->_label_text;
    this->_fg = label_object->_fg;
    this->_bg = label_object->_fg;
    this->_label_render_type = label_object->_label_render_type;
    this->_pos_info = label_object->_pos_info;

    delete label_object;
  } else {
    std::cout << "Engine error: Invalid pointer detected in LabelObject ctor.\n";
  }
}

LabelObject::LabelObject(const FontResource& label_font_resource, const BaseObject& metadata) {
  this->_object_def = "labelobject";
}

LabelObject::LabelObject(FontResource&& label_font_resource, BaseObject&& metadata) {
  this->_object_def = "labelobject";
}

LabelObject::~LabelObject() {
}

void LabelObject::initialize_text(const idk::StringViewChar& label_text,
                                  SDL_Color fg,
                                  SDL_Color bg,
                                  LabelRenderType label_render_type) noexcept {
  this->_label_text = const_cast<idk::StringViewChar&>(label_text);
  this->_fg = fg;
  this->_bg = bg;
  this->_label_render_type = label_render_type;

  this->initialize_label_font_surface();
}

void LabelObject::initialize_text(idk::StringViewChar&& label_text,
                                  SDL_Color fg,
                                  SDL_Color bg,
                                  LabelRenderType label_render_type) noexcept {
  this->_label_text = idk::move(label_text);
  this->_fg = fg;
  this->_bg = bg;
  this->_label_render_type = label_render_type;

  this->initialize_label_font_surface();
}

void LabelObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  this->_render_pos_info = BaseObject::_center_to_top_left_pivot(this->_render_pos_info);
  if(this->_visible &&
    !this->_label_text.is_empty() &&
    !this->_label_font_resource.get_font_path().is_empty() &&
    this->_label_font_resource.get_font_size() > 0)
    SDL_RenderCopyF(Engine::get_instance()->get_window()->get_renderer(),
                 this->_label_font_texture.get_texture(),
                 NULL,
                 &this->_render_pos_info);
  APPLY_DELTAS()
}

__idk_nodiscard
  idk::StringViewChar&
  LabelObject::get_label_text() noexcept {
  return this->_label_text;
}

__idk_nodiscard
  FontResource&
  LabelObject::get_label_font_resource() noexcept {
  return this->_label_font_resource;
}

__idk_nodiscard
  SpriteResource&
  LabelObject::get_label_font_texture() noexcept {
  return this->_label_font_texture;
}

void LabelObject::initialize_label_font_surface() noexcept {
  SDL_Surface* label_surface = nullptr;

  if(!this->get_label_font_resource().get_font()) {
    std::cout << "Engine error: get_font() returns invalid pointer!\n";
  }

  switch(this->_label_render_type) {
  case LabelRenderType::LCD: {
    label_surface = TTF_RenderText_LCD(this->get_label_font_resource().get_font(),
                                       this->_label_text.data(),
                                       this->_fg,
                                       this->_bg);
    break;
  }

  case LabelRenderType::Solid: {
    label_surface = TTF_RenderText_Solid(this->get_label_font_resource().get_font(),
                                         this->_label_text.data(),
                                         this->_fg);
    break;
  }

  case LabelRenderType::Shaded: {
    label_surface = TTF_RenderText_Shaded(this->get_label_font_resource().get_font(),
                                          this->_label_text.data(),
                                          this->_fg,
                                          this->_bg);
    break;
  }

  case LabelRenderType::Blended: {
    label_surface = TTF_RenderText_Blended(this->get_label_font_resource().get_font(),
                                           this->_label_text.data(),
                                           this->_fg);
    break;
  }

  default: {
    std::cout << "Engine error: Reached LabelRenderType out of bounds.\n";
    // using solid as default, but there will never be reached until something breaks up.
    label_surface = TTF_RenderText_Solid(this->get_label_font_resource().get_font(),
                                         this->_label_text.data(),
                                         this->_fg);
    break;
  }
  }

  if(label_surface == nullptr) {
    std::cout << "Engine error: Cannot initialize surface for LabelObject.\n";
    return;
  }

  this->_label_font_texture.get_texture() = SDL_CreateTextureFromSurface(Engine::get_instance()->get_window()->get_renderer(),
                                                                         label_surface);

  SDL_FreeSurface(label_surface);

  if(!this->_label_font_texture.get_texture()) {
    std::cout << "Engine error: Cannot initialize texture for LabelObject.\n";
    return;
  }
}

void LabelObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else if(name.lexeme == "background_red") this->_bg.r = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "background_green") this->_bg.g = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "background_blue") this->_bg.b = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "background_alpha") this->_bg.a = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "foreground_red") this->_fg.r = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "foreground_green") this->_fg.g = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "foreground_blue") this->_fg.b = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "foreground_alpha") this->_fg.a = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "label_text") this->_label_text = std::get<StringIndex>(value).data();
  else if(name.lexeme == "font_size") this->_label_font_resource._font_size = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(name.lexeme == "font_resource") this->_label_font_resource._font_path = std::get<StringIndex>(value).data();
  else {
    std::cout << "Engine [language] error: SpriteObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh