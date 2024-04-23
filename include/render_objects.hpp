//
// Created by gech on 2/2/2024.
//

#ifndef FRESHENGINE_RENDER_OBJECTS_HPP
#define FRESHENGINE_RENDER_OBJECTS_HPP

#include "objects/base_object.hpp"
#include <vector>
#include <memory>
#include <any>

namespace fresh {
class RenderObjects {
public:
  RenderObjects();
  ~RenderObjects();

  static std::shared_ptr<BaseObject> find(idk::isize object_id) noexcept;
  static std::vector<std::shared_ptr<BaseObject>> objects_to_render; // other inherited classes will be sliced.
  static idk::f80 delta_ms;
};
} // namespace fresh

#endif // FRESHENGINE_RENDER_OBJECTS_HPP
