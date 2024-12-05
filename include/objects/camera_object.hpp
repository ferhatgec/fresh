// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <include/camera.hpp>
#include "base_object.hpp"

namespace fresh {
class CameraObject : public BaseObject {
public:
  friend class FesLoaderResource;
  friend class Engine;

  CameraObject();
  CameraObject(idk::f32 width, idk::f32 height);
  ~CameraObject() override = default;

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "cameraobject";
  }

  /// CameraObject::set_camera_position(PointResource) sets given point as exact camera
  /// position.
  /// note:
  /// ----
  /// do not use CameraObject::get_camera() to set properties;
  /// they are just implementation of camera without synchronizing position and other
  /// properties; just renders them to screen.
  void set_camera_position(const PointResource& pt) noexcept;
  /// CameraObject::move_camera(PointResource) moves current camera position
  /// with given point.
  /// note:
  /// ----
  /// do not use CameraObject::get_camera() to set properties;
  /// they are just implementation of camera without synchronizing position and
  /// other properties; just renders them to screen.
  void move_camera(const PointResource& pt) noexcept;

  void resize_camera(idk::f32 w, idk::f32 h) noexcept;

  [[nodiscard]] const std::unique_ptr<fre2d::Camera>& get_camera() const noexcept;

  void set(const fescript::Token& name, fescript::Object value) override;
protected:
  std::unique_ptr<fre2d::Camera> _camera;
};
} // namespace fresh