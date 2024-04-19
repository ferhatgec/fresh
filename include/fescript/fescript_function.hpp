// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "fescript_callable.hpp"

namespace fescript {
class Environment;
class Function;
class FescriptInstance;

class FescriptFunction : public FescriptCallable {
public:
  FescriptFunction(std::shared_ptr<Function> declaration,
              std::shared_ptr<Environment> closure, bool is_initializer);
  [[nodiscard]] int arity() override;
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] std::shared_ptr<FescriptFunction> bind(std::shared_ptr<FescriptInstance> instance);

private:
  std::shared_ptr<Function> declaration;
  std::shared_ptr<Environment> closure;
  bool is_initializer;
};
}// namespace fescript