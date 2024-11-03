// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>
#include <resources/point_resource.hpp>
#include <resources/color_resource.hpp>
#include "fes_keywords.hpp"
#include <vector>
#include <memory>

namespace fresh::fes {
class FesBaseAST {
public:
  FesBaseAST() noexcept = default;
  virtual ~FesBaseAST() noexcept = default;
};

class FesObjectAST : public FesBaseAST {
public:
  friend class FesParser;

  /// FesObjectAST::FesObjectAST() is constructor of FesObjectAST;
  /// used for storing BaseObject properties. hence any object must
  /// be derived from FesObjectAST.
  FesObjectAST() noexcept;

  /// FesObjectAST::~FesObjectAST() is default constructor;
  /// used for BaseObject and any other objects are derived from it.
  ~FesObjectAST() noexcept override = default;

  [[nodiscard]] const Keywords& get_type() const noexcept;
  [[nodiscard]] const idk::usize& get_group_id() const noexcept;
  [[nodiscard]] const bool& get_disabled() const noexcept;
  [[nodiscard]] const bool& get_visible() const noexcept;
  [[nodiscard]] std::vector<std::shared_ptr<FesObjectAST>>& get_sub_groups() noexcept;
  [[nodiscard]] const PointResource& get_size() const noexcept;
  [[nodiscard]] const PointResource& get_position() const noexcept;
  [[nodiscard]] const std::string& get_name() const noexcept;
  [[nodiscard]] const std::string& get_fescript_path() const noexcept;

  void set_type(Keywords keyword) noexcept;
  void set_group_id(idk::usize id) noexcept;
  void set_disabled(bool disabled) noexcept;
  void set_visible(bool visible) noexcept;
  void set_size(const PointResource& size) noexcept;
  void set_position(const PointResource& pos) noexcept;
  void set_name(const std::string& name) noexcept;
  void set_fescript_path(const std::string& path) noexcept;
protected:
  friend class FesParser;
  Keywords _object_type;
  idk::usize _group_id;
  bool _disabled, _visible;
  std::vector<std::shared_ptr<FesObjectAST>> _sub_groups;
  PointResource _size, _pos;
  std::string _name, _fescript_path;
};

class FesAreaObjectAST : public FesObjectAST {
public:
  FesAreaObjectAST() noexcept;
  ~FesAreaObjectAST() noexcept override = default;
};

class FesCameraObjectAST : public FesObjectAST {
public:
  FesCameraObjectAST() noexcept;
  ~FesCameraObjectAST() noexcept override = default;
};

class FesColorObjectAST : public FesObjectAST {
public:
  FesColorObjectAST() noexcept;
  ~FesColorObjectAST() noexcept override = default;

  [[nodiscard]] const ColorResource& get_color() const noexcept;
  void set_color(const ColorResource& color) noexcept;
protected:
  friend class FesParser;
  ColorResource _color;
};

class FesFileObjectAST : public FesObjectAST {
public:
  FesFileObjectAST() noexcept;
  ~FesFileObjectAST() noexcept override = default;

  [[nodiscard]] const std::string& get_file_path() const noexcept;
  void set_file_path(const std::string& path) noexcept;
protected:
  std::string _file_path;
};

class FesLabelObjectAST : public FesObjectAST {
public:
  FesLabelObjectAST() noexcept;
  ~FesLabelObjectAST() noexcept override = default;

  [[nodiscard]] std::shared_ptr<FesColorObjectAST>& get_bg_color() noexcept;
  [[nodiscard]] std::shared_ptr<FesColorObjectAST>& get_fg_color() noexcept;
  [[nodiscard]] const idk::u32& get_font_size() const noexcept;
  [[nodiscard]] const std::string& get_label_text() const noexcept;
  [[nodiscard]] const std::string& get_label_path() const noexcept;

  void set_font_size(idk::u32 font_size) noexcept;
  void set_label_text(const std::string& text) noexcept;
  void set_label_path(const std::string& path) noexcept;
protected:
  friend class FesParser;
  std::shared_ptr<FesColorObjectAST> _bg, _fg;
  idk::u32 _font_size;
  std::string _label_text, _label_path;
};

class FesSpriteObjectAST : public FesObjectAST {
public:
  FesSpriteObjectAST() noexcept;
  ~FesSpriteObjectAST() noexcept override = default;

  [[nodiscard]] const std::string& get_sprite_path() const noexcept;
  void set_sprite_path(const std::string& path) noexcept;
protected:
  std::string _sprite_path;
};

class FesProjectObjectAST : public FesObjectAST {
public:
  FesProjectObjectAST() noexcept;
  ~FesProjectObjectAST() noexcept override = default;

  [[nodiscard]] const std::string& get_project_name() const noexcept;
  [[nodiscard]] const std::string& get_default_fes_file() const noexcept;
  [[nodiscard]] const PointResource& get_default_window_size() const noexcept;
  [[nodiscard]] std::shared_ptr<FesColorObjectAST>& get_default_clear_color() noexcept;
  [[nodiscard]] std::vector<std::shared_ptr<FesFileObjectAST>>& get_preloaded_fes_files() noexcept;

  void set_project_name(const std::string& proj_name) noexcept;
  void set_default_fes_file(const std::string& def_fes_file) noexcept;
  void set_default_size(const PointResource& def_size) noexcept;
protected:
  friend class FesParser;
  std::string _project_name, _default_fes_file;
  PointResource _default_size;
  std::shared_ptr<FesColorObjectAST> _default_clear_color;
  std::vector<std::shared_ptr<FesFileObjectAST>> _preloaded_fes_files;
};

class FesImportObjectAST : public FesObjectAST {
public:
  FesImportObjectAST() noexcept;
  ~FesImportObjectAST() noexcept override = default;

  [[nodiscard]] const std::string& get_import_path() const noexcept;
  void set_import_path(const std::string& imp_path) noexcept;
protected:
  std::string _import_path;
};
} // namespace fresh::fes

