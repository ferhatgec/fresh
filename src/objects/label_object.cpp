#include "../../include/freshengine.hpp"

namespace fresh {
LabelObject::LabelObject() {
  this->_object_def = "labelobject";
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

void LabelObject::sync() noexcept {
  this->get_position_info();// update deltas
  this->_code.interpret_update();

  if(this->_disabled
     || !this->_visible
     || this->_label_text.is_empty()
     || this->_label_font_resource.get_font_path().is_empty()
     || this->_label_font_resource.get_font_size() <= 0)
    return;

  SDL_RenderCopy(Engine::get_instance()->get_window()->get_renderer(),
                 this->_label_font_texture.get_texture(),
                 NULL,
                 &this->_pos_info);

  for(auto& object : this->_sub_objects) {
    object->get_position_info().x += this->delta_x();
    object->get_position_info().y += this->delta_y();
    object->get_position_info().w += this->delta_w();
    object->get_position_info().h += this->delta_h();

    if(object->_object_def != "cameraobject")// we actually sync cameraobject in engine::update()
      object->sync();
  }
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
    // Solid,
    //   Shaded,
    //   Blended
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

  if(!label_surface) {
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
}// namespace fresh