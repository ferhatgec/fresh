// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/animation/animation_frame_object.hpp>
#include <objects/camera_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

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

void AnimationFrameObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
    this->apply_changes();
}

void AnimationFrameObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AnimationFrameObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
} // namespace fresh
