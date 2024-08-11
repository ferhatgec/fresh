//
// Created by gech on 2/4/2024.
//

#pragma once

// fes is FreshEngineScene, it's human readable text scene format
// especially developed and optimized for freshEngine.

#include <types/stringview.hpp>
#include "../../libs/idk/idk/containers/vector.hpp"
#include "../../libs/idk/idk/utilities/pair.hpp"
#include "fes_keywords.hpp"

namespace fresh {
namespace fes {
class FesTokenizer {
public:
  friend class FesParser;
  FesTokenizer();
  FesTokenizer(const idk::StringViewChar& fes_raw_text_data_or_file_path, bool file = true);
  FesTokenizer(idk::StringViewChar&& fes_raw_text_data_or_file_path, bool file = true);
  ~FesTokenizer();

  // most of the time, fes scenes contains not that large data.
  // so memory mapped i/o is a bit overkill here, so we will use normal way.
  // if you want to read files fast, use it on your own, then pass file argument as false.
  // fes will automatically initialize raw_text_data variable with fes_raw_text_data_or_file_path.
  void
  load_from(const idk::StringViewChar& fes_raw_text_data_or_file_path, bool file = true) noexcept;

  void
  load_from(idk::StringViewChar&& fes_raw_text_data_or_file_path, bool file = true) noexcept;

  void
  tokenize() noexcept;

  idk::StringViewChar _raw_file_data;
private:
  void
  _check_and_push() noexcept;
protected:
  idk::Vector<idk::Pair<idk::StringViewChar, Keywords>> _tokens;
  idk::StringViewChar _temp;
  idk::usize _i { 0_usize };
  bool _is_string_data { false };
};
} // namespace fes
} // namespace fresh