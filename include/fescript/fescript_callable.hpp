// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <vector>

#include "fescript_token.hpp"

namespace fescript {
class Interpreter;

class FescriptCallable {
public:
  FescriptCallable() : _is_variadic{false} {}
  virtual ~FescriptCallable() = default;
  [[nodiscard]] virtual int arity() = 0;
  [[nodiscard]] virtual Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) = 0;


  [[nodiscard]] virtual constexpr const char* to_string() const noexcept = 0;

  [[nodiscard]] const bool& is_variadic() const noexcept {
    return _is_variadic;
  }
protected:
  bool _is_variadic;
};
}// namespace fescript