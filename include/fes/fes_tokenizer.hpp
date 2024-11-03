// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

// fes is FreshEngineScene, it's human-readable text scene format
// especially developed and optimized for freshEngine.

#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <unordered_map>
#include <types/predefined.hpp>
#include "fes_keywords.hpp"

namespace fresh::fes {
class FesTokenizer {
public:
  friend class FesParser;
  FesTokenizer() noexcept;
  ~FesTokenizer() noexcept = default;

  /// FesTokenizer::load_from(std::string, bool) loads given context;
  /// and tokenizes it.
  void load_from(const std::string& ctx, bool file = true) noexcept;

  /// FesTokenizer::tokenize() does the tokenization process.
  void tokenize() noexcept;
  std::vector<std::pair<std::string, Keywords>> _tokens;

private:
  void
  _check_and_push() noexcept;
protected:
  std::string _raw_file_data, _temp;
  idk::usize _i;
  bool _is_string_data;

  static inline std::unordered_map<std::string, Keywords> keywords = {
    {"[", Keywords::NodeInit},
    {"]", Keywords::NodeInit},
    {",", Keywords::NextObject},
    {";", Keywords::LastObject},
    {"{", Keywords::ListObjectInit},
    {"}", Keywords::ListObjectEnd},
    {"=", Keywords::Assign}
  };
};
} // namespace fresh::fes