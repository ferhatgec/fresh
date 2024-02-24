#ifndef FRESHENGINE_ID_RESOURCE_HPP
#define FRESHENGINE_ID_RESOURCE_HPP

#include "../../libs/idk/idk/types/predefined.hpp"

namespace fresh {
namespace id {
static idk::u64 object_id; // stupidly simple way to generate id to assign every object.
                           // changing this probably break object matcher especially AnimationResource.
} // namespace id
} // namespace fresh

#endif // FRESHENGINE_ID_RESOURCE_HPP
