// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <objects/base_object.hpp>
#include <resources/color_resource.hpp>
#include <resources/point_resource.hpp>

#include "resources/bbox_resource.hpp"

// AreaObject is a base class for detecting collisions.
namespace fresh {
class CircleAreaObject;
class RectangleAreaObject;
class PolygonAreaObject;

class AreaObject : public BaseObject {
public:
  friend class FesLoaderResource;

  AreaObject();
  explicit AreaObject(BBoxResource pos_info);
  explicit AreaObject(std::shared_ptr<BaseObject> base_object);
  ~AreaObject() override = default;

  void
  sync(bool is_member_of_camera = false) noexcept override;

  __idk_nodiscard
  virtual bool
  is_colliding_with(std::shared_ptr<BaseObject> object) noexcept;

  __idk_nodiscard
  virtual bool
  is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept;

  __idk_nodiscard
  virtual bool
  is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept;

  __idk_nodiscard
  virtual bool
  is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "areaobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj_1,
                                const std::shared_ptr<RectangleAreaObject>& rect_obj_2) noexcept;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj,
                                const std::shared_ptr<CircleAreaObject>& circle_obj) noexcept;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<CircleAreaObject>& circle_obj_1,
                                const std::shared_ptr<CircleAreaObject>& circle_obj_2) noexcept;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<RectangleAreaObject>& rect_obj,
                                const std::shared_ptr<PolygonAreaObject>& poly_obj) noexcept;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<CircleAreaObject>& circle_obj,
                                const std::shared_ptr<PolygonAreaObject>& poly_obj) noexcept;

  [[nodiscard]]
  static bool is_colliding_with(const std::shared_ptr<PolygonAreaObject>& poly_obj_1,
                                const std::shared_ptr<PolygonAreaObject>& poly_obj_2) noexcept;
private:
  [[nodiscard]]
  static idk::f32 _point_to_line_segment_distance(const idk::f32& p_x, const idk::f32& p_y,
                                                  const PointResource& v, const PointResource& w) noexcept;
protected:
  std::shared_ptr<BaseObject> _collider;
};
} // namespace fresh