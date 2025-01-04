// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <unordered_map>

namespace fresh {
// taken from boost hash_combine
template<typename T>
static void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hash_value;
  seed ^= hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
} // namespace fresh

namespace std {
// adds std::hash support for std::pair.
template<typename S, typename T>
struct hash<pair<S, T>> {
  using Type = pair<S, T>;
  size_t operator()(const Type& v) const {
    size_t seed { 0 };
    fresh::hash_combine(seed, v.first);
    fresh::hash_combine(seed, v.second);
    return seed;
  }
};

template<typename S, typename T>
struct equal_to<pair<S, T>> {
  using Type = pair<S, T>;
  bool operator()(const Type& lhs, const Type& rhs) const {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
};
} // namespace std

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