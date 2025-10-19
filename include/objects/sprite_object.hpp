// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <resources/sprite_resource.hpp>
#include "base_object.hpp"
#include "rectangle.hpp"
#include "shader_object.hpp"

namespace fresh {
class SpriteObject : public BaseObject, public ShaderObject {
public:
  friend class FesLoaderResource;

  /// SpriteObject::SpriteObject() constructs a new SpriteObject.
  SpriteObject();

  /// SpriteObject::~SpriteObject() destroys already exist SpriteObject.
  ~SpriteObject() override = default;

  /// SpriteObject::sync() handles the draw functionality.
  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] SpriteResource& get_sprite_resource() noexcept;

  [[nodiscard]]
  SpriteResource copy_get_sprite_resource() const noexcept {
    return this->_sprite_resource;
  }

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "spriteobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
  void init_signal() noexcept override;
  void set_rotation(idk::f32 rad_degrees) noexcept override;
  void set_flip_vertically(bool flip_vertically) noexcept override;
  void set_flip_horizontally(bool flip_horizontally) noexcept override;
  void set_ignore_zoom(bool ignore_zoom) noexcept override;

  [[nodiscard]] const bool& get_flip_vertically() const noexcept override;
  [[nodiscard]] const bool& get_flip_horizontally() const noexcept override;

  void notify_x() noexcept override;
  void notify_y() noexcept override;
  void notify_w() noexcept override;
  void notify_h() noexcept override;

  [[nodiscard]] const fre2d::Rectangle& get_rectangle() const noexcept;
  [[nodiscard]] fre2d::Rectangle& get_rectangle_mutable() noexcept;
protected:
  void _base_notify_xy() noexcept;
  void _base_notify_wh() noexcept;

  SpriteResource _sprite_resource;
  idk::f32 _cache_degrees;
  fre2d::Rectangle _rectangle;
};
} // namespace fresh