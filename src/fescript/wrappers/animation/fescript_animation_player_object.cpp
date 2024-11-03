#include <fescript/wrappers/animation/fescript_animation_player_object.hpp>
#include <fescript/fescript_interpreter.hpp>

#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptAnimationPlayerObjectMemberPushFrame::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_ANIMATIONFRAMEOBJECT("AnimationPlayerObject.push_frame", 1)
  this->_self->push_frame(*std::get<FescriptAnimationFrameObjectIndex>(arguments.front()).get());
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberRunAnimation::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->run_animation();
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberPauseAnimation::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->pause_animation();
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberStopAnimation::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->stop_animation();
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberSetReplayStatus::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("AnimationPlayerObject.set_replay_status()", 1)
  this->_self->set_replay_status(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberIsStarted::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->_self->is_started();
}

[[nodiscard]] Object FescriptAnimationPlayerObjectMemberSynchronizeFrames::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->synchronize_frames();
  return nullptr;
}

[[nodiscard]] Object FescriptAnimationPlayerObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto animation_player_object = std::make_shared<fresh::AnimationPlayerObject>(false);
  this->_object_id = animation_player_object->get_id();
  return std::move(animation_player_object);
}
} // namespace fescript