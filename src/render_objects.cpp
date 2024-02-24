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

std::vector<std::shared_ptr<BaseObject>> RenderObjects::objects_to_render;
}// namespace fresh
#endif