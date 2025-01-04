// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <string>
#include <resources/cache_resource.hpp>
#include <resources/meta_data_resource.hpp>

namespace fresh {
template<typename Key, typename Value>
void CacheResource<Key, Value>::push_overwrite(
  const Key& sprite_path,
  const Value& meta
) noexcept {
  this->_cache_format.insert_or_assign(sprite_path, meta);
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType::const_iterator
CacheResource<Key, Value>::get_sprite_iter(const Key& sprite_path) const noexcept {
  return this->_cache_format.find(sprite_path);
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType::iterator CacheResource<Key, Value>::begin() noexcept {
  return this->_cache_format.begin();
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType::iterator CacheResource<Key, Value>::end() noexcept {
  return this->_cache_format.end();
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType::const_iterator
CacheResource<Key, Value>::cbegin() const noexcept {
  return this->_cache_format.cbegin();
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType::const_iterator
CacheResource<Key, Value>::cend() const noexcept {
  return this->_cache_format.cend();
}

template<typename Key, typename Value>
[[nodiscard]] typename CacheResource<Key, Value>::KeyValueType& CacheResource<Key, Value>::get_map() noexcept {
  return this->_cache_format;
}

template class CacheResource<std::string, SpriteMetadata>;
template class CacheResource<std::pair<std::string, std::string>, ShaderMetadata>;
} // namespace fresh