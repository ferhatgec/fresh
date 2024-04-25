#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
class LabelObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<LabelObjectWrapper> {
public:
  LabelObjectWrapper();
  ~LabelObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript