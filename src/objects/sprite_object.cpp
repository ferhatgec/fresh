#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>
#include <objects/physics/circle_area_object.hpp>

#ifdef __FRESH_ENABLE_EDITOR
#  include <editor/editor.hpp>
#endif

namespace fresh {
SpriteObject::SpriteObject() {
#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif
  this->_object_def = "spriteobject";
  this->_object_id = Engine::get_instance()->get_global_id();
  Engine::get_instance()->increase_global_id();
}

SpriteObject::SpriteObject(SpriteObject* sprite_object) {
#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  if(sprite_object) {
    this->_object_def = sprite_object->_object_def;
    this->_object_id = sprite_object->_object_id;
    this->_pos_info = sprite_object->_pos_info;
    this->_copy_last_pos_info = this->_pos_info;
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
  this->_copy_last_pos_info = this->_pos_info;
  this->_visible = metadata._visible;
  this->_disabled = metadata._disabled;

  this->_sprite_resource = const_cast<SpriteResource&>(sprite_resource);
  this->_object_def = "spriteobject";
  this->_object_id = Engine::get_instance()->get_global_id();

#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  Engine::get_instance()->increase_global_id();
}

SpriteObject::SpriteObject(SpriteResource&& sprite_resource, BaseObject&& metadata) {
  this->_pos_info = idk::move(metadata._pos_info);
  this->_copy_last_pos_info = this->_pos_info;
  this->_visible = idk::move(metadata._visible);
  this->_disabled = idk::move(metadata._disabled);

  this->_sprite_resource = idk::move(sprite_resource);
  this->_object_def = "spriteobject";
  this->_object_id = Engine::get_instance()->get_global_id();

#ifdef __FRESH_ENABLE_EDITOR
  _gizmo = std::make_shared<GuiBaseObject>();
#endif

  Engine::get_instance()->increase_global_id();
}

SpriteObject::~SpriteObject() {
}

// disable gizmos etc when exporting the project. it's easy to make with some booleans or different function
// that being called in exporting process?
void SpriteObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  SDL_SetTextureBlendMode(this->_sprite_resource.get_texture(), this->_convert_blend_mode_enum());
  this->sync_pos_with_camera(is_sync_with_camera);
  this->_render_pos_info = BaseObject::_center_to_top_left_pivot(this->_render_pos_info);
  if(!this->_disabled && this->_visible)
    SDL_RenderCopyF(Engine::get_instance()->get_window()->get_renderer(),
                 this->_sprite_resource.get_texture(), NULL, &this->_render_pos_info);
  APPLY_DELTAS()
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

void SpriteObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else if(name.lexeme == "sprite_resource") this->get_sprite_resource()._texture_path = std::get<StringIndex>(value).data();
  else {
    std::cout << "Engine [language] error: SpriteObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh