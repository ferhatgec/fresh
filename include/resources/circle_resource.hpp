// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>

namespace fresh {
class CircleResource {
public:
  friend class CircleObject;

  explicit CircleResource(
    idk::f32 radius = 36.f,
    idk::f32 thickness = 1.f,
    bool filled = true
  ) noexcept;

  ~CircleResource() noexcept = default;

  [[nodiscard]] const idk::f32& get_radius() const noexcept;
  [[nodiscard]] const bool& get_filled() const noexcept;
  [[nodiscard]] const idk::f32& get_thickness() const noexcept;

  void set_radius(idk::f32 radius) noexcept;
  void set_filled(bool filled) noexcept;
  auto set_thickness(idk::f32 thickness) noexcept -> void;
private:
  idk::f32 _radius, _thickness;
  bool _is_filled;
};
} // namespace fresh