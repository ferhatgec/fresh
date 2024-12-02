// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "objects/base_object.hpp"
#include <vector>
#include <memory>

namespace fresh {
class RenderObjects {
public:
  static constexpr auto NotFound = -1;
  RenderObjects() = default;
  ~RenderObjects() = default;

  [[nodiscard]] static const std::shared_ptr<BaseObject>& get_object(std::string_view object_name) noexcept;
  [[nodiscard]] static const std::shared_ptr<BaseObject>& get_object(std::size_t object_id) noexcept;
  [[nodiscard]] static std::size_t get_index_of_object(std::string_view object_name) noexcept;

  static void push_object(std::shared_ptr<BaseObject> object) noexcept;

  [[nodiscard]] static std::shared_ptr<BaseObject>&& pop_object(std::string_view object_name) noexcept;
  static void pop_object_delete(std::string_view object_name) noexcept;

  static inline std::vector<std::shared_ptr<BaseObject>> objects_to_render; // other inherited classes will be sliced.
  static inline idk::f80 delta_ms { 0_f80 };
  static inline std::shared_ptr<BaseObject> NullptrRefer = nullptr;
};
} // namespace fresh