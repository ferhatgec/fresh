#pragma once

#include <vector>
#include <memory>
#include "../fescript_token.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/stringview.hpp"

//public:                                             \
//                    [[nodiscard]] int arity() override { return arg_count; } \
//                    [[nodiscard]] std::string to_string() override { return #name; } \
//                    [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override; \
//                  };
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