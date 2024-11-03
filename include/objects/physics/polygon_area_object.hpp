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
  sync() noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<BaseObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept override;

  __idk_nodiscard
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