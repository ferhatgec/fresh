// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once
#include "fes_ast.hpp"
#include "fes_tokenizer.hpp"
#include <memory>
#include <algorithm>

namespace fresh::fes {
class FesParser {
public:
  static constexpr std::uint8_t ConvertibleToFloat { 1 };

  friend class FesLoaderResource;

  FesParser() noexcept;
  ~FesParser() noexcept = default;

  /// FesParser::get_tokenizer() returns the current instance of FesTokenizer.
  [[nodiscard]] FesTokenizer& get_tokenizer() noexcept;

  /// FesParser::parse_variable(std::shared_ptr<FesObjectAST>)
  void parse_variable(std::shared_ptr<FesObjectAST> object_node) noexcept;

  /// FesParser::parse_list(std::shared_ptr<FesObjectAST>)
  void parse_list(std::shared_ptr<FesObjectAST> object_node) noexcept;

  /// FesParser::parse_object(std::shared_ptr<FesObjectAST>)
  void parse_object(std::shared_ptr<FesObjectAST> object_node) noexcept;

  /// FesParser::parse() parses given tokenizer array and generates AST from it.
  /// output then used to create new objects which is done by FesLoaderResource.
  void parse() noexcept;
private:
  idk::usize i = 0;

  static void check_project_object(const Keywords& kw, std::string_view msg) noexcept;

  /// FesParser::_parse_floats<std::floating_point>(std::string) parses
  /// given input and checks if it can be convertible to a floating point type.
  /// then returns a variant; check for its index; you can use ConvertibleToFloat
  /// variable to check if it can be convertible to floating point type.
  template<std::floating_point Fp>
  requires std::disjunction_v<std::is_same<Fp, double>, std::is_same<Fp, long double>>
  [[nodiscard]] std::variant<bool, Fp> _parse_floats(const std::string& str) noexcept {
    // that's just for parsing single float;
    // maximum values of int16_t and uint16_t should fit.
    std::uint16_t index = 0;
    std::int16_t sign_index { -1 };
    bool has_decimal { false };
    bool has_digits { false };

    // skip all spaces.
    while (index < str.size() && std::isspace(str[index])) {
      ++index;
    }

    if (index < str.size() && (str[index] == '+' || str[index] == '-')) {
      sign_index = static_cast<std::int16_t>(index);
      ++index;
    }

    Fp number { 0.0 };
    Fp frac { 0.0 };
    Fp divisor { 10.0 };

    while (index < str.size()) {
      const auto& c = str[index];

      if (std::isdigit(c)) {
        has_digits = true;
        if (has_decimal) {
          // get digit and divide it by 10^n to get actual floating point value.
          frac += (c - '0') / divisor;
          divisor *= 10.0;
        } else {
          // every digit multiply it by 10
          number = number * 10 + (c - '0');
        }
      } else if (c == '.' && !has_decimal) {
        has_decimal = true;
      } else {
        break;
      }
      ++index;
    }

    // add fractional part too
    number += frac;

    while (index < str.size() && std::isspace(str[index])) {
      ++index;
    }

    if (index == str.size() && has_digits) {
      // if sign_index == -1 then given str does not specify any operator (+, -)
      return sign_index >= 0 && str[sign_index] == '-' ? -number : number;
    }

    return false;
  }
protected:
  std::shared_ptr<FesObjectAST> _objects;
  FesTokenizer _tokenizer;
};
} // namespace fresh::fes