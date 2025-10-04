// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "base_object.hpp"
#include <include/light.hpp>

namespace fresh {
class PointLightObject : public BaseObject {
public:
  friend class FesLoaderResource;

  PointLightObject() noexcept;

  PointLightObject(
    PointResource pos,
    glm::vec3 ambient,
    glm::vec3 diffuse,
    float constant,
    float linear,
    float quadratic
  ) noexcept;

  ~PointLightObject() override = default;

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "pointlightobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] fre2d::PointLight& get_point_light() noexcept;
  [[nodiscard]] int get_point_light_index() const noexcept;

  void notify_x() noexcept override;
  void notify_y() noexcept override;
  void notify_disabled() noexcept override;
  void notify_visible() noexcept override;

  void init_signal() noexcept override;
private:
  void _base_notify_xy() noexcept;
  fre2d::PointLight _pt;
  bool _sent;
  int _lm_index;
};
} // namespace fresh