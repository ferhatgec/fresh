// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

// TODO: add reverse animation support (run_backwards).
namespace fresh {
AnimationPlayerObject::AnimationPlayerObject(bool replay) noexcept
  : _replay{replay},
    _is_first{true},
    _start{false},
    _current_index{0},
    _previous_index{-1} {}

void AnimationPlayerObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  if(!this->_start)
    return;
  if(this->_timer.paused())
    return;
  if(!this->is_started()) {
    if(this->_replay || this->_is_first) {
      this->_timer.start();
      this->_current_index = 0;
      this->_is_first = false;
    } else
      return;
  }
  if(const auto ticks = this->_timer.get_ticks(); this->_frames[this->_current_index]._end_ms <= ticks) {
    this->increase_frame();
  }
  if (this->get_delta_frame() != 0) {
    this->_process_current_frame();
  }
  this->apply_changes();
}

void AnimationPlayerObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AnimationPlayerObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void AnimationPlayerObject::push_frame(const AnimationFrameObject& frame) noexcept {
  this->_frames.push_back(frame);
}

void AnimationPlayerObject::run_animation() noexcept {
  if (this->_timer.started()) {
    return;
  }
  this->_start = true;
  if(this->_timer.paused()) {
    this->_timer.resume();
    return;
  }
  this->_timer.start();
  this->_current_index = 0;
}

void AnimationPlayerObject::pause_animation() noexcept {
  this->_timer.pause();
  // this->_start = false;
}

void AnimationPlayerObject::stop_animation() noexcept {
  this->_timer.stop();
  this->_current_index = 0;
  this->_process_current_frame();
  this->_start = false;
}

void AnimationPlayerObject::set_replay_status(bool replay) noexcept {
  this->_replay = replay;
  //if(!this->is_started()) {
  //  this->run_animation();
  //}
}

bool AnimationPlayerObject::is_started() noexcept {
  return this->_timer.started();
}

void AnimationPlayerObject::_process_current_frame() noexcept {
  if(this->_current_index == this->_frames.size()) {
    this->_timer.stop();
    this->_start = false;
    return;
  }
  auto& current_frame = this->_frames[this->_current_index];
  if(current_frame._property == "pos_x") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->set_x(std::get<LongDoubleIndex>(current_frame._replace_value));
  } else if(current_frame._property == "pos_y") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->set_y(std::get<LongDoubleIndex>(current_frame._replace_value));
  } else if(current_frame._property == "width") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->set_w(std::get<LongDoubleIndex>(current_frame._replace_value));
  } else if(current_frame._property == "height") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->set_h(std::get<LongDoubleIndex>(current_frame._replace_value));
  } else if(current_frame._property == "visible") {
    MUST_BE_BOOL(current_frame._replace_value)
    current_frame._obj->set_visible(std::get<BoolIndex>(current_frame._replace_value));
  } else if(current_frame._property == "disabled") {
    MUST_BE_BOOL(current_frame._replace_value)
    current_frame._obj->set_disabled(std::get<BoolIndex>(current_frame._replace_value));
  } else if(current_frame._property == "sprite_resource") {
    MUST_BE_STRING(current_frame._replace_value)
    if(const auto& sprite_ptr = std::static_pointer_cast<fresh::SpriteObject>(current_frame._obj);
      sprite_ptr != nullptr) {
      sprite_ptr->get_sprite_resource().load_resource(
        std::get<StringIndex>(current_frame._replace_value),
        sprite_ptr
      );
    } else {
      std::cout << "Engine error: AnimationFrameObject got non-SpriteObject for sprite_resource.\n";
      std::exit(1);
    }
  }
}

// synchronizes start_ms of (n + 1)th frame with end_ms of nth frame.
void AnimationPlayerObject::synchronize_frames() noexcept {
  for (idk::isize i = 1; i < this->_frames.size(); ++i)
    this->_frames[i]._start_ms = this->_frames[i - 1]._end_ms;
}

void AnimationPlayerObject::increase_frame() noexcept {
  this->_previous_index = this->_current_index;
  ++this->_current_index;
}

void AnimationPlayerObject::decrease_frame() noexcept {
  this->_previous_index = this->_current_index;
  --this->_current_index;
}

void AnimationPlayerObject::reset_frame() noexcept {
  this->_previous_index = this->_current_index;
  this->_current_index = 0;
}

[[nodiscard]] const idk::isize& AnimationPlayerObject::get_frame() const noexcept {
  return this->_current_index;
}

[[nodiscard]] idk::isize AnimationPlayerObject::get_delta_frame() const noexcept {
  return this->_current_index - this->_previous_index;
}
} // namespace fresh
