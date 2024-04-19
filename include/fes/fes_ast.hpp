//
// Created by gech on 2/5/2024.
//

#ifndef FRESHENGINE_FES_AST_HPP
#define FRESHENGINE_FES_AST_HPP

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/types/stringview.hpp"
#include "../../libs/idk/idk/containers/vector.hpp"
#include "fes_keywords.hpp"
#include <memory>
//{
// [Project,
//  project_name = "Test Game",
//  default_window_size_w = 960,
//  default_window_size_h = 480,
//  default_clear_color = {
//    [Color,
//     red = 255,
//     green = 255,
//     blue = 255,
//     alpha = 255;
//    ];
//  },
//  default_fes_file = "example/scene.fes",
//  preloaded_fes_files = {
//    [File, name = "Scene1", file = "example/scene.fes"; ],
//    [File, name = "Scene2", file = "example/scene_1.fes"; ];
//  };
// ];
//};
namespace fresh {
namespace fes {
class FesBaseAST {
public:
  FesBaseAST();
  virtual ~FesBaseAST();
};

class FesObjectAST : public FesBaseAST {
public:
  friend class FesParser;

  FesObjectAST();
  ~FesObjectAST();

  Keywords _object_type = Keywords::Undefined;

  idk::usize _group_id;

  bool _disabled;
  bool _visible;

  idk::Vec<std::shared_ptr<FesObjectAST>> _sub_groups;

  idk::usize _width { 64_usize };
  idk::usize _height { 64_usize };
  idk::isize _position_x { 0_isize };
  idk::isize _position_y { 0_isize };

  idk::StringViewChar _name = ""; // name of the created object.
  idk::StringViewChar _fescript_path = "";
protected:
};

using FesGuiBaseObjectAST = FesObjectAST;
using FesAreaObjectAST = FesObjectAST;
using FesCameraObjectAST = FesObjectAST;
using FesCollisionObjectAST = FesObjectAST;

class FesColorObjectAST : public FesObjectAST {
public:
  FesColorObjectAST();
  FesColorObjectAST(FesColorObjectAST* color_object_ast);
  ~FesColorObjectAST();

  idk::u32 _red { 255_u32 };
  idk::u32 _green { 255_u32 };
  idk::u32 _blue { 255_u32 };
  idk::u32 _alpha { 255_u32 };
};

class FesFileObjectAST : public FesObjectAST {
public:
  FesFileObjectAST();
  ~FesFileObjectAST();

  idk::StringViewChar _file_path = "";
};

class FesLabelObjectAST : public FesObjectAST {
public:
  FesLabelObjectAST();
  FesLabelObjectAST(FesLabelObjectAST* label_object_ast);
  ~FesLabelObjectAST();

  std::shared_ptr<FesColorObjectAST> _bg_color;
  std::shared_ptr<FesColorObjectAST> _fg_color;

  LabelRenderType _label_render_type;

  idk::u32 _font_size { 16_u32 };

  idk::StringViewChar _label_text;
  idk::StringViewChar _label_path;
};

class FesSpriteObjectAST : public FesObjectAST {
public:
  FesSpriteObjectAST();
  FesSpriteObjectAST(FesSpriteObjectAST* sprite_object_ast);
  ~FesSpriteObjectAST();

  idk::StringViewChar _sprite_path;
};

class FesGuiButtonObjectAST : public FesGuiBaseObjectAST {
public:
  FesGuiButtonObjectAST();
  ~FesGuiButtonObjectAST();

  std::shared_ptr<FesSpriteObjectAST> _sprite_object;
  std::shared_ptr<FesSpriteObjectAST> _on_clicked_sprite_object;
  std::shared_ptr<FesSpriteObjectAST> _on_hover_sprite_object;

  std::shared_ptr<FesLabelObjectAST> _label_object;
  std::shared_ptr<FesLabelObjectAST> _on_clicked_label_object;
  std::shared_ptr<FesLabelObjectAST> _on_hover_label_object;
};

class FesProjectObjectAST : public FesObjectAST {
public:
  FesProjectObjectAST();
  ~FesProjectObjectAST();

  idk::StringViewChar _project_name = "";
  idk::i32 _default_window_size_w { 960_i32 };
  idk::i32 _default_window_size_h { 480_i32 };
  std::shared_ptr<FesColorObjectAST> _default_clear_color;
  idk::StringViewChar _default_fes_file = "";
  idk::Vector<std::shared_ptr<FesFileObjectAST>> _preloaded_fes_files;
};
}
}

#endif // FRESHENGINE_FES_AST_HPP
