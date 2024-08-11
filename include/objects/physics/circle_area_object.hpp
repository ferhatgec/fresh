#pragma once

#include "area_object.hpp"
#include <resources/circle_resource.hpp>

namespace fresh {
class CircleAreaObject : public AreaObject, public std::enable_shared_from_this<CircleAreaObject>  {
public:
  CircleAreaObject();
  explicit CircleAreaObject(SDL_FRect pos_info);
  explicit CircleAreaObject(std::shared_ptr<BaseObject> object);
  ~CircleAreaObject() override = default;

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<BaseObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<CircleAreaObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<RectangleAreaObject> object) noexcept override;

  __idk_nodiscard
  bool is_colliding_with(std::shared_ptr<PolygonAreaObject> object) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "circleareaobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] CircleResource& get_circle_resource() noexcept;
protected:
  CircleResource _resource;
};
} // namespace fresh