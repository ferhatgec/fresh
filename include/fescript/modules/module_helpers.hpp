#pragma once

#include <fescript/fescript_token.hpp>

#define DEFINE_MODULE_CLASS(name, module_name, arg_count) \
              class Fescript##module_name##name : public FescriptCallable { \
                  public:                                             \
                    [[nodiscard]] int arity() override { return arg_count; } \
                    [[nodiscard]] std::string to_string() override { return #name; } \
                    [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override; \
                  };

#define DEFINE_MEMBER_MODULE_CLASS(name, module_name, arg_count, self_type) \
              class Fescript##module_name##name : public FescriptCallable { \
                  public:                                                   \
                    Fescript##module_name##name(std::shared_ptr<self_type> self) : _self{self} {} \
                    [[nodiscard]] int arity() override { return arg_count; } \
                    [[nodiscard]] std::string to_string() override { return #name; } \
                    [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override; \
                  private:                                                  \
                    std::shared_ptr<self_type> _self; \
                  };

#define ERR_CHECK_TYPE(fn_name, arg_count, type_str, type_index) \
              if(arguments.size() > arg_count || arguments.empty()) { \
                std::cout << "Engine [language] error: " #fn_name " must take " #arg_count " argument/s.\n"; \
                std::exit(1); \
              }                                                                                                          \
                                                                                                         \
              for(idk::isize i = 0; i < arguments.size(); ++i) {                                                                    \
                if(arguments[i].index() != type_index) {                                                                                              \
                  std::cout << "Engine [language] error: " << i + 1 << "th element in function " #fn_name " only takes '" type_str "' type."; \
                  std::exit(1);                                                                                 \
                } \
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
#define ERR_CHECK_COLLISIONOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "collisionobject", FescriptCollisionObjectIndex)
#define ERR_CHECK_CAMERAOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "cameraobject", FescriptCameraObjectIndex)
#define ERR_CHECK_ANIMATIONPLAYEROBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "animationplayerobject", FescriptAnimationPlayerObjectIndex)
#define ERR_CHECK_ANIMATIONFRAMEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "animationframeobject", FescriptAnimationFrameObjectIndex)
#define ERR_CHECK_CIRCLEOBJECT(fn_name, arg_count) ERR_CHECK_TYPE(fn_name, arg_count, "circleobject", FescriptCircleObjectIndex)