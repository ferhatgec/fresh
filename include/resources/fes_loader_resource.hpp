// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <fes/fes_ast.hpp>
#include <fes/fes_keywords.hpp>
#include <fes/fes_parser.hpp>
#include <fes/fes_tokenizer.hpp>
#include <objects/base_object.hpp>
#include <functional>

namespace fresh {
static inline constexpr int SameCstr { 0 };
class FesLoaderResource {
 public:
  FesLoaderResource() noexcept = default;
  ~FesLoaderResource() noexcept = default;

  [[nodiscard]] fes::FesParser& get_parser() noexcept;
  void load_fes(const std::string& ctx, bool is_file = true) noexcept;

  [[nodiscard]] std::shared_ptr<BaseObject> generate() noexcept;

  /// FesLoaderResource::generate_from_ast(std::shared_ptr<FesObjectAST>)
  /// generates std::shared_ptr<BaseObject> that contains the same information
  /// as FesObjectAST version.
  [[nodiscard]] std::shared_ptr<BaseObject> generate_from_ast(
      const std::shared_ptr<fes::FesObjectAST>& fes_obj) noexcept;

  /// FesLoaderResource::generate_from_object(std::shared_ptr<BaseObject>)
  /// generates std::shared_ptr<FesObjectAST> that contains the same information
  /// as BaseObject version.
  [[nodiscard]] std::shared_ptr<fes::FesObjectAST> generate_from_object(
      const std::shared_ptr<BaseObject>& fresh_obj) noexcept;

  [[nodiscard]] std::string serialize(
      const std::shared_ptr<BaseObject>& base_object) noexcept;

  [[nodiscard]] std::string serialize_object(
      const std::shared_ptr<fes::FesObjectAST>& fes_obj,
      std::uint32_t whitespace_count = 0) noexcept;

  template<typename T>
  [[nodiscard]] std::string serialize_list(
      const std::vector<std::shared_ptr<T>>& fes_obj,
      std::uint32_t whitespace_count = 0) noexcept;
 private:
  /// FesLoaderResource::_set_baseobject_properties(std::shared_ptr<FesObjectAST>,
  /// std::shared_ptr<BaseObject>) fills BaseObject class properties using
  /// FesObjectAST properties. specific properties of custom BaseObject-derived
  /// classes should call this function first; then should set their own
  /// properties from their FesObjectAST derived classes. so; xObject should
  /// have FesxObjectAST interface too.
  static void _set_baseobject_properties(
      const std::shared_ptr<fes::FesObjectAST>& fes_obj,
      const std::shared_ptr<BaseObject>& fresh_obj) noexcept;

  static void _set_fesobject_properties(
      const std::shared_ptr<BaseObject>& fresh_obj,
      std::shared_ptr<fes::FesObjectAST>& fes_obj) noexcept;

  /// FesLoaderResource::_create_object(Keywords) used for creating new
  /// BaseObject-derived objects. but you probably need to cast it later then.
  /// ----
  /// note: fes::Import is an exception here.
  [[nodiscard]] static std::shared_ptr<BaseObject> _create_object(
      fes::Keywords kw) noexcept;

  [[nodiscard]] static std::shared_ptr<fes::FesObjectAST> _create_fes_object(
      const char* fresh_kw) noexcept;

  static void _serialize_append(std::string& ctx,
                                const std::string& input,
                                std::uint32_t whitespace_count,
                                bool newline = false) noexcept;

  [[nodiscard]] static std::string _whitespace_generate(
      std::uint32_t whitespace_count) noexcept;

  [[nodiscard]] static std::string _bool_to_str(bool input) noexcept;

  fes::FesParser _parser;
  std::string _ctx;
  bool _file;

  /// FesLoaderResource::id_counter is globally accessible counter
  /// that is used for initializing _object_id. it might be better
  /// if we use some hash functions instead of just counting
  /// the newly created objects.
  static inline std::uint32_t id_counter{0};
};
} // namespace fresh