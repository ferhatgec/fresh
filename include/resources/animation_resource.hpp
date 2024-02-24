#ifndef FRESHENGINE_ANIMATION_RESOURCE_HPP
#define FRESHENGINE_ANIMATION_RESOURCE_HPP

#include "animation_key_resource.hpp"
#include "timer_resource.hpp"
#include "../render_objects.hpp"
#include "../objects/base_object.hpp"
#include "../../libs/idk/idk/containers/vector.hpp"
#include <vector>

namespace fresh {
template<typename KeyType>
class AnimationResource {
public:
  AnimationResource();
  ~AnimationResource();

  virtual void
  init_animation(bool loop = false) noexcept;

  virtual void
  run_animation() noexcept;

  virtual void
  pause_animation() noexcept;

  virtual void
  stop_animation() noexcept;

  virtual void
  push_animation_key(AnimationKeyResource<KeyType>& animation_key) noexcept;

  virtual void
  push_animation_key(AnimationKeyResource<KeyType>&& animation_key) noexcept;

  virtual void
  sync_render_objects() noexcept;

  __idk_nodiscard
  TimerResource&
  get_timer_resource() noexcept;
private:
  virtual void
  _reset_to_first_state() noexcept;
protected:
  bool _ended { false };
  bool _loop { false };
  TimerResource _timer;
  idk::usize _current_index { 0_usize };
  std::vector<AnimationKeyResource<KeyType>> _animation_frame; // you can only change one object at one animation frame.
                                                               // to change another one, initialize new AnimationResource.

  std::vector<BaseObject*> _casted_render_objects; // when render_object changes, don't forget to update using sync_render_objects()!
};
} // namespace fresh
#include "../../src/resources/animation_resource.cpp"
#endif // FRESHENGINE_ANIMATION_RESOURCE_HPP
