// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <log/log.hpp>
#include <fescript/fescript_token.hpp>

namespace fescript {
// FIXME: replace macros ERR_CHECK_TYPE_AT, ERR_CHECK_TYPE and ERR_CHECK_UNINITIALIZED with their function equivalents.
static inline std::string_view function_name;
} // namespace fescript

#define DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(name, module_name, arg_count, derived_from) \
  class Fescript##module_name##name : public derived_from { \
  public: \
    [[nodiscard]] int arity() override { return arg_count; } \
    [[nodiscard]] constexpr const char* to_string() const noexcept override { return #module_name; } \
    [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override; \
  };

#define DEFINE_MEMBER_MODULE_CLASS_CUSTOM_DERIVED_FROM(name, module_name, arg_count, self_type, derived_from) \
  class Fescript##module_name##name : public derived_from { \
  public: \
    Fescript##module_name##name() = default; \
    explicit Fescript##module_name##name(const std::shared_ptr<self_type>& self) : _self{self} {} \
    [[nodiscard]] int arity() override { return arg_count; } \
    [[nodiscard]] constexpr const char* to_string() const noexcept override { return #name; } \
    [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override; \
    [[nodiscard]] const std::shared_ptr<self_type>& get_self() const noexcept { return this->_self; } \
    void set_self(const std::shared_ptr<self_type>& slf_ptr) noexcept { this->_self = slf_ptr; } \
  private: \
    std::shared_ptr<self_type> _self; \
  };

#define DEFINE_MODULE_CLASS(name, module_name, arg_count) \
  DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(name, module_name, arg_count, FescriptCallable)

#define DEFINE_MEMBER_MODULE_CLASS(name, module_name, arg_count, self_type) \
  DEFINE_MEMBER_MODULE_CLASS_CUSTOM_DERIVED_FROM(name, module_name, arg_count, self_type, FescriptCallable)

#define ERR_CHECK_TYPE_AT(fn_name, i, type_str, type_index) \
  fescript::function_name = fn_name;\
  if(arguments.size() < i || arguments.empty()) { \
    fresh::log_error(fresh::src(), "{} index {} out of bounds.", #fn_name, i); \
    std::exit(1); \
  } \
  \
  if(arguments[i].index() != type_index) { \
    fresh::log_error(fresh::src(), "{}th element in function {} must take '{}' type.", i + 1, #fn_name, type_str); \
    std::exit(1); \
  }

#define ERR_CHECK_TYPE(fn_name, arg_count, type_str, type_index) \
  fescript::function_name = fn_name; \
  if(arguments.size() > arg_count || arguments.empty()) { \
    fresh::log_error(fresh::src(), "{} must take {} argument/s", #fn_name, arg_count); \
    std::exit(1); \
  } \
  \
  for(idk::isize i = 0; i < arguments.size(); ++i) { \
    if(arguments[i].index() != type_index) { \
      fresh::log_error(fresh::src(), "{}th element in function {} must take '{}' type.", i + 1, #fn_name, type_str); \
      std::exit(1); \
    } \
  }

#define ERR_CHECK_UNINITIALIZED_AUTO() \
  if(!this->_self) {\
    fresh::log_error(fresh::src(), "{} cannot be called since object is not initialized.", fescript::function_name); \
    std::exit(1); \
  }

#define ERR_CHECK_UNINITIALIZED(fn_name) \
  fescript::function_name = fn_name; \
  if(!this->_self) {\
    fresh::log_error(fresh::src(), "{} cannot be called since object is not initialized.", fn_name); \
    std::exit(1); \
  }

#define ERR_CHECK_STRING(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "string", StringIndex)
#define ERR_CHECK_DECIMAL(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "decimal", LongDoubleIndex)
#define ERR_CHECK_BOOL(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "bool", BoolIndex)
#define ERR_CHECK_NULLPTR(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "null", NullptrIndex)
#define ERR_CHECK_DICT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "dict", FescriptDictIndex)
#define ERR_CHECK_ARRAY(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "array", FescriptArrayIndex)

#define ERR_CHECK_BASEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "baseobject", FescriptBaseObjectIndex)
#define ERR_CHECK_SPRITEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "spriteobject", FescriptSpriteObjectIndex)
#define ERR_CHECK_LABELOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "labelobject", FescriptLabelObjectIndex)

#define ERR_CHECK_AREAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "areaobject", FescriptAreaObjectIndex)
#define ERR_CHECK_RECTANGLEAREAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "rectangleareaobject", FescriptRectangleObjectIndex)
#define ERR_CHECK_CIRCLEAREAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "circleareaobject", FescriptCircleAreaObjectIndex)
#define ERR_CHECK_POLYGONAREAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "polygonareaobject", FescriptPolygonAreaObjectIndex)

#define ERR_CHECK_RECTANGLEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "rectangleobject", FescriptRectangleObjectIndex)
#define ERR_CHECK_CIRCLEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "circleobject", FescriptCircleObjectIndex)
#define ERR_CHECK_POLYGONOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "polygonobject", FescriptPolygonObjectIndex)

#define ERR_CHECK_BODYOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "bodyobject", FescriptBodyObjectIndex)
#define ERR_CHECK_RECTANGLEBODYOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "rectanglebodyobject", FescriptRectangleBodyObjectIndex)
#define ERR_CHECK_CIRCLEBODYOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "circlebodyobject", FescriptCircleBodyObjectIndex)
#define ERR_CHECK_POLYGONBODYOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "polygonbodyobject", FescriptPolygonBodyObjectIndex)

#define ERR_CHECK_WORLDOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "worldobject", FescriptWorldObjectIndex)

#define ERR_CHECK_CAMERAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "cameraobject", FescriptCameraObjectIndex)

#define ERR_CHECK_ANIMATIONPLAYEROBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "animationplayerobject", FescriptAnimationPlayerObjectIndex)
#define ERR_CHECK_ANIMATIONFRAMEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "animationframeobject", FescriptAnimationFrameObjectIndex)