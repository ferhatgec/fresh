#ifndef FRESHENGINE_RENDER_OBJECTS_CPP// headers guards only stands for including
#define FRESHENGINE_RENDER_OBJECTS_CPP// this thing twice will regenerate objects_to_render at different place in memory.              \
                                      // only thing we want is force objects_to_render at a static place, that thing important because \
                                      // we run objects_to_render every frame to sync.
#include "../include/render_objects.hpp"
#include "../include/freshengine.hpp"
#include "../libs/SDL_image/include/SDL_image.h"

namespace fresh {
RenderObjects::RenderObjects() {}
RenderObjects::~RenderObjects() {}
std::shared_ptr<BaseObject> RenderObjects::find(idk::isize object_id) noexcept {
  for(auto& object: RenderObjects::objects_to_render) {
    if(object->get_object_id() == object_id)
      return object;
  }
  std::cout << "Engine error: Cannot find RenderObject member with object id (" << object_id << ").\n";
  std::exit(1);
}

std::vector<std::shared_ptr<BaseObject>> RenderObjects::objects_to_render;
idk::f80 RenderObjects::delta_ms { 0_f80 };
}// namespace fresh
#endif