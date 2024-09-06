#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

// TODO: add reverse animation support (run_backwards).
namespace fresh {
AnimationPlayerObject::AnimationPlayerObject(bool replay) noexcept 
  : _replay{replay}, _is_first{true}, _start{false} {
}

AnimationPlayerObject::~AnimationPlayerObject() {
}

void AnimationPlayerObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(!this->_start)
    return;
  if(this->_timer.is_paused())
    return;
  if(!this->is_started()) {
    if(this->_replay || this->_is_first) {
      this->_timer.start();
      this->_current_index = 0;
      this->_is_first = false;
    } else
      return;
  }
  if(const auto ticks = this->_timer.get_ticks(); this->_frames[this->_current_index]._end_ms <= ticks)
    ++this->_current_index;
  this->_process_current_frame();
  if(this->_current_index == this->_frames.size())
    this->_timer.stop();
  APPLY_DELTAS()
}

void AnimationPlayerObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AnimationPlayerObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void AnimationPlayerObject::push_frame(const fresh::AnimationFrameObject& frame) noexcept {
  this->_frames.push_back(frame);
}

void AnimationPlayerObject::run_animation() noexcept {
  if(this->_timer.is_paused())
    this->_timer.unpause();
  this->_start = true;
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
  return this->_timer.is_started();
}

void AnimationPlayerObject::_process_current_frame() noexcept {
  auto& current_frame = this->_frames[this->_current_index];
  if(current_frame._property == "pos_x") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->get_position_info().x = std::get<LongDoubleIndex>(current_frame._replace_value);
  } else if(current_frame._property == "pos_y") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->get_position_info().y = std::get<LongDoubleIndex>(current_frame._replace_value);
  } else if(current_frame._property == "width") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->get_position_info().w = std::get<LongDoubleIndex>(current_frame._replace_value);
  } else if(current_frame._property == "height") {
    MUST_BE_DECIMAL(current_frame._replace_value)
    current_frame._obj->get_position_info().h = std::get<LongDoubleIndex>(current_frame._replace_value);
  } else if(current_frame._property == "visible") {
    MUST_BE_BOOL(current_frame._replace_value)
    current_frame._obj->get_is_visible() = std::get<BoolIndex>(current_frame._replace_value);
  } else if(current_frame._property == "disabled") {
    MUST_BE_BOOL(current_frame._replace_value)
    current_frame._obj->get_is_disabled() = std::get<BoolIndex>(current_frame._replace_value);
  } else if(current_frame._property == "sprite_resource") {
    MUST_BE_STRING(current_frame._replace_value)
    if(auto sprite_ptr = std::dynamic_pointer_cast<fresh::SpriteObject>(current_frame._obj);
      sprite_ptr != nullptr) {
      sprite_ptr->get_sprite_resource().load_resource(std::get<StringIndex>(current_frame._replace_value).data());
    } else {
      std::cout << "Engine error: AnimationFrameObject got non-SpriteObject for sprite_resource.\n";
      std::exit(1);
    }
  }
}

// synchronizes start_ms of (n + 1)th frame with end_ms of nth frame.
void AnimationPlayerObject::synchronize_frames() noexcept {
  for(idk::isize i = 1; i < this->_frames.size(); ++i)
    this->_frames[i]._start_ms = this->_frames[i - 1]._end_ms;
}
} // namespace fresh
