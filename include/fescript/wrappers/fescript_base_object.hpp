#pragma once

#include <fescript/fescript_token.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/stringview.hpp>
#include <objects/base_object.hpp>
#include <objects/sprite_object.hpp>
#include <objects/label_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/polygon_object.hpp>
#include <objects/rectangle_object.hpp>
#include <objects/physics/area_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/physics/body_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <objects/physics/polygon_body_object.hpp>
#include <objects/physics/world_object.hpp>
#include <vector>
#include <memory>


#define RETURN_BASE_OBJECT_PROPERTIES(index) \
if(keyword.lexeme == "pos_x") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().x); \
else if(keyword.lexeme == "pos_y") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().y); \
else if(keyword.lexeme == "visible") return std::get<index>(value)->get_is_visible();  \
else if(keyword.lexeme == "disabled") return std::get<index>(value)->get_is_disabled(); \
else if(keyword.lexeme == "width") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().w); \
else if(keyword.lexeme == "height") return static_cast<idk::f80>(std::get<index>(value)->get_position_info().h); \
else if(keyword.lexeme == "name") return std::string(std::get<index>(value)->_name.data()); \
else if(keyword.lexeme == "object_def") return std::string(std::get<index>(value)->_object_def.data()); \
else if(keyword.lexeme == "sub_groups") { \
  auto array = std::make_shared<FescriptArray>(); \
  for(const auto& object: std::get<index>(value)->_sub_objects) { \
    array->values.push_back(Interpreter::baseobject_to_fescript_object(object)); \
  } \
  return std::move(array); \
 }



#define SET_BASE_OBJECT_PROPERTIES() \
if(name.lexeme == "pos_x") this->get_position_info().x = static_cast<idk::f32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "pos_y") this->get_position_info().y = static_cast<idk::f32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "visible") this->get_is_visible() = std::get<BoolIndex>(value); \
else if(name.lexeme == "disabled") this->get_is_disabled() = std::get<BoolIndex>(value); \
else if(name.lexeme == "width") this->get_position_info().w = static_cast<idk::f32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "height") this->get_position_info().h = static_cast<idk::f32>(std::get<LongDoubleIndex>(value)); \
else if(name.lexeme == "sub_groups") { \
  this->_sub_objects.clear(); \
  auto array = std::get<FescriptArrayIndex>(value); \
  for(const auto& object: array->values) { \
    switch(object.index()) { \
     case FescriptBaseObjectIndex: { this->push_to_sub_objects(std::get<FescriptBaseObjectIndex>(object)); break; } \
     case FescriptSpriteObjectIndex: { this->push_to_sub_objects(std::get<FescriptSpriteObjectIndex>(object)); break; } \
     case FescriptLabelObjectIndex: { this->push_to_sub_objects(std::get<FescriptLabelObjectIndex>(object)); break; } \
     case FescriptAreaObjectIndex: { this->push_to_sub_objects(std::get<FescriptAreaObjectIndex>(object)); break; } \
     case FescriptCameraObjectIndex: { this->push_to_sub_objects(std::get<FescriptCameraObjectIndex>(object)); break; } \
     case FescriptCircleObjectIndex: { this->push_to_sub_objects(std::get<FescriptCircleObjectIndex>(object)); break; } \
     case FescriptPolygonObjectIndex: { this->push_to_sub_objects(std::get<FescriptPolygonObjectIndex>(object)); break; } \
     case FescriptRectangleObjectIndex: { this->push_to_sub_objects(std::get<FescriptRectangleObjectIndex>(object)); break; } \
     case FescriptRectangleAreaObjectIndex: { this->push_to_sub_objects(std::get<FescriptRectangleAreaObjectIndex>(object)); break; } \
     case FescriptCircleAreaObjectIndex: { this->push_to_sub_objects(std::get<FescriptCircleAreaObjectIndex>(object)); break; } \
     case FescriptPolygonAreaObjectIndex: { this->push_to_sub_objects(std::get<FescriptPolygonAreaObjectIndex>(object)); break; } \
     case FescriptBodyObjectIndex: { this->push_to_sub_objects(std::get<FescriptBodyObjectIndex>(object)); break; } \
     case FescriptRectangleBodyObjectIndex: { this->push_to_sub_objects(std::get<FescriptRectangleBodyObjectIndex>(object)); break; } \
     case FescriptCircleBodyObjectIndex: { this->push_to_sub_objects(std::get<FescriptCircleBodyObjectIndex>(object)); break; } \
     case FescriptPolygonBodyObjectIndex: { this->push_to_sub_objects(std::get<FescriptPolygonBodyObjectIndex>(object)); break; } \
     case FescriptWorldObjectIndex: { this->push_to_sub_objects(std::get<FescriptWorldObjectIndex>(object)); break; } \
     default: { \
      std::cout << "Engine [language] error: Cannot use types those not inherited from BaseObject."; \
      std::exit(1); \
     } \
    } \
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
class BaseObjectWrapper : public FescriptCallable {
public:
  BaseObjectWrapper();
  BaseObjectWrapper(const idk::StringViewChar& object_def,
                    idk::u32 object_id,
                    const std::vector<std::shared_ptr<BaseObjectWrapper>>& sub_objects);
  virtual ~BaseObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
protected:
  idk::StringViewChar _object_def;
  idk::u32 _object_id;
  std::vector<std::shared_ptr<BaseObjectWrapper>> _sub_objects;
};
} // namespace fescript