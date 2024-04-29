// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include "../../include/fescript/fescript_array.hpp"
#include "../../include/fescript/fescript_class.hpp"
#include "../../include/fescript/fescript_dict.hpp"
#include "../../include/fescript/fescript_function.hpp"
#include "../../include/fescript/fescript_instance.hpp"
#include "../../include/fescript/fescript_token.hpp"

namespace fescript {
Token::Token(TokenType type, std::string lexeme, Object literal, int line, bool is_variadic) noexcept
    : type{type},
      lexeme{lexeme},
      literal{std::move(literal)},
      line{line},
      is_variadic{is_variadic} {
}

Token::Token(const Token& token) noexcept
    : type{token.type},
      lexeme{token.lexeme},
      literal{token.literal},
      line{token.line},
      is_variadic{token.is_variadic} {
}

Token::~Token() noexcept {
}

[[nodiscard]] std::string Token::to_string() const noexcept {
  std::string literal_text;
  switch (this->type) {
  case TokenType::IDENTIFIER: {
    literal_text = this->lexeme;
    break;
  }
  default: {
    literal_text = Token::to_string(this->literal);
    break;
  }
  }
  return fescript::to_string(this->type) + " " + this->lexeme + " " + literal_text;
}

[[nodiscard]] std::string Token::to_string(const Object& object) noexcept {
  std::string literal_text;
  switch (object.index()) {
  case StringIndex: {
    literal_text = std::get<StringIndex>(object);
    break;
  }
  case LongDoubleIndex: {
    literal_text = std::to_string(std::get<LongDoubleIndex>(object));
    break;
  }
  case BoolIndex: {
    literal_text = std::get<BoolIndex>(object) ? "true" : "false";
    break;
  }
  case FescriptFunctionIndex: {
    literal_text = std::get<FescriptFunctionIndex>(object)->to_string();
    break;
  }
  case FescriptClassIndex: {
    literal_text = std::get<FescriptClassIndex>(object)->to_string();
    break;
  }
  case FescriptInstanceIndex: {
    literal_text = std::get<FescriptInstanceIndex>(object)->to_string();
    break;
  }
  case FescriptArrayIndex: {
    literal_text = std::get<FescriptArrayIndex>(object)->to_string();
    break;
  }
  case FescriptDictIndex: {
    literal_text = std::get<FescriptDictIndex>(object)->to_string();
    break;
  }
  default: {
    literal_text = "nil";
    break;
  }
  }
  return literal_text;
}
}// namespace fescript