#pragma once

#include "base_object.hpp"
#include <resources/sprite_resource.hpp>
#include "rectangle.hpp"

namespace fresh {
class SpriteObject : public BaseObject {
public:
  friend class FesLoaderResource;

  /// SpriteObject::SpriteObject() constructs a new SpriteObject.
  SpriteObject();

  /// SpriteObject::~SpriteObject() destroys already exist SpriteObject.
  ~SpriteObject() override = default;

  /// SpriteObject::sync() handles the draw functionality.
  void sync() noexcept override;

  [[nodiscard]] SpriteResource& get_sprite_resource() noexcept;

  __idk_nodiscard
  SpriteResource copy_get_sprite_resource() const noexcept {
    return this->_sprite_resource;
  }

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "spriteobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;
  void set_rotation(idk::f32 rad_degrees) noexcept override;
protected:
  SpriteResource _sprite_resource;
  idk::f32 _cache_degrees;
  fre2d::Rectangle _rectangle;
  fre2d::Shader _shader;
};
} // namespace fresh