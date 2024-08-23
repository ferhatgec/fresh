// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <map>

#include "fescript_callable.hpp"

namespace fescript {
class Interpreter;
class FescriptFunction;

class FescriptClass : public FescriptCallable,
                 public std::enable_shared_from_this<FescriptClass> {
  friend class FescriptInstance;

public:
  FescriptClass(std::string name, std::shared_ptr<FescriptClass> superclass,
           std::map<std::string, std::shared_ptr<FescriptFunction>> methods);

  [[nodiscard]] std::shared_ptr<FescriptFunction> find_method(const std::string &name);
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
  [[nodiscard]] int arity() override;

private:
  std::string name;
  const std::shared_ptr<FescriptClass> superclass;
  std::map<std::string, std::shared_ptr<FescriptFunction>> methods;
};
}// namespace fescript
