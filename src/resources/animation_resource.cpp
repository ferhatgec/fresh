#ifndef FRESHENGINE_ANIMATION_RESOURCE_CPP
#define FRESHENGINE_ANIMATION_RESOURCE_CPP

#include "../../include/resources/animation_resource.hpp"
#include "../../include/objects/base_object.hpp"
#include <any>

namespace fresh {
template<typename KeyType>
AnimationResource<KeyType>::AnimationResource() {
}

template<typename KeyType>
AnimationResource<KeyType>::~AnimationResource() {
}

template<typename KeyType>
void AnimationResource<KeyType>::init_animation(bool loop) noexcept {
  this->_loop = loop;
  this->sync_render_objects();
}

template<typename KeyType>
void AnimationResource<KeyType>::run_animation() noexcept {
  if(!this->_timer.is_started() || ((this->_animation_frame.size() - 1) < this->_current_index)) {
    if((this->_animation_frame.size() - 1) == this->_current_index) {
      if(this->_ended) {
        if(!_loop) {
          this->_reset_to_first_state();
          return;
        }
      }

      this->_reset_to_first_state();
      this->_ended = true;

      if(_loop) {
        this->_timer.stop();
        this->_timer.start();
        this->_current_index = 0;
      } else {
        this->_timer.stop();
      }

      return;
    }

    this->_timer.start();
    this->_current_index = 0;
  } else {
    if(auto _tick = this->_timer.get_ticks();
       (_tick < this->_animation_frame[this->_current_index].get_end_ms())
       && (_tick >= this->_animation_frame[this->_current_index].get_start_ms())) {
      for(idk::isize i = 0; i < fresh::RenderObjects::objects_to_render.size(); ++i) {
        if(!fresh::RenderObjects::objects_to_render[i])
          continue;

        if(fresh::RenderObjects::objects_to_render[i]->get_object_id()
           == this->_animation_frame[this->_current_index].get_object_id()) {
          fresh::RenderObjects::objects_to_render[i] = dynamic_cast<BaseObject*>(this->_animation_frame[this->_current_index].get_assignable_object());
          ++this->_current_index;
          break;
        }
      }
    }
  }
}

template<typename KeyType>
void AnimationResource<KeyType>::pause_animation() noexcept {
}

template<typename KeyType>
void AnimationResource<KeyType>::stop_animation() noexcept {
}

template<typename KeyType>
void AnimationResource<KeyType>::push_animation_key(AnimationKeyResource<KeyType>& animation_key) noexcept {
  this->_animation_frame.push_back(animation_key);
}

template<typename KeyType>
void AnimationResource<KeyType>::push_animation_key(AnimationKeyResource<KeyType>&& animation_key) noexcept {
  this->_animation_frame.push_back(idk::move(animation_key));
}

template<typename KeyType>
void AnimationResource<KeyType>::sync_render_objects() noexcept {
}

template<typename KeyType>
__idk_nodiscard
  TimerResource&
  AnimationResource<KeyType>::get_timer_resource() noexcept {
  return this->_timer;
}

template<typename KeyType>
void AnimationResource<KeyType>::_reset_to_first_state() noexcept {
  for(idk::isize i = 0; i < fresh::RenderObjects::objects_to_render.size(); ++i) {
    if(!fresh::RenderObjects::objects_to_render[i])
      continue;

    if(fresh::RenderObjects::objects_to_render[i]->get_object_id()
       == this->_animation_frame[0].get_object_id()) {
      fresh::RenderObjects::objects_to_render[i] = dynamic_cast<BaseObject*>(this->_animation_frame[0].get_assignable_object());
      return;
    }
  }
}
}// namespace fresh
#endif