#pragma once

#include "animation_frame_object.hpp"
#include <resources/timer_resource.hpp>
#include <vector>

#define MUST_BE_ERROR(obj_value, type_index, error_msg) if(##obj_value.index() != type_index) { std::cout << "Given AnimationPlayerResource frame must be " #error_msg "\n"; std::exit(1); }
#define MUST_BE_STRING(obj_value) MUST_BE_ERROR(##obj_value, StringIndex, "string")
#define MUST_BE_DECIMAL(obj_value) MUST_BE_ERROR(##obj_value, LongDoubleIndex, "decimal")
#define MUST_BE_BOOL(obj_value) MUST_BE_ERROR(##obj_value, BoolIndex, "bool")
#define MUST_BE_NIL(obj_value) MUST_BE_ERROR(##obj_value, NullptrIndex, "nil")
#define MUST_BE_BUILTIN_FUNCTION(obj_value) MUST_BE_ERROR(##obj_value, FescriptFunctionIndex, "built-in function")
#define MUST_BE_CLASS(obj_value) MUST_BE_ERROR(##obj_value, FescriptClassIndex, "class")
#define MUST_BE_INSTANCE(obj_value) MUST_BE_ERROR(##obj_value, FescriptInstanceIndex, "instance")
#define MUST_BE_ARRAY(obj_value) MUST_BE_ERROR(##obj_value, FescriptArrayIndex, "array")
#define MUST_BE_DICT(obj_value) MUST_BE_ERROR(##obj_value, FescriptDictIndex, "dict")
#define MUST_BE_CALLABLE(obj_value) MUST_BE_ERROR(##obj_value, FescriptCallableIndex, "callable")
#define MUST_BE_BASEOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptBaseObjectIndex, "baseobject")
#define MUST_BE_SPRITEOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptSpriteObjectIndex, "spriteobject")
#define MUST_BE_LABELOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptLabelObjectIndex, "labelobject")
#define MUST_BE_AREAOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptAreaObjectIndex, "areaobject")
#define MUST_BE_COLLISIONOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptCollisionObjectIndex, "collisionobject")
#define MUST_BE_CAMERAOBJECT(obj_value) MUST_BE_ERROR(##obj_value, FescriptCameraObjectIndex, "cameraobject")

namespace fresh {
class AnimationPlayerObject : public BaseObject {
public:
  AnimationPlayerObject();
  AnimationPlayerObject(bool replay = false) noexcept;
  ~AnimationPlayerObject();

  void sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "animationplayerobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  void push_frame(const AnimationFrameObject& frame) noexcept;
  void run_animation() noexcept;
  void pause_animation() noexcept;
  void stop_animation() noexcept;
  void set_replay_status(bool replay) noexcept;
  bool is_started() noexcept;

  void synchronize_frames() noexcept;
private:
  void _process_current_frame() noexcept;
protected:
  std::vector<AnimationFrameObject> _frames;
  bool _replay;
  bool _is_ended;
  bool _is_first;
  TimerResource _timer;
  idk::isize _current_index;
  bool _start;
};
} // namespace fresh