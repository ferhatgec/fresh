#ifndef FRESHENGINE_SPRITE_OBJECT_HPP
#define FRESHENGINE_SPRITE_OBJECT_HPP

#include "../resources/sprite_resource.hpp"
#include "gui/gui_base_object.hpp"
#include "base_object.hpp"

namespace fresh {
class SpriteObject : public BaseObject {
public:
  friend class FesLoaderResource;

  SpriteObject();
  SpriteObject(SpriteObject* sprite_object);
  SpriteObject(const SpriteResource& sprite_resource, const BaseObject& metadata);
  SpriteObject(SpriteResource&& sprite_resource, BaseObject&& metadata);

  ~SpriteObject();

  void
  sync() noexcept override;

  __idk_nodiscard
  SpriteResource&
  get_sprite_resource() noexcept;

  template<typename KeyType>
  KeyType&
  get_property() noexcept {
    return this->get_sprite_resource();
  }

  template<>
  SpriteResource&
  get_property<SpriteResource>() noexcept {
    return this->_sprite_resource;
  }

  template<>
  bool&
  get_property<bool>() noexcept {
    return this->_visible;
  }

  [[nodiscard]] std::string to_string() {
    return "spriteobject";
  }

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;
private:
  __idk_nodiscard
  SDL_BlendMode
  _convert_blend_mode_enum() noexcept;
protected:
#ifdef __FRESH_ENABLE_EDITOR
  std::shared_ptr<GuiBaseObject> _gizmo;
#endif
  bool _still_focus { false };
  SpriteResource _sprite_resource;
};
}

#endif // FRESHENGINE_SPRITE_OBJECT_HPP