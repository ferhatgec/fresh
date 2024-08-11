#include <fescript/wrappers/animation/fescript_animation_player_object.hpp>
#include <fescript/fescript_interpreter.hpp>

#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptAnimationPlayerObjectMemberPushFrame::call(fescript::Interpreter& interpreter,
                                                                          std::vector<Object> arguments) {
  ERR_CHECK_ANIMATIONFRAMEOBJECT("AnimationPlayerObject.push_frame", 1)
  this->_self->push_frame(*std::get<FescriptAnimationFrameObjectIndex>(arguments.front()).get());
  return nullptr;
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberRunAnimation::call(fescript::Interpreter& interpreter,
                                                                             std::vector<Object> arguments) {
  this->_self->run_animation();
  return nullptr;
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberPauseAnimation::call(fescript::Interpreter& interpreter,
                                                                               std::vector<Object> arguments) {
  this->_self->pause_animation();
  return nullptr;
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberStopAnimation::call(fescript::Interpreter& interpreter,
                                                                               std::vector<Object> arguments) {
  this->_self->stop_animation();
  return nullptr;
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberSetReplayStatus::call(fescript::Interpreter& interpreter,
                                                                                std::vector<Object> arguments) {
  ERR_CHECK_BOOL("AnimationPlayerObject.set_replay_status()", 1)
  this->_self->set_replay_status(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberIsStarted::call(fescript::Interpreter& interpreter,
                                                                          std::vector<Object> arguments) {
  return this->_self->is_started();
}

__idk_nodiscard Object FescriptAnimationPlayerObjectMemberSynchronizeFrames::call(fescript::Interpreter& interpreter,
                                                                                  std::vector<Object> arguments) {
  this->_self->synchronize_frames();
  return nullptr;
}

AnimationPlayerObjectWrapper::AnimationPlayerObjectWrapper() {
  this->_object_def = "animationplayerobject";
}

AnimationPlayerObjectWrapper::~AnimationPlayerObjectWrapper() noexcept {
}

[[nodiscard]] std::string AnimationPlayerObjectWrapper::to_string() {
  return "animationplayerobject";
}

[[nodiscard]] Object AnimationPlayerObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto animation_player_object = std::make_shared<fresh::AnimationPlayerObject>(false);
  this->_object_id = animation_player_object->get_object_id();
  return std::move(animation_player_object);
}
} // namespace fescript