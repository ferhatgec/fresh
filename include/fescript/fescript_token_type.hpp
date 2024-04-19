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
  LEFT_PAREN = '(',
  RIGHT_PAREN = ')',
  LEFT_BRACE = '{',
  RIGHT_BRACE = '}',
  COMMA = ',',
  DOT = '.',
  MINUS = '-',
  PLUS = '+',
  SEMICOLON = ';',
  SLASH = '/',
  STAR = '*',
  LEFT_BOX_PAREN = '[',
  RIGHT_BOX_PAREN = ']',
  COLON = ':',

  // One or two character tokens.
  BANG = -127,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,
  ARRAY,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  ELIF,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  EOF_
};

static const std::array<std::string, 40> strings {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
  "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH",
  "STAR", "BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL", "IDENTIFIER",
  "STRING", "NUMBER", "AND", "CLASS", "ELSE", "ELIF",
  "FALSE", "FUN", "FOR", "IF", "NIL",
  "OR", "PRINT", "RETURN", "SUPER", "THIS",
  "TRUE", "VAR", "WHILE", "EOF"
};

static std::string to_string(TokenType type) {
  return fescript::strings[static_cast<int>(type)];
}
}// namespace fescript