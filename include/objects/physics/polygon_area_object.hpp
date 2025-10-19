// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "area_object.hpp"
#include <resources/point_resource.hpp>
#include <resources/polygon_resource.hpp>

namespace fresh {
class PolygonAreaObject : public AreaObject, public std::enable_shared_from_this<PolygonAreaObject>  {
public:
  PolygonAreaObject();
  explicit PolygonAreaObject(BBoxResource pos_info);
  explicit PolygonAreaObject(std::shared_ptr<BaseObject> object);
  ~PolygonAreaObject() override = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]]
  bool is_colliding_with(std::shared_ptr<BaseObject> object) noexcept override;

  [[nodiscard]]
  bool is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept override;

  [[nodiscard]]
  bool is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept override;

  [[nodiscard]]
  bool is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "polygonareaobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] PolygonResource& get_polygon_resource() noexcept;
protected:
  PolygonResource _resource;
};
} // namespace fresh