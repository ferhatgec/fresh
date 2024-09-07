#pragma once

#include "base_object.hpp"
#include <resources/sprite_resource.hpp>
#include <objects/gui/gui_base_object.hpp>

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
  sync(bool is_sync_with_camera = false) noexcept override;

  __idk_nodiscard
  SpriteResource& get_sprite_resource() noexcept;

  __idk_nodiscard
  SpriteResource copy_get_sprite_resource() const noexcept {
    return this->_sprite_resource;
  }

  [[nodiscard]] std::string to_string() {
    return "spriteobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept override;
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
  idk::f32 _cache_degrees;
};
} // namespace fresh