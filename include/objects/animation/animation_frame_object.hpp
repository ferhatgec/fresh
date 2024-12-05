// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>
#include <types/stringview.hpp>
#include <fescript/fescript_token.hpp>
#include <objects/base_object.hpp>

namespace fresh {
// AnimationFrameObject inherits BaseObject BUT, we don't care about its position_info.
// It's Object just because of sync(), which we will control our animation in, instead of
// calling run_animation() in update(delta).
class AnimationFrameObject : public BaseObject {
public:
  friend class AnimationPlayerObject;
  AnimationFrameObject(idk::f64 start_ms,
                       idk::f64 end_ms,
                       std::shared_ptr<BaseObject> obj,
                       fescript::Object replace_value,
                       const idk::StringViewChar& property) noexcept;
  ~AnimationFrameObject();

  void sync(bool is_member_of_camera = false) noexcept override;

  [[nodiscard]] constexpr const char* to_string() noexcept override {
    return "animationframeobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;
protected:
  idk::f64 _start_ms, _end_ms;
  std::shared_ptr<BaseObject> _obj;
  fescript::Object _replace_value;
  idk::StringViewChar _property;
};
} // namespace fresh