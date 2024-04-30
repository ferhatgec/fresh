#pragma once

#include <vector>
#include <memory>
#include "../fescript_token.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/stringview.hpp"
#include "../../objects/base_object.hpp"
#include "../../objects/sprite_object.hpp"
#include "../../objects/label_object.hpp"
#include "../../objects/area_object.hpp"
#include "../../objects/collision_object.hpp"

#define RETURN_BASE_OBJECT_PROPERTIES(index) \
if(keyword.lexeme == "pos_x") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().x); \
else if(keyword.lexeme == "pos_y") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().y); \
else if(keyword.lexeme == "visible") return std::get<index>(value)->get_is_visible();  \
else if(keyword.lexeme == "disabled") return std::get<index>(value)->get_is_disabled();  \
else if(keyword.lexeme == "width") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().w);  \
else if(keyword.lexeme == "height") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().h);\
else if(keyword.lexeme == "name") return std::string(std::get<index>(value)->_name.data());                \
else if(keyword.lexeme == "object_def") return std::string(std::get<index>(value)->_object_def.data());                                             \
else if(keyword.lexeme == "sub_groups") {    \
  auto array = std::make_shared<FescriptArray>();                                                            \
  for(const auto& object: std::get<index>(value)->_sub_objects) {                                          \
    array->values.push_back(Interpreter::baseobject_to_fescript_object(object));                                            \
  }                                           \
  return std::move(array); \
 }



#define SET_BASE_OBJECT_PROPERTIES() \
if(name.lexeme == "pos_x") this->get_position_info().x = static_cast<idk::i32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "pos_y") this->get_position_info().y = static_cast<idk::i32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "visible") this->get_is_visible() = std::get<BoolIndex>(value); \
else if(name.lexeme == "disabled") this->get_is_disabled() = std::get<BoolIndex>(value); \
else if(name.lexeme == "width") this->get_position_info().w = static_cast<idk::i32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "height") this->get_position_info().h = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));\
else if(name.lexeme == "sub_groups") {                                                                            \
  this->_sub_objects.clear();                                   \
  auto array = std::get<FescriptArrayIndex>(value);                                                               \
  for(const auto& object: array->values) {                                                                       \
    switch(object.index()) {                                        \
     case FescriptBaseObjectIndex: { this->push_to_sub_objects(std::get<FescriptBaseObjectIndex>(object)); break; }                               \
     case FescriptSpriteObjectIndex: { this->push_to_sub_objects(std::get<FescriptSpriteObjectIndex>(object)); break; }                               \
     case FescriptLabelObjectIndex: { this->push_to_sub_objects(std::get<FescriptLabelObjectIndex>(object)); break; }                               \
     case FescriptAreaObjectIndex: { this->push_to_sub_objects(std::get<FescriptAreaObjectIndex>(object)); break; }                               \
     case FescriptCollisionObjectIndex: { this->push_to_sub_objects(std::get<FescriptCollisionObjectIndex>(object)); break; }                     \
     case FescriptCameraObjectIndex: { this->push_to_sub_objects(std::get<FescriptCameraObjectIndex>(object)); break; }                                \
     default: {                      \
      std::cout << "Engine [language] error: Cannot use types those not inherited from BaseObject.";              \
      std::exit(1); \
     }\
    }                                    \
  }                                     \
}

#define RETURN_MEMBER_FUNCTION(object_fn, wrapped_fn_str) \
  switch(arguments.front().index()) { \
case FescriptBaseObjectIndex: { return this->_self->##object_fn(std::get<FescriptBaseObjectIndex>(arguments.front())); } \
case FescriptSpriteObjectIndex: { return this->_self->##object_fn(std::get<FescriptSpriteObjectIndex>(arguments.front())); } \
case FescriptLabelObjectIndex: { return this->_self->##object_fn(std::get<FescriptLabelObjectIndex>(arguments.front())); } \
case FescriptAreaObjectIndex: { return this->_self->##object_fn(std::get<FescriptAreaObjectIndex>(arguments.front())); } \
case FescriptCollisionObjectIndex: { return this->_self->##object_fn(std::get<FescriptCollisionObjectIndex>(arguments.front())); } \
case FescriptCameraObjectIndex: { return this->_self->##object_fn(std::get<FescriptCameraObjectIndex>(arguments.front())); }                                                          \
default: { \
std::cout << "Engine [language] error: " wrapped_fn_str " requires objects those inherited from BaseObject.\n"; \
std::exit(1); \
} \
}

namespace fescript {
class BaseObjectWrapper : public FescriptCallable, public std::enable_shared_from_this<BaseObjectWrapper> {
public:
  BaseObjectWrapper();
  BaseObjectWrapper(const idk::StringViewChar& object_def,
                    idk::u32 object_id,
                    const std::vector<std::shared_ptr<BaseObjectWrapper>>& sub_objects);
  virtual ~BaseObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
protected:
  idk::StringViewChar _object_def;
  idk::u32 _object_id;
  std::vector<std::shared_ptr<BaseObjectWrapper>> _sub_objects;
};
} // namespace fescript