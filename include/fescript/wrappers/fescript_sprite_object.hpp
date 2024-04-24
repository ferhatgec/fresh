#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
class SpriteObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<SpriteObjectWrapper> {
public:
  SpriteObjectWrapper();
  ~SpriteObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript