#pragma once

#include "fescript_base_object.hpp"
#include "../modules/module_helpers.hpp"

#define AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AreaObjectMember, arg_count)

namespace fescript {
class FescriptAreaObjectMemberIsCollidingWith : public FescriptCallable {
public:
  FescriptAreaObjectMemberIsCollidingWith(const std::shared_ptr<fresh::AreaObject>& self)
    : _self{self} {}

  [[nodiscard]] int arity() override { return 1; }
  [[nodiscard]] std::string to_string() override { return "IsCollidingWith"; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
private:
  std::shared_ptr<fresh::AreaObject> _self;
};

class AreaObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<AreaObjectWrapper> {
public:
  AreaObjectWrapper();
  ~AreaObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript