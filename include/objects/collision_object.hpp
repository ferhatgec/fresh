#ifndef FRESHENGINE_COLLISION_OBJECT_HPP
#define FRESHENGINE_COLLISION_OBJECT_HPP

#include "area_object.hpp"

namespace fresh {
class CollisionObject : public AreaObject {
public:
  friend class FesLoaderResource;

  CollisionObject();
  ~CollisionObject();

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "collisionobject";
  }

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;
};
} // namespace fresh

#endif // FRESHENGINE_COLLISION_OBJECT_HPP
