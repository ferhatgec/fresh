// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

namespace fresh::fes {
enum Keywords {
  NodeInit, // [
  NodeEnd, // ]

  NextObject, // ,
  LastObject, // ;

  ListObjectInit, // {
  ListObjectEnd, // }
  Assign, // =

  Red, // red
  Green, // green
  Blue, // blue
  Alpha, // alpha
  Radius, // radius
  Thickness, // thickness
  FgColor, // fg_color
  BgColor, // bg_color

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

  GroupId, // group_id
  Disabled, // disabled
  Visible, // visible,
  SubGroups, // sub_groups
  Width, // width
  Height, // height,
  Name, // name
  PositionX, // position_x
  PositionY, // position_y
  Vertices, // vertices
  Ambient, // ambient
  Diffuse, // diffuse
  AttConstant, // att_constant
  AttLinear, // att_linear
  AttQuadratic, // att_quadratic

/// start of objects >
  Project, // Project
  Color, // Color
  File, // File
  Import, // Import
  Vertex, // Vertex

  AreaObject, // AreaObject
  CircleAreaObject, // CircleAreaObject
  PolygonAreaObject, // PolygonAreaObject
  RectangleAreaObject, // RectangleAreaObject

  // TODO >
  BodyObject, // BodyObject
  CircleBodyObject, // CircleBodyObject
  PolygonBodyObject, // PolygonBodyObject
  RectangleBodyObject, // RectangleBodyObject
  WorldObject, // WorldObject
  AudioPlayerObject, // AudioPlayerObject
  // < TODO
  PointLightObject, // PointLightObject

  BaseObject, // BaseObject
  CircleObject, // CircleObject
  PolygonObject, // PolygonObject
  RectangleObject, // RectangleObject

  CameraObject, // CameraObject
  LabelObject, // LabelObject
  SpriteObject, // SpriteObject
/// < end of objects
  Int,
  String,
  Bool,
  True,
  False,
  Auto, // auto

  Data,
  Undefined
};
} // namespace fresh::fes
