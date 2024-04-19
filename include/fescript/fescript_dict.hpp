#pragma once

#include "fescript_token.hpp"
#include <map>
#include <unordered_map>

namespace fescript {
class Dict;
class Interpreter;
class FescriptDict : public std::enable_shared_from_this<FescriptDict> {
  friend class Token;
  friend class Parser;
  friend class Interpreter;
public:
  FescriptDict();
  ~FescriptDict();

  [[nodiscard]] Object get(Object key);
  [[nodiscard]] std::string to_string();

private:
  // we need std::less implementation to use std::map with Object properly.
  // instead, using std::unordered_map is much better option.
  // we use dict for look-ups, they don't need to be ordered.
  std::unordered_map<Object, Object> dictionary;
};
}