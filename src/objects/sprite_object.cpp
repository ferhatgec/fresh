#include "../../include/freshengine.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"

#ifdef __FRESH_ENABLE_EDITOR
#include "../../include/editor/editor.hpp"
#endif

namespace fresh {
SpriteObject::SpriteObject() {
#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif
  this->_object_def = "spriteobject";
  this->_object_id = id::object_id;
  ++id::object_id;
}

SpriteObject::SpriteObject(SpriteObject* sprite_object) {
#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  if(sprite_object) {
    this->_object_def = sprite_object->_object_def;
    this->_object_id = sprite_object->_object_id;
    this->_pos_info = sprite_object->_pos_info;
    this->_visible = sprite_object->_visible;
    this->_disabled = sprite_object->_disabled;

    this->_sprite_resource = sprite_object->_sprite_resource;

    delete sprite_object;
  } else {
    std::cout << "Engine error: Invalid pointer detected in SpriteObject ctor!\n";
  }
}

SpriteObject::SpriteObject(const SpriteResource& sprite_resource, const BaseObject& metadata) {
  this->_pos_info = metadata._pos_info;
  this->_visible = metadata._visible;
  this->_disabled = metadata._disabled;

  this->_sprite_resource = const_cast<SpriteResource&>(sprite_resource);
  this->_object_def = "spriteobject";
  this->_object_id = id::object_id;

#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  ++id::object_id;
}

SpriteObject::SpriteObject(SpriteResource&& sprite_resource, BaseObject&& metadata) {
  this->_pos_info = idk::move(metadata._pos_info);
  this->_visible = idk::move(metadata._visible);
  this->_disabled = idk::move(metadata._disabled);

  this->_sprite_resource = idk::move(sprite_resource);
  this->_object_def = "spriteobject";
  this->_object_id = id::object_id;

#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  ++id::object_id;
}

SpriteObject::~SpriteObject() {
}

// disable gizmos etc when exporting the project. it's easy to make with some booleans or different function
// that being called in exporting process?
void SpriteObject::sync() noexcept {
#ifdef __FRESH_ENABLE_EDITOR
  _gizmo->get_position_info() = this->get_position_info();// update deltas
#endif
  this->_code.interpret_update();

  SDL_SetTextureBlendMode(this->_sprite_resource.get_texture(), this->_convert_blend_mode_enum());

  if(this->_disabled || !this->_visible)
    return;

  SDL_RenderCopy(Engine::get_instance()->get_window()->get_renderer(),
                 this->_sprite_resource.get_texture(), NULL, &this->_pos_info);

  for(auto& object : this->_sub_objects) {
    object->get_position_info().x += this->delta_x();
    object->get_position_info().y += this->delta_y();
    object->get_position_info().w += this->delta_w();
    object->get_position_info().h += this->delta_h();

    if(object->_object_def != "cameraobject")// we actually sync cameraobject in engine::update()
      object->sync();
  }

#ifdef __FRESH_ENABLE_EDITOR
  if(_gizmo->is_mouse_hover() || Editor::_editor_focus_group_id == this->_object_id) {
    if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_RIGHT)) {
      this->get_position_info().x += 3;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_LEFT)) {
      this->get_position_info().x -= 3;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_UP)) {
      this->get_position_info().y -= 3;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_DOWN)) {
      this->get_position_info().y += 3;
    } else if(Engine::get_instance()->get_mouse_input().is_button_pressed(SDL_BUTTON_LEFT)
              || Editor::_editor_focus_group_id == this->_object_id) {
      Editor::_editor_focus_group_id = this->_object_id;
      SDL_Rect gizmo_x, gizmo_y;
      auto coords = this->get_position_info();
      gizmo_x.w = 64;
      gizmo_x.h = 16;
      gizmo_y.w = 16;
      gizmo_y.h = 64;

      gizmo_x.x = coords.x + coords.w / 2;
      gizmo_x.y = coords.y + coords.h / 2;

      gizmo_y.x = coords.x + coords.w / 2;
      gizmo_y.y = (coords.y + coords.h / 2) - 56;

      SDL_Rect _draw = this->get_position_info();

      _draw.w += 5;
      _draw.h += 5;

      SDL_RenderDrawRect(Engine::get_instance()->get_window()->get_renderer(),
                         &_draw);
      SDL_RenderCopy(Engine::get_instance()->get_window()->get_renderer(),
                     Editor::_gizmo_x_axis, NULL, &gizmo_x);
      SDL_RenderCopy(Engine::get_instance()->get_window()->get_renderer(),
                     Editor::_gizmo_y_axis, NULL, &gizmo_y);
    }
  }
#endif
}

__idk_nodiscard
  SpriteResource&
  SpriteObject::get_sprite_resource() noexcept {
  return this->_sprite_resource;
}

__idk_nodiscard
  SDL_BlendMode
  SpriteObject::_convert_blend_mode_enum() noexcept {
  switch(this->_sprite_resource.get_blend_mode()) {
  case SpriteBlendMode::None:
    return SDL_BLENDMODE_NONE;

  case SpriteBlendMode::Alpha:
    return SDL_BLENDMODE_BLEND;

  case SpriteBlendMode::Additive:
    return SDL_BLENDMODE_ADD;

  case SpriteBlendMode::Modulate:
    return SDL_BLENDMODE_MOD;

  case SpriteBlendMode::Multiply:
    return SDL_BLENDMODE_MUL;

  default: {// never reach
    std::cout << "Engine warning: Reached SpriteBlendMode out of bounds.\n";
    return SDL_BLENDMODE_NONE;
  }
  }
}

[[nodiscard]] void SpriteObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else if(name.lexeme == "sprite_resource") {
    this->get_sprite_resource()._texture_path = std::get<StringIndex>(value).data();
    // TODO: wrap a function that handles load_resource in fescript. for now, we automatically load that resource.
    this->get_sprite_resource().load_resource(this->get_sprite_resource()._texture_path);
  } else {
    std::cout << "Engine [language] error: SpriteObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh