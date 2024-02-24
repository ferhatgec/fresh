#ifndef FRESHENGINE_ANIMATION_PROPERTY_RESOURCE_HPP
#define FRESHENGINE_ANIMATION_PROPERTY_RESOURCE_HPP

#include "animation_key_resource.hpp"
#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/utilities/type_traits.hpp"
#include "../objects/area_object.hpp"
#include "../objects/collision_object.hpp"
#include "../objects/label_object.hpp"
#include "../objects/sprite_object.hpp"
#include "../objects/base_object.hpp"

// AnimationPropertyResource is a lightweight way to avoid using AnimationResource, which actually changes whole object
// instead of one property from the object.
namespace fresh {
template<typename Class> struct IsInheritsToBaseObject    : idk::false_type {};
template<> struct IsInheritsToBaseObject<AreaObject>      : idk::true_type  {};
template<> struct IsInheritsToBaseObject<CollisionObject> : idk::true_type  {};
template<> struct IsInheritsToBaseObject<LabelObject>     : idk::true_type  {};
template<> struct IsInheritsToBaseObject<SpriteObject>    : idk::true_type  {};
template<> struct IsInheritsToBaseObject<GuiBaseObject>   : idk::true_type  {};
template<> struct IsInheritsToBaseObject<GuiButtonObject> : idk::true_type  {};

template<typename KeyType, typename SecondType = KeyType,
          idk::EnableIfType<
              IsInheritsToBaseObject<
                  idk::RemovePointer<
                    idk::RemoveConstAndVolatileType<
                        idk::RemoveReferenceType<KeyType>>>>::value, bool> = true>
class AnimationPropertyResource {
public:
  AnimationPropertyResource() {}
  virtual ~AnimationPropertyResource() {}

  void
  init_animation(bool loop = false) noexcept {
    this->_loop = loop;
    this->sync_render_objects();
  }

  __idk_nodiscard
  bool&
  get_loop() noexcept {
    return this->_loop;
  }

  void
  run_animation() noexcept {
    if(this->_animation_frame.empty())
      return;

    if(!this->_ended && !this->_timer.is_started()) {
      this->_timer.start();
      this->_current_index = 0;
      return;
    }

    auto _tick = this->_timer.get_ticks();

    if(((this->_animation_frame.size()) == this->_current_index)) {
      if(_tick < this->_animation_frame.back().get_end_ms() &&
          _tick >= this->_animation_frame.back().get_start_ms()) {
        return;
      }

      if(_tick >= this->_animation_frame.back().get_end_ms() ||
          (this->_animation_frame.size()) == this->_current_index) {
        this->_reset_to_first_state();

        if(this->_ended && !_loop) {
          this->_timer.stop();
          this->_current_index = 0;
          return;
        }

        this->_ended = true;
        this->_timer.stop();

        if(!_loop) {
          return;
        }
      }

      this->_timer.start();
      this->_current_index = 0;
    } else {
      if((_tick < this->_animation_frame[this->_current_index].get_end_ms())
        && (_tick >= this->_animation_frame[this->_current_index].get_start_ms())) { // [start, end)
        dynamic_cast<SecondType*>(fresh::RenderObjects::objects_to_render[this->_index_in_render_objects])
            ->get_property<KeyType>()
            = *this->_animation_frame[this->_current_index].get_assignable_object();

        ++this->_current_index;
      }
    }
  }

  void
  sync_render_objects() noexcept {
    std::cout << "Engine info: You actually don't need to call sync_render_objects() from an AnimatedPropertyResource.\n";
  }

  void
  push_sprite_key(AnimationKeyResource<KeyType, SecondType>& sprite_key) noexcept {
    this->_animation_frame.push_back(sprite_key);
  }

  void
  push_sprite_key(AnimationKeyResource<KeyType, SecondType>&& sprite_key) noexcept {
    this->_animation_frame.push_back(idk::move(sprite_key));
  }

  __idk_nodiscard
  idk::u64&
  get_index_in_render_objects() noexcept {
    return this->_index_in_render_objects;
  }

  void
  clear_animation_frame() {
    this->_animation_frame.clear();
  }

  __idk_nodiscard
  TimerResource&
  get_timer_resource() noexcept {
    return this->_timer;
  }

  __idk_nodiscard
  bool&
  get_ended() noexcept {
    return this->_ended;
  }
private:
  void
  _reset_to_first_state() noexcept {
    if(this->_animation_frame.empty()/* || !this->_object_sprite->get_sprite_resource().get_texture()*/) {
      std::cout << "Engine error: Animation frame empty or SpriteResource points to invalid place, _reset_to_first_state() is ignored.\n";
      return;
    }

    dynamic_cast<SecondType*>(fresh::RenderObjects::objects_to_render[this->_index_in_render_objects])
        ->get_property<KeyType>() = *this->_animation_frame[0].get_assignable_object();

    this->_current_index = 0;
  }

protected:
  bool _ended { false };
  bool _loop { false };
  bool _do_reset_to_first_state { true };

  TimerResource _timer;

  idk::usize _current_index { 0_usize };
  idk::u64 _index_in_render_objects { 0_u64 };

  std::vector<AnimationKeyResource<KeyType, SecondType>> _animation_frame;
};
} // namespace fresh

#endif // FRESHENGINE_ANIMATION_PROPERTY_RESOURCE_HPP
