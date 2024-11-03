// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <map>
#include <string_view>
#include <vector>

#include "fescript_error.hpp"
#include "fescript_token.hpp"

namespace fescript {
class Scanner {
public:
  Scanner(std::string_view source);

  [[nodiscard]] std::vector<Token> scan_tokens();

private:
  void scan_token();
  void identifier();
  void number();
  void string();

  [[nodiscard]] const char &peek();
  [[nodiscard]] const char &peek_next();
  const char &advance();

  [[nodiscard]] bool match(const char &expected);
  [[nodiscard]] bool is_alpha(const char &c);
  [[nodiscard]] bool is_alpha_numeric(const char &c);
  [[nodiscard]] bool is_digit(const char &c);
  [[nodiscard]] bool is_at_end();

  void add_token(TokenType type);
  void add_token(TokenType type, Object literal);

private:
  std::string_view source;
  std::vector<Token> tokens;

  int start{0},
    current{0},
    line{1};

  static inline const char null_char = '\0';
  static inline const std::map<std::string, TokenType> keywords{
    {"and", TokenType::TOKEN_AND},
    {"class", TokenType::TOKEN_CLASS},
    {"else", TokenType::TOKEN_ELSE},
    {"elif", TokenType::TOKEN_ELIF},
    {"false", TokenType::TOKEN_FALSE},
    {"for", TokenType::TOKEN_FOR},
    {"fn", TokenType::TOKEN_FUN},
    {"if", TokenType::TOKEN_IF},
    {"nil", TokenType::TOKEN_NIL},
    {"or", TokenType::TOKEN_OR},
    {"return", TokenType::TOKEN_RETURN},
    {"super", TokenType::TOKEN_SUPER},
    {"this", TokenType::TOKEN_THIS},
    {"true", TokenType::TOKEN_TRUE},
    {"def", TokenType::TOKEN_VAR},
    {"while", TokenType::TOKEN_WHILE},
    {"not", TokenType::TOKEN_BANG}
  };
};
}// namespace fescript