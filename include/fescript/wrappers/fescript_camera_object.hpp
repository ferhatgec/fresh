#pragma once

#include "fescript_base_object.hpp"
#include "../modules/module_helpers.hpp"

namespace fescript {
class FescriptCameraObjectMemberIsVisibleOnCamera : public FescriptCallable {
public:
  FescriptCameraObjectMemberIsVisibleOnCamera(const std::shared_ptr<fresh::CameraObject>& self)
    : _self{self} {}

  [[nodiscard]] int arity() override { return 1; }
  [[nodiscard]] std::string to_string() override { return "IsVisibleOnCamera"; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
private:
  std::shared_ptr<fresh::CameraObject> _self;
};

class CameraObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<CameraObjectWrapper> {
public:
  CameraObjectWrapper();
  ~CameraObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript