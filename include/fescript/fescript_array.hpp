#pragma once

#include "fescript_token.hpp"
#include <vector>

namespace fescript {
class Array;
class Interpreter;
class FescriptArray : public std::enable_shared_from_this<FescriptArray> {
  friend class Token;
  friend class Parser;
  friend class Interpreter;
public:
  FescriptArray();
  ~FescriptArray();

  [[nodiscard]] Object get(const int index);
  [[nodiscard]] std::string to_string();
  
private:
  std::vector<Object> values;
};
}