#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, BodyObjectMember, arg_count)

namespace fescript {
class BodyObjectWrapper : public BaseObjectWrapper {
public:
  BodyObjectWrapper();
  virtual ~BodyObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript