// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <unordered_map>

namespace fresh {
template<typename Key, typename Value>
class CacheResource {
public:
  using KeyValueType = std::unordered_map<Key, Value>;
  CacheResource() noexcept = default;
  ~CacheResource() noexcept = default;

  void push_overwrite(const Key& sprite_path, const Value& sprite_data) noexcept;
  [[nodiscard]] typename KeyValueType::const_iterator get_sprite_iter(const Key& sprite_path) const noexcept;
  [[nodiscard]] KeyValueType& get_map() noexcept;

  [[nodiscard]] typename KeyValueType::iterator begin() noexcept;
  [[nodiscard]] typename KeyValueType::iterator end() noexcept;
  [[nodiscard]] typename KeyValueType::const_iterator cbegin() const noexcept;
  [[nodiscard]] typename KeyValueType::const_iterator cend() const noexcept;
private:
  /// first part is sprite path, second is content of the sprite;
  /// mostly in RGBA format.
  KeyValueType _cache_format;
};
} // namespace fresh