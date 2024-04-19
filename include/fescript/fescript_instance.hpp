// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include "fescript_token.hpp"
#include <map>

namespace fescript {
class FescriptClass;
class Token;

class FescriptInstance : public std::enable_shared_from_this<FescriptInstance> {
public:
  FescriptInstance();
  FescriptInstance(std::shared_ptr<FescriptClass> klass);
  ~FescriptInstance();

  [[nodiscard]] Object get(const Token &name);
  void set(const Token &name, Object value);
  [[nodiscard]] std::string to_string();

private:
  std::shared_ptr<FescriptClass> klass;
  std::map<std::string, Object> fields;
};
}// namespace fescript