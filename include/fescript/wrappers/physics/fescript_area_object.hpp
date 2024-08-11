#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>

#define AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, AreaObjectMember, 1, fresh::AreaObject)

class AreaObjectWrapper : public BaseObjectWrapper {
public:
  AreaObjectWrapper();
  virtual ~AreaObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript