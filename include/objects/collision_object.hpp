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
  sync() noexcept override;
};
} // namespace fresh

#endif // FRESHENGINE_COLLISION_OBJECT_HPP
