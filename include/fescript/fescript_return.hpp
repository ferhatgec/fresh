// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <exception>

#include "fescript_token.hpp"

namespace fescript {
class FescriptReturnException : std::exception {
public:
  FescriptReturnException(Object value) : value{value} {}
  const Object value;
};
}// namespace fescript