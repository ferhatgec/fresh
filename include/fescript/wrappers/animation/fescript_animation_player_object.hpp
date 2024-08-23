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

class AnimationPlayerObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<AnimationPlayerObjectWrapper> {
public:
  AnimationPlayerObjectWrapper();
  ~AnimationPlayerObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript