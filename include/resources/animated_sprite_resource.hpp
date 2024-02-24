#ifndef FRESHENGINE_ANIMATED_SPRITE_RESOURCE_HPP
#define FRESHENGINE_ANIMATED_SPRITE_RESOURCE_HPP

#include "animation_property_resource.hpp"
#include "../objects/sprite_object.hpp"
#include "sprite_resource.hpp"
#include "timer_resource.hpp"
#include <vector>

// using AnimatedSpriteObject is good when only changed thing is SpriteResource.
// it's automatically sync without messing up with AnimationResource (it's directly assign given object, not only the member property)
// this resource stores only
namespace fresh {
using AnimatedSpriteResource = AnimationPropertyResource<SpriteResource, SpriteObject>;
} // namespace fresh
#endif // FRESHENGINE_ANIMATED_SPRITE_RESOURCE_HPP
