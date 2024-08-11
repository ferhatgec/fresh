#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsVisibleOnCamera, CameraObjectMember, 1, fresh::CameraObject)
DEFINE_MEMBER_MODULE_CLASS(Move, CameraObjectMember, 2, fresh::CameraObject)

class CameraObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<CameraObjectWrapper> {
public:
  CameraObjectWrapper();
  ~CameraObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript