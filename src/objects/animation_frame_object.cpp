#include "../../include/objects/animation_frame_object.hpp"
#include "../../include/objects/camera_object.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"

namespace fresh {
AnimationFrameObject::AnimationFrameObject(idk::f64 start_ms,
                                           idk::f64 end_ms,
                                           std::shared_ptr <BaseObject> obj,
                                           fescript::Object replace_value,
                                           const idk::StringViewChar& property) noexcept
  : _start_ms{start_ms},
    _end_ms{end_ms},
    _obj{obj},
    _replace_value{replace_value},
    _property{property} {
}

AnimationFrameObject::~AnimationFrameObject() {
}

void AnimationFrameObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  APPLY_DELTAS()
}

[[nodiscard]] void AnimationFrameObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AnimationFrameObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
} // namespace fresh
