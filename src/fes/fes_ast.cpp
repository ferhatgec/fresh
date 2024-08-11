#include <fes/fes_ast.hpp>

namespace fresh {
namespace fes {
FesBaseAST::FesBaseAST() {
}

FesBaseAST::~FesBaseAST() {
}

FesObjectAST::FesObjectAST() {
  this->_width = 0;
  this->_height = 0;
  this->_visible = true;
  this->_disabled = false;
  this->_position_y = 0;
  this->_position_x = 0;
  this->_group_id = 0;
  this->_object_type = Keywords::BaseObject;
}

FesObjectAST::~FesObjectAST() {
}

FesColorObjectAST::FesColorObjectAST() {
  this->_object_type = Keywords::Color;
}

FesColorObjectAST::FesColorObjectAST(FesColorObjectAST* color_object_ast) {
  if(color_object_ast) {
    this->_width = color_object_ast->_width;
    this->_height = color_object_ast->_height;
    this->_visible = color_object_ast->_visible;
    this->_disabled = color_object_ast->_disabled;
    this->_position_y = color_object_ast->_position_y;
    this->_position_x = color_object_ast->_position_x;
    this->_group_id = color_object_ast->_group_id;
    this->_red = color_object_ast->_red;
    this->_green = color_object_ast->_green;
    this->_blue = color_object_ast->_blue;
    this->_alpha = color_object_ast->_alpha;

    delete color_object_ast;
  } else {
    std::cout << "Engine error: Invalid pointer detected in FesColorObjectAST ctor.\n";
  }
}

FesColorObjectAST::~FesColorObjectAST() {
}

FesFileObjectAST::FesFileObjectAST() {
  this->_object_type = Keywords::File;
}

FesFileObjectAST::~FesFileObjectAST() {
}

FesLabelObjectAST::FesLabelObjectAST() {
  this->_object_type = Keywords::LabelObject;
  this->_bg_color = std::make_shared<FesColorObjectAST>();
  this->_fg_color = std::make_shared<FesColorObjectAST>();
}

FesLabelObjectAST::FesLabelObjectAST(FesLabelObjectAST* label_object_ast) {
  if(label_object_ast) {
    this->_width = label_object_ast->_width;
    this->_height = label_object_ast->_height;
    this->_visible = label_object_ast->_visible;
    this->_disabled = label_object_ast->_disabled;
    this->_position_y = label_object_ast->_position_y;
    this->_position_x = label_object_ast->_position_x;
    this->_group_id = label_object_ast->_group_id;
    this->_bg_color = idk::move(label_object_ast->_bg_color);
    this->_fg_color = idk::move(label_object_ast->_fg_color);

    this->_label_render_type = label_object_ast->_label_render_type;

    this->_font_size = label_object_ast->_font_size;

    this->_label_text = label_object_ast->_label_text;
    this->_label_path = label_object_ast->_label_path;

    delete label_object_ast;
  } else {
    std::cout << "Engine error: Invalid pointer detected in FesLabelObjectAST ctor.\n";
  }
}

FesLabelObjectAST::~FesLabelObjectAST() {
}

FesSpriteObjectAST::FesSpriteObjectAST() {
  this->_object_type = Keywords::SpriteObject;
}

FesSpriteObjectAST::FesSpriteObjectAST(FesSpriteObjectAST* sprite_object_ast) {
  if(sprite_object_ast) {
    this->_width = sprite_object_ast->_width;
    this->_height = sprite_object_ast->_height;
    this->_visible = sprite_object_ast->_visible;
    this->_disabled = sprite_object_ast->_disabled;
    this->_position_y = sprite_object_ast->_position_y;
    this->_position_x = sprite_object_ast->_position_x;
    this->_group_id = sprite_object_ast->_group_id;
    this->_sprite_path = sprite_object_ast->_sprite_path;

    delete sprite_object_ast;
  } else {
    std::cout << "Engine error: Invalid pointer detected in FesSpriteObjectAST ctor.\n";
  }
}

FesSpriteObjectAST::~FesSpriteObjectAST() {
}

FesGuiButtonObjectAST::FesGuiButtonObjectAST() {
  this->_object_type = Keywords::GuiButtonObject;

  this->_sprite_object = std::make_shared<FesSpriteObjectAST>();
  this->_on_clicked_sprite_object = std::make_shared<FesSpriteObjectAST>();
  this->_on_hover_sprite_object = std::make_shared<FesSpriteObjectAST>();

  this->_label_object = std::make_shared<FesLabelObjectAST>();
  this->_on_clicked_label_object = std::make_shared<FesLabelObjectAST>();
  this->_on_hover_label_object = std::make_shared<FesLabelObjectAST>();
}

FesGuiButtonObjectAST::~FesGuiButtonObjectAST() {
}

FesProjectObjectAST::FesProjectObjectAST() {
  this->_object_type = Keywords::Project;
  this->_default_clear_color = std::make_shared<FesColorObjectAST>();
}

FesProjectObjectAST::~FesProjectObjectAST() {
}

FesImportObjectAST::FesImportObjectAST() {
  this->_object_type = Keywords::Import;
}

FesImportObjectAST::~FesImportObjectAST() {
}
}// namespace fes
}// namespace fresh