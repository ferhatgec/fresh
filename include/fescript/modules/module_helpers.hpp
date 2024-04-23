#pragma once

#include "../fescript_token.hpp"

#define DEFINE_MODULE_CLASS(name, module_name, arg_count) \
              class Fescript##module_name##name : public FescriptCallable { \
                  public:                                             \
                    [[nodiscard]] int arity() override { return arg_count; } \
                    [[nodiscard]] std::string to_string() override { return #name; } \
                    [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override; \
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
