// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include "../../include/fescript/fescript_class.hpp"
#include "../../include/fescript/fescript_function.hpp"
#include "../../include/fescript/fescript_instance.hpp"

namespace fescript {
FescriptClass::FescriptClass(std::string name, std::shared_ptr<FescriptClass> superclass,
                   std::map<std::string, std::shared_ptr<FescriptFunction>> methods)
    : superclass{superclass}, name{std::move(name)},
      methods{std::move(methods)} {
  if(const auto& init = this->find_method("init"); init != nullptr) {
    this->is_variadic = init->is_variadic;
  }
}

[[nodiscard]] std::shared_ptr<FescriptFunction> FescriptClass::find_method(const std::string &name) {
  auto elem = methods.find(name);
  if (elem != methods.end()) {
    return elem->second;
  }
  if (this->superclass != nullptr) {
    return this->superclass->find_method(name);
  }
  return nullptr;
}

[[nodiscard]] int FescriptClass::arity() {
  std::shared_ptr<FescriptFunction> initializer = this->find_method("init");
  if (initializer == nullptr)
    return 0;
  return initializer->arity(); // it checks for is_variadic, no need for doing it twice.
}

[[nodiscard]] Object FescriptClass::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto instance = std::make_shared<FescriptInstance>(shared_from_this());
  std::shared_ptr<FescriptFunction> initializer = find_method("init");
  if (initializer != nullptr) {
    initializer->bind(instance)->call(interpreter, std::move(arguments));
  }
  return instance;
}

[[nodiscard]] std::string FescriptClass::to_string() { return name; }
}// namespace fescript