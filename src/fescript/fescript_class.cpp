// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_class.hpp>
#include <fescript/fescript_function.hpp>
#include <fescript/fescript_instance.hpp>
#include <utility>

namespace fescript {
FescriptClass::FescriptClass(
  std::string name,
  std::shared_ptr<FescriptClass> superclass,
  std::map<std::string, std::shared_ptr<FescriptFunction>> methods
) : name{std::move(name)},
    superclass{std::move(superclass)},
    methods{std::move(methods)} {
  if(const auto& init = this->find_method("init"); init != nullptr) {
    this->_is_variadic = init->is_variadic();
  }
}

[[nodiscard]] std::shared_ptr<FescriptFunction> FescriptClass::find_method(const std::string &name) {
  auto elem = methods.find(name);
  if (elem != methods.end()) {
    return elem->second;
  }
  if (this->superclass) {
    return this->superclass->find_method(name);
  }
  return nullptr;
}

[[nodiscard]] int FescriptClass::arity() {
  const auto& initializer = this->find_method("init");
  if (!initializer) {
    return 0;
  }
  return initializer->arity(); // it checks for is_variadic, no need for doing it twice.
}

[[nodiscard]] Object FescriptClass::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto instance = std::make_shared<FescriptInstance>(shared_from_this());
  const auto& initializer = find_method("init");
  if (initializer != nullptr) {
    (void)initializer->bind(instance)->call(interpreter, arguments);
  }
  return instance;
}
}// namespace fescript