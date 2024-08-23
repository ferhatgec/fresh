#pragma once

#include "body_object.hpp"
#include <resources/polygon_resource.hpp>

namespace fresh {
class PolygonBodyObject : public BodyObject {
public:
  PolygonBodyObject(const b2WorldId& world_id, SDL_FRect pos, PolygonResource vertices, bool is_static_body = BodyObject::IsStaticBodyDefault);
  ~PolygonBodyObject() override = default;

  void sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "polygonbodyobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  void set_is_static_body(bool is_static_body) noexcept override;
private:
  void _create_body() noexcept;
protected:
  PolygonResource _vertices;
};
} // namespace fresh