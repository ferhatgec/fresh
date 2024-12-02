// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fes/fes_ast.hpp>

namespace fresh::fes {
FesObjectAST::FesObjectAST() noexcept
    : _object_type{Keywords::BaseObject},
      _group_id{0},
      _disabled{false},
      _visible{true} {}

[[nodiscard]] const Keywords& FesObjectAST::get_type() const noexcept {
  return this->_object_type;
}

[[nodiscard]] const idk::usize& FesObjectAST::get_group_id() const noexcept {
  return this->_group_id;
}

[[nodiscard]] const bool& FesObjectAST::get_disabled() const noexcept {
  return this->_disabled;
}

[[nodiscard]] const bool& FesObjectAST::get_visible() const noexcept {
  return this->_visible;
}

[[nodiscard]] std::vector<std::shared_ptr<FesObjectAST>>& FesObjectAST::get_sub_groups() noexcept {
  return this->_sub_groups;
}

[[nodiscard]] const PointResource& FesObjectAST::get_size() const noexcept {
  return this->_size;
}

[[nodiscard]] const PointResource& FesObjectAST::get_position() const noexcept {
  return this->_pos;
}

[[nodiscard]] const std::string& FesObjectAST::get_name() const noexcept {
  return this->_name;
}

[[nodiscard]] const std::string& FesObjectAST::get_fescript_path()
    const noexcept {
  return this->_fescript_path;
}

[[nodiscard]] const ColorResource& FesObjectAST::get_color() const noexcept {
  return this->_color;
}

void FesObjectAST::set_type(Keywords keyword) noexcept {
  this->_object_type = keyword;
}

void FesObjectAST::set_group_id(idk::usize id) noexcept {
  this->_group_id = id;
}

void FesObjectAST::set_disabled(bool disabled) noexcept {
  this->_disabled = disabled;
}

void FesObjectAST::set_visible(bool visible) noexcept {
  this->_visible = visible;
}

void FesObjectAST::set_size(const PointResource& size) noexcept {
  this->_size = size;
}

void FesObjectAST::set_position(const PointResource& pos) noexcept {
  this->_pos = pos;
}

void FesObjectAST::set_name(const std::string& name) noexcept {
  this->_name = name;
}

void FesObjectAST::set_fescript_path(const std::string& path) noexcept {
  this->_fescript_path = path;
}

void FesObjectAST::set_color(const ColorResource& res) noexcept {
  this->_color = res;
}

FesCircleObjectAST::FesCircleObjectAST() noexcept {
  this->_object_type = CircleObject;
}

void FesCircleObjectAST::set_resource(const CircleResource& res) noexcept {
  this->_circle_res = res;
}

[[nodiscard]] const CircleResource& FesCircleObjectAST::get_resource()
    const noexcept {
  return this->_circle_res;
}

FesPolygonObjectAST::FesPolygonObjectAST() noexcept {
  this->_object_type = PolygonObject;
}

[[nodiscard]] std::vector<std::shared_ptr<FesVertexAST>>& FesPolygonObjectAST::get_resource_mutable() noexcept {
  return this->_pol_res;
}

FesRectangleObjectAST::FesRectangleObjectAST() noexcept {
  this->_object_type = RectangleObject;
}

FesAreaObjectAST::FesAreaObjectAST() noexcept {
  this->_object_type = AreaObject;
}

FesCircleAreaObjectAST::FesCircleAreaObjectAST() noexcept {
  this->_object_type = Keywords::CircleAreaObject;
}

void FesCircleAreaObjectAST::set_resource(const CircleResource& res) noexcept {
  this->_circle_res = res;
}

[[nodiscard]] const CircleResource& FesCircleAreaObjectAST::get_resource()
    const noexcept {
  return this->_circle_res;
}

FesPolygonAreaObjectAST::FesPolygonAreaObjectAST() noexcept {
  this->_object_type = Keywords::PolygonAreaObject;
}

[[nodiscard]] std::vector<std::shared_ptr<FesVertexAST>>& FesPolygonAreaObjectAST::get_resource_mutable() noexcept {
  return this->_pol_res;
}

FesRectangleAreaObject::FesRectangleAreaObject() noexcept {
  this->_object_type = Keywords::RectangleAreaObject;
}

FesCameraObjectAST::FesCameraObjectAST() noexcept {
  this->_object_type = Keywords::CameraObject;
}

FesColorObjectAST::FesColorObjectAST() noexcept {
  this->_object_type = Keywords::Color;
}

[[nodiscard]] const ColorResource& FesColorObjectAST::get_resource() const noexcept {
  return this->_color;
}

void FesColorObjectAST::set_resource(const ColorResource& color) noexcept {
  this->_color = color;
}

FesFileObjectAST::FesFileObjectAST() noexcept {
  this->_object_type = Keywords::File;
}

[[nodiscard]] const std::string& FesFileObjectAST::get_file_path() const noexcept {
  return this->_file_path;
}

void FesFileObjectAST::set_file_path(const std::string& path) noexcept {
  this->_file_path = path;
}

FesLabelObjectAST::FesLabelObjectAST() noexcept {
  this->_object_type = Keywords::LabelObject;
  this->_bg = std::make_shared<FesColorObjectAST>();
  this->_fg = std::make_shared<FesColorObjectAST>();
}

[[nodiscard]] std::shared_ptr<FesColorObjectAST>& FesLabelObjectAST::get_bg_color() noexcept {
  return this->_bg;
}

[[nodiscard]] std::shared_ptr<FesColorObjectAST>& FesLabelObjectAST::get_fg_color() noexcept {
  return this->_fg;
}

[[nodiscard]] const idk::u32& FesLabelObjectAST::get_font_size() const noexcept {
  return this->_font_size;
}

[[nodiscard]] const std::string& FesLabelObjectAST::get_label_text() const noexcept {
  return this->_label_text;
}

[[nodiscard]] const std::string& FesLabelObjectAST::get_label_path() const noexcept {
  return this->_label_path;
}

void FesLabelObjectAST::set_font_size(idk::u32 font_size) noexcept {
  this->_font_size = font_size;
}

void FesLabelObjectAST::set_label_text(const std::string& text) noexcept {
  this->_label_text = text;
}

void FesLabelObjectAST::set_label_path(const std::string& path) noexcept {
  this->_label_path = path;
}

FesSpriteObjectAST::FesSpriteObjectAST() noexcept {
  this->_object_type = Keywords::SpriteObject;
}

[[nodiscard]] const std::string& FesSpriteObjectAST::get_sprite_path() const noexcept {
  return this->_sprite_path;
}

void FesSpriteObjectAST::set_sprite_path(const std::string& path) noexcept {
  this->_sprite_path = path;
}

FesProjectObjectAST::FesProjectObjectAST() noexcept {
  this->_object_type = Keywords::Project;
  this->_default_clear_color = std::make_shared<FesColorObjectAST>();
}

[[nodiscard]] const std::string& FesProjectObjectAST::get_project_name() const noexcept {
  return this->_project_name;
}

[[nodiscard]] const std::string& FesProjectObjectAST::get_default_fes_file() const noexcept {
  return this->_default_fes_file;
}

[[nodiscard]] const PointResource& FesProjectObjectAST::get_default_window_size() const noexcept {
  return this->_default_size;
}

[[nodiscard]] std::shared_ptr<FesColorObjectAST>& FesProjectObjectAST::get_default_clear_color() noexcept {
  return this->_default_clear_color;
}

[[nodiscard]] std::vector<std::shared_ptr<FesFileObjectAST>>& FesProjectObjectAST::get_preloaded_fes_files() noexcept {
  return this->_preloaded_fes_files;
}

void FesProjectObjectAST::set_project_name(const std::string& proj_name) noexcept {
  this->_project_name = proj_name;
}

void FesProjectObjectAST::set_default_fes_file(const std::string& def_fes_file) noexcept {
  this->_default_fes_file = def_fes_file;
}

void FesProjectObjectAST::set_default_size(const PointResource& def_size) noexcept {
  this->_size = def_size;
}

FesImportObjectAST::FesImportObjectAST() noexcept {
  this->_object_type = Keywords::Import;
}

[[nodiscard]] const std::string& FesImportObjectAST::get_import_path() const noexcept {
  return this->_import_path;
}

void FesImportObjectAST::set_import_path(const std::string& imp_path) noexcept {
  this->_import_path = imp_path;
}

FesVertexAST::FesVertexAST() noexcept {
  this->_object_type = Vertex;
}

void FesVertexAST::set_resource(const PointResource& res) noexcept {
  this->_vertex = res;
}

[[nodiscard]] const PointResource& FesVertexAST::get_resource() const noexcept {
  return this->_vertex;
}

[[nodiscard]] PointResource& FesVertexAST::get_resource_mutable() noexcept {
  return this->_vertex;
}
} // namespace fresh::fes
