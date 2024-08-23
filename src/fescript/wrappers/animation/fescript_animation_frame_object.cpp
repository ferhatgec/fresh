#include <fescript/wrappers/animation/fescript_animation_frame_object.hpp>
#include <fescript/fescript_interpreter.hpp>

#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
AnimationFrameObjectWrapper::AnimationFrameObjectWrapper() {
  this->_object_def = "animationframeobject";
}

AnimationFrameObjectWrapper::~AnimationFrameObjectWrapper() noexcept {
}

[[nodiscard]] std::string AnimationFrameObjectWrapper::to_string() {
  return "animationframeobject";
}

[[nodiscard]] Object AnimationFrameObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: apply type checking here. function would crash if types are not satisfied.
  std::shared_ptr<fresh::BaseObject> obj;
  switch(arguments[2].index()) {
    case FescriptBaseObjectIndex: { obj = std::get<FescriptBaseObjectIndex>(arguments[2]); break; }
    case FescriptSpriteObjectIndex: { obj = std::get<FescriptSpriteObjectIndex>(arguments[2]); break; }
    case FescriptLabelObjectIndex: { obj = std::get<FescriptLabelObjectIndex>(arguments[2]); break; }
    case FescriptAreaObjectIndex: { obj = std::get<FescriptAreaObjectIndex>(arguments[2]); break; }
    case FescriptCameraObjectIndex: { obj = std::get<FescriptCameraObjectIndex>(arguments[2]); break; }
    case FescriptAnimationPlayerObjectIndex: { obj = std::get<FescriptAnimationPlayerObjectIndex>(arguments[2]); break; }
    case FescriptAnimationFrameObjectIndex: { obj = std::get<FescriptAnimationFrameObjectIndex>(arguments[2]); break; }
    default: {
      std::cout << "Engine [language] error: AnimationFrameObject(,,object,,): object must be inherited by BaseObject.\n";
      std::exit(1);
    }
  }
  auto animation_frame_object = std::make_shared<fresh::AnimationFrameObject>(
    std::get<LongDoubleIndex>(arguments[0]), // start_ms
      std::get<LongDoubleIndex>(arguments[1]), // end_ms
      obj, // object
      arguments[3], // replace_value
      std::get<StringIndex>(arguments[4]).data() // property
    );
  this->_object_id = animation_frame_object->get_object_id();
  return std::move(animation_frame_object);
}
} // namespace fescript