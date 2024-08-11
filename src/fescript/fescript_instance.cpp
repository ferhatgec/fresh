// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_instance.hpp>
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_error.hpp>
#include <fescript/fescript_function.hpp>

namespace fescript {
FescriptInstance::FescriptInstance()
    : klass{nullptr} {
}

FescriptInstance::FescriptInstance(std::shared_ptr<FescriptClass> klass)
    : klass{std::move(klass)} {
}

FescriptInstance::~FescriptInstance() {
}

[[nodiscard]] Object FescriptInstance::get(const Token &name) {
  if (auto it = this->fields.find(name.lexeme); it != this->fields.end()) {
    return it->second;
  }
  std::shared_ptr<FescriptFunction> method = this->klass->find_method(name.lexeme);
  if (method != nullptr)
    return method->bind(shared_from_this());
  throw RuntimeError(name, "undefined property '" + name.lexeme + "'.");
}

void FescriptInstance::set(const Token &name, Object value) {
  this->fields[name.lexeme] = value;
}

[[nodiscard]] std::string FescriptInstance::to_string() {
  return this->klass->name + " instance";
}
}// namespace fescript