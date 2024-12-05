// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "area_object.hpp"

namespace fresh {
class RectangleAreaObject : public AreaObject, public std::enable_shared_from_this<RectangleAreaObject> {
public:
  RectangleAreaObject();
  explicit RectangleAreaObject(BBoxResource pos_info);
  explicit RectangleAreaObject(std::shared_ptr<BaseObject> object);
  ~RectangleAreaObject() override = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<BaseObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "rectangleareaobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
};
} // namespace fresh