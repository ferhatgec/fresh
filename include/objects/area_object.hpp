// AreaObject is BaseObject that comes with collision support (no polygons for now).
// You can use AreaObject with SpriteObject.

#ifndef FRESHENGINE_AREA_OBJECT_HPP
#define FRESHENGINE_AREA_OBJECT_HPP

#include "base_object.hpp"

namespace fresh {
class AreaObject : public BaseObject {
public:
  friend class FesLoaderResource;

  AreaObject();
  AreaObject(SDL_Rect pos_info);
  AreaObject(std::shared_ptr<BaseObject> base_object);
  ~AreaObject();

  void
  sync() noexcept override;

  __idk_nodiscard
  bool
  is_colliding_with(std::shared_ptr<BaseObject> object) noexcept;

  [[nodiscard]] std::string to_string() {
    return "areaobject";
  }

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;
};
} // namespace fresh

#endif // FRESHENGINE_AREA_OBJECT_HPP
