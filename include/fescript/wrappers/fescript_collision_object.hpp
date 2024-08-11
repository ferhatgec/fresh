#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
class CollisionObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<CollisionObjectWrapper> {
public:
  CollisionObjectWrapper();
  ~CollisionObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript