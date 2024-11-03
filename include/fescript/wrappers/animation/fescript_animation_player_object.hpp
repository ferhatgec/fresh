#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define ANIMATION_PLAYER_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AnimationPlayerObjectMember, arg_count)

/// @namespace fescript
/// @brief Global Fescript namespace.
namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(PushFrame, AnimationPlayerObjectMember, 1, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(RunAnimation, AnimationPlayerObjectMember, 0, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseAnimation, AnimationPlayerObjectMember, 0, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopAnimation, AnimationPlayerObjectMember, 0, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(SetReplayStatus, AnimationPlayerObjectMember, 1, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(IsStarted, AnimationPlayerObjectMember, 0, fresh::AnimationPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(SynchronizeFrames, AnimationPlayerObjectMember, 0, fresh::AnimationPlayerObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, AnimationPlayerObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript