// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <variant>

#include "fescript_token_type.hpp"

#define StringIndex 0
#define LongDoubleIndex 1
#define BoolIndex 2
#define NullptrIndex 3
#define FescriptFunctionIndex 4
#define FescriptClassIndex 5
#define FescriptInstanceIndex 6
#define FescriptArrayIndex 7
#define FescriptDictIndex 8
#define FescriptCallableIndex 9

namespace fescript {
class FescriptFunction;
class FescriptClass;
class FescriptInstance;
class FescriptArray;
class FescriptDict;
class FescriptCallable;

using Object =
  std::variant<std::string, long double, bool, std::nullptr_t,
               std::shared_ptr<FescriptFunction>, std::shared_ptr<FescriptClass>,
               std::shared_ptr<FescriptInstance>,
               std::shared_ptr<FescriptArray>,
               std::shared_ptr<FescriptDict>,
               std::shared_ptr<FescriptCallable>>;

class Token {
public:
  Token(TokenType type, std::string lexeme, Object literal, int line) noexcept;
  Token(const Token& token) noexcept;
  Token() {}
  ~Token() noexcept;
  [[nodiscard]] std::string to_string() const noexcept;
  [[nodiscard]] static std::string to_string(const Object& object) noexcept;
public:
  TokenType type;
  std::string lexeme;
  Object literal;
  int line;
};

static inline Token empty_token = Token(TokenType::SEMICOLON, "", std::string(""), -1);
}// namespace fescript