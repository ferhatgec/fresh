// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fes/fes_parser.hpp>
#include <log/log.hpp>

#define accesstok(index) this->get_tokenizer()._tokens[index]

namespace fresh::fes {
FesParser::FesParser() noexcept {
  this->_objects = std::make_shared<FesObjectAST>();
}

[[nodiscard]] FesTokenizer& FesParser::get_tokenizer() noexcept {
  return this->_tokenizer;
}

// parses only a single object:
// [ObjectName, Property = Value, XProperty = XValue, ...; ], ...
void FesParser::parse_variable(std::shared_ptr<FesObjectAST> object_node) noexcept {
  if(const auto& [kw_str, kw] = accesstok(i); kw != Data) {
    ++i;
    if(accesstok(i).second == Assign) {
      ++i;
      auto [var, var_kw] = accesstok(i);

      switch(kw) {
        /// these properties are convertible to floating point
        case GroupId:
        case Width:
        case Height:
        case PositionX:
        case PositionY:
        case Red:
        case Green:
        case Blue:
        case Alpha:
        case Radius:
        case Thickness:
        case DefaultWindowSizeWidth:
        case DefaultWindowSizeHeight:
        case FontSize: {
          const auto& val = _parse_floats<idk::f64>(var);
          if(val.index() == ConvertibleToFloat) {
            const auto& _value = std::get<ConvertibleToFloat>(val);
            switch(kw) {
              case GroupId:
                object_node->_group_id = static_cast<idk::usize>(_value);
                break;
              case Width:
                object_node->_size.set_w(static_cast<idk::f32>(_value));
                break;
              case Height:
                object_node->_size.set_h(static_cast<idk::f32>(_value));
                break;
              case PositionX: {
                if(object_node->get_type() == Vertex) {
                  const auto& vert = std::static_pointer_cast<fes::FesVertexAST>(object_node);
                  vert->get_resource_mutable().set_x(static_cast<idk::f32>(_value));
                } else {
                  object_node->_pos.set_x(static_cast<idk::f32>(_value));
                }
                break;
              }
              case PositionY: {
                if(object_node->get_type() == Vertex) {
                  const auto& vert = std::static_pointer_cast<fes::FesVertexAST>(object_node);
                  vert->get_resource_mutable().set_y(static_cast<idk::f32>(_value));
                } else {
                  object_node->_pos.set_y(static_cast<idk::f32>(_value));
                }
                break;
              }
              case FontSize:
                if(object_node->_object_type == SpriteObject)
                  std::static_pointer_cast<FesLabelObjectAST>(object_node)->_font_size = static_cast<idk::u32>(_value);
                break;
              case Red:
              case Green:
              case Blue:
              case Alpha: {
                if(object_node->_object_type == Color) {
                  const auto& color_object = std::static_pointer_cast<FesColorObjectAST>(object_node);
                  auto color = color_object->get_color();
                  switch(kw) {
                    case Red:
                      color.set_red(static_cast<idk::f32>(_value));
                      break;
                    case Green:
                      color.set_green(static_cast<idk::f32>(_value));
                      break;
                    case Blue:
                      color.set_blue(static_cast<idk::f32>(_value));
                      break;
                    case Alpha:
                      color.set_alpha(static_cast<idk::f32>(_value));
                      break;
                  }
                  color_object->set_color(color);
                } else {
                  log_warning(
                    src(),
                    "use red, green, blue and alpha properties inside a Color object: name is '{}'.",
                    object_node->get_name()
                  );
                }
                break;
              }
              case Radius: {
                if(object_node->get_type() == CircleObject) {
                  const auto& c_obj = std::static_pointer_cast<fes::FesCircleObjectAST>(object_node);
                  auto res = c_obj->get_resource();
                  res.set_radius(static_cast<idk::f32>(_value));
                  c_obj->set_resource(res);
                } else if(object_node->get_type() == CircleAreaObject) {
                  const auto& c_obj = std::static_pointer_cast<fes::FesCircleAreaObjectAST>(object_node);
                  auto res = c_obj->get_resource();
                  res.set_radius(static_cast<idk::f32>(_value));
                  c_obj->set_resource(res);
                }
                break;
              }
              case Thickness: {
                if(object_node->get_type() == CircleObject) {
                  const auto& c_obj = std::static_pointer_cast<fes::FesCircleObjectAST>(object_node);
                  auto res = c_obj->get_resource();
                  res.set_thickness(static_cast<idk::f32>(_value));
                  c_obj->set_resource(res);
                }
                break;
              }
              case DefaultWindowSizeWidth:
              case DefaultWindowSizeHeight: {
                if(object_node->_object_type == Project) {
                  const auto& project_object = std::static_pointer_cast<FesProjectObjectAST>(object_node);
                  if(kw == DefaultWindowSizeWidth) {
                    project_object->_default_size.set_w(static_cast<idk::f32>(_value));
                  } else {
                    project_object->_default_size.set_h(static_cast<idk::f32>(_value));
                  }
                }
                break;
              }
            }
          } else {
            switch(kw) {
              case GroupId: {
                if(var_kw == Auto) {
                  object_node->_group_id = -1;
                }
                break;
              }
              default: {
                log_error(src(), "invalid property: '{}'.", kw_str);
                break;
              }
            }
          }
          break;
        }
        case SpriteResource: {
          if(object_node->_object_type == SpriteObject) {
            std::static_pointer_cast<FesSpriteObjectAST>(object_node)->set_sprite_path(var);
          }
          break;
        }
        case Name: {
          object_node->set_name(var);
          break;
        }
        case LabelText: {
          if(object_node->_object_type == LabelObject) {
            std::static_pointer_cast<FesLabelObjectAST>(object_node)->set_label_text(var);
          }
          break;
        }
        case FontResource: {
          if(object_node->_object_type == LabelObject) {
            std::static_pointer_cast<FesLabelObjectAST>(object_node)->set_label_path(var);
          }
          break;
        }
        case ScriptResource: {
          object_node->set_fescript_path(var);
          break;
        }
        case Visible:
        case Disabled: {
          if(kw == Visible) {
            object_node->_visible = var_kw == True;
          } else {
            object_node->_disabled = var_kw == True;
          }
          break;
        }
        case ProjectName: {
          if(object_node->_object_type == Project) {
            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_project_name = var;
          }
          break;
        }
        case DefaultFesFile: {
          if(object_node->_object_type == Project) {
            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_fes_file = var;
          }
          break;
        }
        case Path: {
          if(object_node->_object_type == File) {
            std::static_pointer_cast<FesFileObjectAST>(object_node)->set_file_path(var);
          } else if(object_node->_object_type == Import) {
            std::static_pointer_cast<FesImportObjectAST>(object_node)->set_import_path(var);
          }
          break;
        }
        case DefaultClearColor: {
          if(object_node->_object_type == Project) {
            ++i;
            auto color_object_ptr = std::static_pointer_cast<FesObjectAST>(
              std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_clear_color);

            this->parse_list(color_object_ptr);

            if(color_object_ptr->_sub_groups.empty()) {
              log_error(src(), "default_clear_color: empty list detected; at least one member must have been declared.");
              return;
            }

            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_clear_color =
              std::static_pointer_cast<FesColorObjectAST>(color_object_ptr->_sub_groups.at(0));

            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_clear_color->_object_type = Color;
          } else {
            log_error(src(), "FesParser cannot handle default_clear_color for this object type.");
            return;
          }
          break;
        }
        case PreloadedFesFiles: {
          if(object_node->_object_type == Project) {
            ++i;
            this->parse_list(object_node);
          }
          break;
        }
        case Vertices: {
          if(object_node->get_type() == PolygonObject || object_node->get_type() == PolygonAreaObject) {
            ++i;
            auto ptr = std::make_shared<fes::FesObjectAST>();
            this->parse_list(ptr);

            // TODO: remove duplicate code
            if(object_node->get_type() == PolygonObject) {
              const auto& poly_ptr = std::static_pointer_cast<fes::FesPolygonObjectAST>(object_node);
              for(const auto& vert: ptr->get_sub_groups()) {
                if(vert->get_type() != Vertex) {
                  log_info(src(), "vertices keyword only takes list of Vertex.");
                  continue;
                }
                auto vert_ptr = std::static_pointer_cast<fes::FesVertexAST>(vert);
                poly_ptr->get_resource_mutable().push_back(std::move(vert_ptr));
              }
            } else if(object_node->get_type() == PolygonAreaObject) {
              const auto& poly_ptr = std::static_pointer_cast<fes::FesPolygonAreaObjectAST>(object_node);
              for(const auto& vert: ptr->get_sub_groups()) {
                if(vert->get_type() != Vertex) {
                  log_info(src(), "vertices keyword only takes list of Vertex.");
                  continue;
                }
                auto vert_ptr = std::static_pointer_cast<fes::FesVertexAST>(vert);
                poly_ptr->get_resource_mutable().push_back(std::move(vert_ptr));
              }
            }
          }
          break;
        }
        case FgColor: {
          ++i;
          auto ptr = std::make_shared<fes::FesObjectAST>();
          this->parse_list(ptr);
          if(ptr->get_sub_groups().size() != 1) {
            log_warning(src(), "fg_color expects only 1 Color object.");
            return;
          }
          if(ptr->get_sub_groups()[0]->get_type() != Color) {
            log_error(src(), "fg_color expects Color object in the list.");
            return;
          }
          const auto& color = std::static_pointer_cast<fes::FesColorObjectAST>(ptr->get_sub_groups()[0]);
          object_node->set_color(color->get_color());
          break;
        }
        case BgColor: {
          if(object_node->get_type() != LabelObject) {
            log_error(src(), "bg_color expects to be constructed within LabelObject.");
            return;
          }
          ++i;
          auto ptr = std::make_shared<fes::FesObjectAST>();
          this->parse_list(ptr);
          if(ptr->get_sub_groups().size() != 1) {
            log_warning(src(), "bg_color expects only 1 Color object.");
            return;
          }
          if(ptr->get_sub_groups()[0]->get_type() != Color) {
            log_error(src(), "fg_color expects Color object in the list.");
            return;
          }
          const auto& label_obj = std::static_pointer_cast<fes::FesLabelObjectAST>(object_node);
          auto color = std::static_pointer_cast<fes::FesColorObjectAST>(ptr->get_sub_groups()[0]);
          label_obj->get_bg_color() = std::move(color);
          break;
        }
        case SubGroups: {
          ++i;
          this->parse_list(object_node);
          break;
        }
        default: {
          log_error(src(), "invalid token: '{}'", var);
          break;
        }
      }
    } else { // accesstok(i).second != Assign
      log_error(src(), "to assign a property to object; use '=' operator, not this: '{}'", accesstok(i).first);
    }
  } else { // accesstok(i).second == Data
    log_error(src(), "invalid property name: '{}'.", kw_str);
  }
}

void FesParser::parse_list(std::shared_ptr<FesObjectAST> object_node) noexcept {
  if(accesstok(i).second == ListObjectInit) {// {;}
    ++i;
    return;
  }

  while(accesstok(i).second == NodeInit) {
    ++i;
    if(object_node->_object_type == Project
        && accesstok(i).second != File) {
      check_project_object(
          object_node->_object_type,
          "cannot use other than File property in ProjectObject."
        );
      return;
    }
    switch(accesstok(i).second) {
      case Color: {
        object_node->_sub_groups.push_back(std::make_shared<FesColorObjectAST>());
        break;
      }
      case File: {
        if(object_node->_object_type == Project) {
          std::static_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.push_back(std::make_shared<FesFileObjectAST>());
        } else {
          object_node->_sub_groups.push_back(std::make_shared<FesFileObjectAST>());
        }
        break;
      }
      case Project:
        object_node->_sub_groups.push_back(std::make_shared<FesProjectObjectAST>());
        break;
      case Import:
        object_node->_sub_groups.push_back(std::make_shared<FesImportObjectAST>());
        break;
      case Vertex:
        object_node->_sub_groups.push_back(std::make_shared<FesVertexAST>());
        break;
      case AreaObject:
        object_node->_sub_groups.push_back(std::make_shared<FesAreaObjectAST>());
        break;
      case CircleAreaObject:
        object_node->_sub_groups.push_back(std::make_shared<FesCircleAreaObjectAST>());
        break;
      case PolygonAreaObject:
        object_node->_sub_groups.push_back(std::make_shared<FesPolygonAreaObjectAST>());
        break;
      case RectangleAreaObject:
        object_node->_sub_groups.push_back(std::make_shared<FesRectangleAreaObject>());
        break;
      case BaseObject:
        object_node->_sub_groups.push_back(std::make_shared<FesObjectAST>());
        break;
      case CircleObject:
        object_node->_sub_groups.push_back(std::make_shared<FesCircleObjectAST>());
        break;
      case PolygonObject:
        object_node->_sub_groups.push_back(std::make_shared<FesPolygonObjectAST>());
        break;
      case RectangleObject:
        object_node->_sub_groups.push_back(std::make_shared<FesRectangleObjectAST>());
        break;
      case CameraObject:
        object_node->_sub_groups.push_back(std::make_shared<FesCameraObjectAST>());
        break;
      case LabelObject:
        object_node->_sub_groups.push_back(std::make_shared<FesLabelObjectAST>());
        break;
      case SpriteObject: {
        object_node->_sub_groups.push_back(std::make_shared<FesSpriteObjectAST>());
        break;
      }
    }

    if(object_node->_object_type == Project) {
      if(const auto& ptr = std::static_pointer_cast<fes::FesProjectObjectAST>(object_node); !ptr->_preloaded_fes_files.empty()) {
        this->parse_object(std::static_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.back());
      }
    } else {
      this->parse_object(object_node->_sub_groups.back());
    }

    ++i;
    if(accesstok(i).second == LastObject) {// {}; <-
      return;
    }
  }
}

void FesParser::parse_object(std::shared_ptr<FesObjectAST> object_node) noexcept {
  // between Vertices and Int; we have a range where all object enumerations are
  // defined.
  if(accesstok(i).second < Int && accesstok(i).second > Vertices) {
    object_node->_object_type = accesstok(i).second;
    ++i;

    if(accesstok(i).second == NextObject) {
      while(true) {
        ++i;
        this->parse_variable(object_node);
        ++i;

        if(accesstok(i).second == LastObject) {
          ++i;
          break;
        }
      }
    } else if(accesstok(i).second == NodeEnd) {// [Object]
      ++i;
      return;
    }
  } else {
    log_error(src(), "invalid object type: '{}'", accesstok(i).first);
    return;
  }
  ++i;
}

void FesParser::parse() noexcept {
  ++i;
  this->_objects = std::make_shared<fes::FesObjectAST>();
  this->parse_object(this->_objects);
}

void FesParser::check_project_object(const Keywords& kw, std::string_view msg) noexcept {
  if(kw == Project) {
    log_error(src(), msg);
  }
}
} // namespace fresh::fes
#undef accesstok