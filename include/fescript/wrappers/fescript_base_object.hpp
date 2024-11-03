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
if(keyword.lexeme == "pos_x") return static_cast<idk::f80>(std::get<index>(value)->get_x()); \
else if(keyword.lexeme == "pos_y") return static_cast<idk::f80>(std::get<index>(value)->get_y()); \
else if(keyword.lexeme == "visible") return std::get<index>(value)->get_visible();  \
else if(keyword.lexeme == "disabled") return std::get<index>(value)->get_disabled(); \
else if(keyword.lexeme == "width") return static_cast<idk::f80>(std::get<index>(value)->get_w()); \
else if(keyword.lexeme == "height") return static_cast<idk::f80>(std::get<index>(value)->get_h()); \
else if(keyword.lexeme == "name") return std::string(std::get<index>(value)->_name.data()); \
else if(keyword.lexeme == "object_def") return std::get<index>(value)->to_string(); \
else if(keyword.lexeme == "push_to_sub_objects") return std::make_shared<FescriptBaseObjectMemberPushSubObject>(std::get<index>(value)); \
else if(keyword.lexeme == "set_rotation") return std::make_shared<FescriptBaseObjectMemberSetRotationByRadianDegrees>(std::get<index>(value)); \
else if(keyword.lexeme == "sub_groups") { \
  auto array = std::make_shared<FescriptArray>(); \
  for(const auto& object: std::get<index>(value)->_sub_objects) { \
    array->push_value(fescript::Interpreter::baseobject_to_fescript_object(object)); \
  } \
  return std::move(array); \
 }



#define SET_BASE_OBJECT_PROPERTIES() \
if(name.lexeme == "pos_x") this->set_x(static_cast<idk::f32>(std::get<LongDoubleIndex>(value))); \
else if(name.lexeme == "pos_y") this->set_y(static_cast<idk::f32>(std::get<LongDoubleIndex>(value))); \
else if(name.lexeme == "visible") this->set_visible(std::get<BoolIndex>(value)); \
else if(name.lexeme == "disabled") this->set_disabled(std::get<BoolIndex>(value)); \
else if(name.lexeme == "width") this->set_w(static_cast<idk::f32>(std::get<LongDoubleIndex>(value))); \
else if(name.lexeme == "height") this->set_h(static_cast<idk::f32>(std::get<LongDoubleIndex>(value))); \
else if(name.lexeme == "sub_groups") { \
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
DEFINE_MEMBER_MODULE_CLASS(PushSubObject, BaseObjectMember, 1, fresh::BaseObject)
DEFINE_MEMBER_MODULE_CLASS(SetRotationByRadianDegrees, BaseObjectMember, 1, fresh::BaseObject)

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