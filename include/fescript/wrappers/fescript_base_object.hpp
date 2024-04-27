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
if(expr->name.lexeme == "pos_x") return static_cast<idk::f80>(std::get<index>(object)->get_position_info().x); \
else if(expr->name.lexeme == "pos_y") return static_cast<idk::f80>(std::get<index>(object)->get_position_info().y); \
else if(expr->name.lexeme == "visible") return std::get<index>(object)->get_is_visible();  \
else if(expr->name.lexeme == "disabled") return std::get<index>(object)->get_is_disabled();  \
else if(expr->name.lexeme == "width") return static_cast<idk::f80>(std::get<index>(object)->get_position_info().w);  \
else if(expr->name.lexeme == "height") return static_cast<idk::f80>(std::get<index>(object)->get_position_info().h);\
else if(expr->name.lexeme == "sub_groups") { \
 auto array = std::make_shared<FescriptArray>();                                                               \
 for(const auto& object: std::get<index>(object)->_sub_objects) {                                                    \
  array->values.push_back(object);                                            \
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
     case FescriptBaseObjectIndex: { this->_sub_objects.push_back(std::get<FescriptBaseObjectIndex>(object)); break; }                               \
     case FescriptSpriteObjectIndex: { this->_sub_objects.push_back(std::get<FescriptSpriteObjectIndex>(object)); break; }                               \
     case FescriptLabelObjectIndex: { this->_sub_objects.push_back(std::get<FescriptLabelObjectIndex>(object)); break; }                               \
     case FescriptAreaObjectIndex: { this->_sub_objects.push_back(std::get<FescriptAreaObjectIndex>(object)); break; }                               \
     case FescriptCollisionObjectIndex: { this->_sub_objects.push_back(std::get<FescriptCollisionObjectIndex>(object)); break; }                     \
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