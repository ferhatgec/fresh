// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_token.hpp"
#include <vector>

namespace fresh {
class PointResource;
class BBoxResource;
} // namespace fresh
namespace fescript {
class Array;
class Interpreter;

class FescriptArray : public std::enable_shared_from_this<FescriptArray> {
  friend class Token;
  friend class Parser;
  friend class Interpreter;
public:
  FescriptArray() noexcept;
  ~FescriptArray() noexcept = default;

  [[nodiscard]] const Object& get_value(std::size_t index) const noexcept;
  [[nodiscard]] const std::string& to_string() noexcept;

  [[nodiscard]] const std::vector<Object>& get_values() noexcept;

  void set_array(const std::vector<Object>& values) noexcept;
  void set_array(std::vector<Object>&& values) noexcept;

  /// dummy bool used here for function tagging, since both PointResource and
  /// BBoxResource takes optional float values and those are not marked as explicit;
  /// long double values can be implicitly converted to float values, which leads
  /// compiler error since 3 possible functions available.
  void push_value(const Object& value, bool dummy = false) noexcept;
  void push_value(const fresh::PointResource& value, bool dummy) noexcept;
  void push_value(const fresh::BBoxResource& value, bool dummy) noexcept;

  void pop_value() noexcept;
  void clear() noexcept;
  void remove_value(std::size_t index) noexcept;
  void push_value(std::size_t index, const Object& value) noexcept;

  [[nodiscard]] std::size_t get_size() const noexcept;
private:
  std::string _to_string_cache;
  std::vector<Object> _values;
  bool _needs_update;
};
}