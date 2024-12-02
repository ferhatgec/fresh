// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "bbox_resource.hpp"
#include "sprite_resource.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// cursorresource is not an object,
// it maybe seems much better to use SpriteObject instead of SpriteResource with SDL_Rect but
// we don't need any position info of our cursor at *scene*.
namespace fresh {
class CursorResource {
public:
  enum class CursorMode {
    Disabled,
    Hidden,
    Normal
  };
  CursorResource() noexcept;
  ~CursorResource() noexcept;

  /// CursorResource::get_position() returns current local position of cursor.
  /// ----
  /// note: it's currently lose precision due double to float cast.
  [[nodiscard]] const PointResource& get_position() noexcept;

  /// CursorResource::get_w() returns current width of cursor.
  /// returns -1 if no cursor attached.
  [[nodiscard]] const idk::i32& get_w() const noexcept;

  /// CursorResource::get_w() returns current width of cursor.
  /// returns -1 if no cursor attached.
  [[nodiscard]] const idk::i32& get_h() const noexcept;

  /// CursorResource::get_mode() returns current mode of cursor.
  /// it can be Disabled, Hidden or Normal.
  [[nodiscard]] const CursorMode& get_mode() const noexcept;

  /// CursorResource::set_position(BBoxResource) is write-only access
  /// to _pos_info property.
  void set_position(const PointResource& pos) noexcept;

  /// CursorResource::load_sprite(std::string) loads image from specified file path;
  /// then creates a cursor.
  void load_sprite(const std::string& sprite_path, idk::i32 w = -1, idk::i32 h = -1) noexcept;

  /// CursorResource::sync_position() calls related glfw functions
  /// to get current cursor position. it's called directly when
  /// get_position() called.
  void sync_position() noexcept;

  /// CursorResource::sync_mode() calls related glfw functions to
  /// get current cursor mode. it does not been called directly when
  /// get_mode() being called.
  void sync_mode() noexcept;

  /// CursorResource::set_mode(CursorMode) is write-only access to _mode property.
  /// it can be Disabled, Hidden or Normal.
  void set_mode(CursorMode mode) noexcept;

  [[nodiscard]] glm::vec2 get_ndc() noexcept;
  [[nodiscard]] glm::vec2 get_world_space_position() noexcept;
private:
  GLFWimage _sprite;
  GLFWcursor* _cursor;
  PointResource _pos;
  CursorMode _mode;
};
} // namespace fresh