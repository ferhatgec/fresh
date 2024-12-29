// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript/modules/module_helpers.hpp"

#include <fescript/fescript_callable.hpp>
#include <fescript/fescript_token.hpp>
#include <memory>
#include <objects/base_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/label_object.hpp>
#include <objects/physics/area_object.hpp>
#include <objects/physics/body_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/polygon_body_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <objects/physics/world_object.hpp>
#include <objects/polygon_object.hpp>
#include <objects/rectangle_object.hpp>
#include <objects/sprite_object.hpp>
#include <types/stringview.hpp>
#include <vector>

#define RETURN_BASE_OBJECT_PROPERTIES(index) \
  const auto& obj_ptr = std::get<index>(value); \
  if(keyword.lexeme == "visible") return obj_ptr->get_visible();  \
  if(keyword.lexeme == "disabled") return obj_ptr->get_disabled(); \
  if(keyword.lexeme == "object_def") return obj_ptr->to_string(); \
  if(keyword.lexeme == "push_to_sub_objects") return fescript::cache_make_shared<FescriptBaseObjectMemberPushSubObject>(obj_ptr); \
  if(keyword.lexeme == "set_visible") return fescript::cache_make_shared<FescriptBaseObjectMemberSetVisible>(obj_ptr); \
  if(keyword.lexeme == "set_visible") return fescript::cache_make_shared<FescriptBaseObjectMemberSetVisible>(obj_ptr); \
  if(keyword.lexeme == "set_x") return fescript::cache_make_shared<FescriptBaseObjectMemberSetX>(obj_ptr); \
  if(keyword.lexeme == "set_y") return fescript::cache_make_shared<FescriptBaseObjectMemberSetY>(obj_ptr); \
  if(keyword.lexeme == "set_w") return fescript::cache_make_shared<FescriptBaseObjectMemberSetW>(obj_ptr); \
  if(keyword.lexeme == "set_h") return fescript::cache_make_shared<FescriptBaseObjectMemberSetH>(obj_ptr); \
  if(keyword.lexeme == "set_xywh") return fescript::cache_make_shared<FescriptBaseObjectMemberSetXYWH>(obj_ptr); \
  if(keyword.lexeme == "set_rot") return fescript::cache_make_shared<FescriptBaseObjectMemberSetRot>(obj_ptr); \
  if(keyword.lexeme == "set_name") return fescript::cache_make_shared<FescriptBaseObjectMemberSetName>(obj_ptr); \
  if(keyword.lexeme == "set_flip_vertically") return fescript::cache_make_shared<FescriptBaseObjectMemberSetFlipVertically>(obj_ptr); \
  if(keyword.lexeme == "set_flip_horizontally") return fescript::cache_make_shared<FescriptBaseObjectMemberSetFlipHorizontally>(obj_ptr); \
  if(keyword.lexeme == "get_visible") return fescript::cache_make_shared<FescriptBaseObjectMemberGetVisible>(obj_ptr); \
  if(keyword.lexeme == "get_visible") return fescript::cache_make_shared<FescriptBaseObjectMemberGetVisible>(obj_ptr); \
  if(keyword.lexeme == "get_x") return fescript::cache_make_shared<FescriptBaseObjectMemberGetX>(obj_ptr); \
  if(keyword.lexeme == "get_y") return fescript::cache_make_shared<FescriptBaseObjectMemberGetY>(obj_ptr); \
  if(keyword.lexeme == "get_w") return fescript::cache_make_shared<FescriptBaseObjectMemberGetW>(obj_ptr); \
  if(keyword.lexeme == "get_h") return fescript::cache_make_shared<FescriptBaseObjectMemberGetH>(obj_ptr); \
  if(keyword.lexeme == "get_xywh") return fescript::cache_make_shared<FescriptBaseObjectMemberGetXYWH>(obj_ptr); \
  if(keyword.lexeme == "get_rot") return fescript::cache_make_shared<FescriptBaseObjectMemberGetRot>(obj_ptr); \
  if(keyword.lexeme == "get_name") return fescript::cache_make_shared<FescriptBaseObjectMemberGetName>(obj_ptr); \
  if(keyword.lexeme == "get_flip_vertically") return fescript::cache_make_shared<FescriptBaseObjectMemberGetFlipVertically>(obj_ptr); \
  if(keyword.lexeme == "get_flip_horizontally") return fescript::cache_make_shared<FescriptBaseObjectMemberGetFlipHorizontally>(obj_ptr); \
  if(keyword.lexeme == "get_object") return fescript::cache_make_shared<FescriptBaseObjectMemberGetObject>(obj_ptr); \
  if(keyword.lexeme == "sub_groups") { \
    auto array = std::make_shared<FescriptArray>(); \
    for(const auto& object: std::get<index>(value)->_sub_objects) { \
      array->push_value(fescript::Interpreter::baseobject_to_fescript_object(object)); \
    } \
    return std::move(array); \
  }

// always add after RETURN_BASE_OBJECT_PROPERTIES()
#define RETURN_BODY_OBJECT_PROPERTIES() \
  if(keyword.lexeme == "set_fixed_rot") return fescript::cache_make_shared<FescriptBodyObjectMemberSetFixedRot>(obj_ptr); \
  if(keyword.lexeme == "get_fixed_rot") return fescript::cache_make_shared<FescriptBodyObjectMemberGetFixedRot>(obj_ptr); \
  if(keyword.lexeme == "set_is_static_body") return fescript::cache_make_shared<FescriptBodyObjectMemberSetIsStaticBody>(obj_ptr); \
  if(keyword.lexeme == "get_is_static_body") return fescript::cache_make_shared<FescriptBodyObjectMemberGetIsStaticBody>(obj_ptr); \
  if(keyword.lexeme == "set_linear_velocity") return fescript::cache_make_shared<FescriptBodyObjectMemberSetLinearVelocity>(obj_ptr); \
  if(keyword.lexeme == "get_linear_velocity") return fescript::cache_make_shared<FescriptBodyObjectMemberGetLinearVelocity>(obj_ptr); \
  if(keyword.lexeme == "apply_force_center") return fescript::cache_make_shared<FescriptBodyObjectMemberApplyForceCenter>(obj_ptr); \
  if(keyword.lexeme == "apply_linear_impulse_center") return fescript::cache_make_shared<FescriptBodyObjectMemberApplyLinearImpulseCenter>(obj_ptr);
#define SET_BASE_OBJECT_PROPERTIES() \
  if(name.lexeme == "sub_groups") { \
    this->_sub_objects.clear(); \
    auto array = std::get<FescriptArrayIndex>(value); \
    for(const auto& object: array->get_values()) { \
      this->push_object(std::move(fescript::Interpreter::fescript_object_to_baseobject(object)));\
    } \
  }

#define RETURN_MEMBER_FUNCTION(object_fn, wrapped_fn_str) \
  switch(arguments.front().index()) { \
case FescriptBaseObjectIndex: { return this->_self->##object_fn(std::get<FescriptBaseObjectIndex>(arguments.front())); } \
case FescriptSpriteObjectIndex: { return this->_self->##object_fn(std::get<FescriptSpriteObjectIndex>(arguments.front())); } \
case FescriptLabelObjectIndex: { return this->_self->##object_fn(std::get<FescriptLabelObjectIndex>(arguments.front())); } \
case FescriptAreaObjectIndex: { return this->_self->##object_fn(std::get<FescriptAreaObjectIndex>(arguments.front())); } \
case FescriptCameraObjectIndex: { return this->_self->##object_fn(std::get<FescriptCameraObjectIndex>(arguments.front())); } \
case FescriptCircleObjectIndex: { return this->_self->##object_fn(std::get<FescriptCircleObjectIndex>(arguments.front())); } \
case FescriptPolygonObjectIndex: { return this->_self->##object_fn(std::get<FescriptPolygonObjectIndex>(arguments.front())); } \
case FescriptRectangleObjectIndex: { return this->_self->##object_fn(std::get<FescriptRectangleObjectIndex>(arguments.front())); } \
case FescriptRectangleAreaObjectIndex: { return this->_self->##object_fn(std::get<FescriptRectangleAreaObjectIndex>(arguments.front())); } \
case FescriptCircleAreaObjectIndex: { return this->_self->##object_fn(std::get<FescriptCircleAreaObjectIndex>(arguments.front())); } \
case FescriptPolygonAreaObjectIndex: { return this->_self->##object_fn(std::get<FescriptPolygonAreaObjectIndex>(arguments.front())); } \
case FescriptBodyObjectIndex: { return this->_self->##object_fn(std::get<FescriptBodyObjectIndex>(arguments.front())); } \
case FescriptRectangleBodyObjectIndex: { return this->_self->##object_fn(std::get<FescriptRectangleBodyObjectIndex>(arguments.front())); } \
case FescriptCircleBodyObjectIndex: { return this->_self->##object_fn(std::get<FescriptCircleBodyObjectIndex>(arguments.front())); } \
case FescriptPolygonBodyObjectIndex: { return this->_self->##object_fn(std::get<FescriptPolygonBodyObjectIndex>(arguments.front())); } \
case FescriptWorldObjectIndex: { return this->_self->##object_fn(std::get<FescriptWorldObjectIndex>(arguments.front())); } \
default: { \
std::cout << "Engine [language] error: " wrapped_fn_str " requires objects those inherited from BaseObject.\n"; \
std::exit(1); \
} \
}

namespace fescript {
/// T must be BaseObject derived class.
/// U must be FescriptCallable derived class.
/// cache_make_shared is cache friendly approach to std::make_shared, instead of allocating new memory
/// for each function call in fescript, this function uses unordered_map to cache functions so if a function
/// called more than once, then it will return the function from allocated memory; it's also sometimes better way
/// to handle memory than allocating every function fescript interface in every instance of the object, so only
/// first call of the function will allocate the memory, so first call would be slower than next function calls.
///
/// note:
/// ----
/// if speed is everything then using C++ API directly is the best way; implementing bytecode for fescript
/// could be better than using tree-walking interpreter; but for now it's not the priority; TODO.
template<typename U, typename T = fresh::BaseObject>
  requires std::derived_from<U, FescriptCallable>
static const std::shared_ptr<FescriptCallable>& cache_make_shared(const std::shared_ptr<T>& obj) noexcept {
  if (!obj) {
    fresh::log_error(fresh::src(), "nullptr passed.");
    std::exit(1);
  }
  const auto fn_str = U().to_string();
  if (const auto& it = obj->cache_fn.find(fn_str);
    it != obj->cache_fn.end()) {
    return it->second;
  }
  obj->cache_fn[fn_str] = std::make_shared<U>(obj);
  return obj->cache_fn[fn_str];
}

DEFINE_MEMBER_MODULE_CLASS(PushSubObject, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetVisible, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetDisabled, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetX, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetY, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetW, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetH, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetXYWH, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetRot, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetName, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetFlipVertically, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetFlipHorizontally, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetVisible, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetDisabled, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetX, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetY, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetW, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetH, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetXYWH, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetRot, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetName, BaseObjectMember, 0, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetFlipVertically, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetFlipHorizontally, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(GetObject, BaseObjectMember, 1, fresh::BaseObject)

class FescriptBaseObjectWrapper : public FescriptCallable {
public:
  FescriptBaseObjectWrapper() = default;
  FescriptBaseObjectWrapper(
    idk::u32 object_id,
    const std::vector<std::shared_ptr<FescriptBaseObjectWrapper>>& sub_objects
  );
  ~FescriptBaseObjectWrapper() override = default;

  [[nodiscard]] constexpr const char* to_string() const noexcept override {
    return fresh::BaseObject().to_string();
  }

  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
protected:
  idk::u32 _object_id;
  std::vector<std::shared_ptr<FescriptBaseObjectWrapper>> _sub_objects;
};
} // namespace fescript