// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <array>
#include <string>

namespace fescript {
enum TokenType {
  // Single-character tokens.
  TOKEN_LEFT_PAREN = '(',
  TOKEN_RIGHT_PAREN = ')',
  TOKEN_LEFT_BRACE = '{',
  TOKEN_RIGHT_BRACE = '}',
  TOKEN_COMMA = ',',
  TOKEN_DOT = '.',
  TOKEN_MINUS = '-',
  TOKEN_PLUS = '+',
  TOKEN_SEMICOLON = ';',
  TOKEN_SLASH = '/',
  TOKEN_STAR = '*',
  TOKEN_PERCENT = '%',
  TOKEN_LEFT_BOX_PAREN = '[',
  TOKEN_RIGHT_BOX_PAREN = ']',
  TOKEN_COLON = ':',

  // One or two character tokens.
  TOKEN_BANG = -127,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,

  // Literals.
  TOKEN_IDENTIFIER,
  TOKEN_STRING,
  TOKEN_NUMBER,
  TOKEN_ARRAY,

  // Keywords.
  TOKEN_AND,
  TOKEN_CLASS,
  TOKEN_ELSE,
  TOKEN_ELIF,
  TOKEN_FALSE,
  TOKEN_FUN,
  TOKEN_FOR,
  TOKEN_IF,
  TOKEN_NIL,
  TOKEN_OR,
  TOKEN_RETURN,
  TOKEN_SUPER,
  TOKEN_THIS,
  TOKEN_TRUE,
  TOKEN_VAR,
  TOKEN_WHILE,
  TOKEN_VARIADIC,

  TOKEN_EOF_
};

static const std::array<std::string, 41> strings {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
  "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH",
  "STAR", "PERCENT", "BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL", "IDENTIFIER",
  "STRING", "NUMBER", "AND", "CLASS", "ELSE", "ELIF",
  "FALSE", "FUN", "FOR", "IF", "NIL",
  "OR", "RETURN", "SUPER", "THIS",
  "TRUE", "VAR", "WHILE", "VARIADIC", "EOF"
};

static std::string to_string(TokenType type) {
  return fescript::strings[static_cast<int>(type)];
}
}// namespace fescript