//
// Created by gech on 2/5/2024.
//

#ifndef FRESHENGINE_FES_KEYWORDS_HPP
#define FRESHENGINE_FES_KEYWORDS_HPP

namespace fresh {
namespace fes {
enum Keywords {
  NodeInit, // [
  NodeEnd, // ]

  NextObject, // ,
  LastObject, // ;

  ListObjectInit, // {
  ListObjectEnd, // }
                  // =
  Assign,

  BackgroundRed, // background_red
  BackgroundGreen, // background_green
  BackgroundBlue, // background_blue
  BackgroundAlpha, // background_alpha
  ForegroundRed, // foreground_red
  ForegroundGreen, // foreground_green
  ForegroundBlue, // foreground_blue
  ForegroundAlpha, // foreground_alpha

  Red, // red
  Green, // green
  Blue, // blue
  Alpha, // alpha

  ProjectName, // project_name
  DefaultWindowSizeWidth, // default_window_size_w
  DefaultWindowSizeHeight, // default_window_size_h
  DefaultFesFile, // default_fes_file
  PreloadedFesFiles, // preloaded_fes_files
  Path, // path

  DefaultClearColor, // default_clear_color

  LabelText, // label_text
  FontSize, // font_size
  FontResource, // font_resource
  SpriteResource, // sprite_resource
  ScriptResource, // script_resource
  LabelObjectProperty, // label_object
  SpriteObjectProperty, // sprite_object

  OnClickedSpriteObjectProperty, // on_clicked_sprite_object
  OnClickedLabelObjectProperty, // on_clicked_label_object

  OnHoverSpriteObjectProperty, // on_hover_sprite_object
  OnHoverLabelObjectProperty, // on_hover_label_object

  GroupId, // group_id
  Disabled, // disabled
  Visible, // visible,
  SubGroups, // sub_groups
  Width, // width
  Height, // height,
  Name, // name
  PositionX, // position_x
  PositionY, // position_y

  Project, // Project
  Color, // Color
  File, // File

  GuiButtonObject, // GuiButtonObject
  GuiBaseObject, // GuiBaseObject
  AreaObject, // AreaObject
  BaseObject, // BaseObject
  CameraObject, // CameraObject
  CollisionObject, // CollisionObject
  LabelObject, // LabelObject
  SpriteObject, // SpriteObject

  Int,
  String,
  Bool,
  True,
  False,
  Auto, // auto

  Data,
  Undefined
};

enum class LabelRenderType {
  LCD,
  Solid,
  Shaded,
  Blended
};
}
}

#endif // FRESHENGINE_FES_KEYWORDS_HPP
