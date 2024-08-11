// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_array.hpp>
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_dict.hpp>
#include <fescript/fescript_function.hpp>
#include <fescript/fescript_instance.hpp>
#include <fescript/fescript_interpreter.hpp>

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
  return Interpreter::stringify(object);
}
}// namespace fescript