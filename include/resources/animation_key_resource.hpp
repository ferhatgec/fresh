#ifndef FRESHENGINE_ANIMATION_KEY_RESOURCE_HPP
#define FRESHENGINE_ANIMATION_KEY_RESOURCE_HPP

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/types/any.hpp"
#include "id_resource.hpp"
#include <any>

namespace fresh {
enum class AnimationKeyType {
  Bool,
  Int,
  Float,
  String,
  AreaObject,
  LabelObject,
  SpriteObject
};

template<typename KeyType, typename SecondType = KeyType>
class AnimationKeyResource {
public:
  AnimationKeyResource() {

  }

  AnimationKeyResource(KeyType* assign_to_object,
                       SecondType* object_ptr_store = nullptr,
                       idk::f64 start_ms = 0_f64, idk::f64 end_ms = 0_f64) {
    this->_assign_to_object = assign_to_object;
    this->_object_ptr_store = object_ptr_store;
    this->_start_ms         = start_ms;
    this->_end_ms           = end_ms;
  }

  AnimationKeyResource(idk::f64 start_ms, idk::f64 end_ms) {
    this->_start_ms = start_ms;
    this->_end_ms   = end_ms;
  }

  ~AnimationKeyResource() {

  }

  void
  link_to_key(KeyType* assign_to_object) noexcept {
    this->_assign_to_object = assign_to_object;
  }

  __idk_nodiscard
  idk::f64&
  get_start_ms() noexcept {
    return this->_start_ms;
  }

  __idk_nodiscard
  idk::f64&
  get_end_ms() noexcept {
    return this->_end_ms;
  }

  __idk_nodiscard
  idk::u64&
  get_object_id() noexcept {
    return this->_object_id;
  }

  __idk_nodiscard
  KeyType*&
  get_assignable_object() noexcept {
    return this->_assign_to_object;
  }
protected:
  idk::f64 _start_ms { 0_f64 };
  idk::f64 _end_ms { 0_f64 };
  idk::u64 _object_id { 0_u64 };
  KeyType* _assign_to_object = nullptr;
};
} // namespace fresh

#endif // FRESHENGINE_ANIMATION_KEY_RESOURCE_HPP
