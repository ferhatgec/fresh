#include <fes/fes_parser.hpp>
#include "log/log.hpp"

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
  if(const auto& [kw_str, kw] = accesstok(i); kw != Keywords::Data) {
    ++i;
    if(accesstok(i).second == Keywords::Assign) {
      ++i;
      auto [var, var_kw] = accesstok(i);

      switch(kw) {
        /// these properties are convertible to floating point
        case Keywords::GroupId:
        case Keywords::Width:
        case Keywords::Height:
        case Keywords::PositionX:
        case Keywords::PositionY:
        case Keywords::Red:
        case Keywords::Green:
        case Keywords::Blue:
        case Keywords::Alpha:
        case Keywords::BackgroundRed:
        case Keywords::BackgroundGreen:
        case Keywords::BackgroundBlue:
        case Keywords::BackgroundAlpha:
        case Keywords::ForegroundRed:
        case Keywords::ForegroundGreen:
        case Keywords::ForegroundBlue:
        case Keywords::ForegroundAlpha:
        case Keywords::DefaultWindowSizeWidth:
        case Keywords::DefaultWindowSizeHeight:
        case Keywords::FontSize: {
          const auto& val = FesParser::_parse_floats<idk::f64>(var);
          if(val.index() == ConvertibleToFloat) {
            const auto& _value = std::get<ConvertibleToFloat>(val);
            switch(kw) {
              case Keywords::GroupId: {
                object_node->_group_id = static_cast<idk::usize>(_value);
                break;
              }
              case Keywords::Width: {
                object_node->_size.set_w(static_cast<idk::f32>(_value));
                break;
              }
              case Keywords::Height: {
                object_node->_size.set_h(static_cast<idk::f32>(_value));
                break;
              }
              case Keywords::PositionX: {
                object_node->_pos.set_x(static_cast<idk::f32>(_value));
                break;
              }
              case Keywords::PositionY: {
                object_node->_pos.set_y(static_cast<idk::f32>(_value));
                break;
              }
              case Keywords::FontSize: {
                if(object_node->_object_type == Keywords::SpriteObject)
                  std::static_pointer_cast<FesLabelObjectAST>(object_node)->_font_size = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::Red:
              case Keywords::Green:
              case Keywords::Blue:
              case Keywords::Alpha: {
                if(object_node->_object_type == Keywords::Color) {
                  const auto& color_object = std::static_pointer_cast<FesColorObjectAST>(object_node);
                  switch(kw) {
                    case Keywords::Red: {
                      color_object->_color.set_red(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::Green: {
                      color_object->_color.set_green(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::Blue: {
                      color_object->_color.set_blue(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::Alpha: {
                      color_object->_color.set_alpha(static_cast<idk::f32>(_value));
                      break;
                    }
                  }
                }
                break;
              }
              case Keywords::BackgroundRed:
              case Keywords::BackgroundGreen:
              case Keywords::BackgroundBlue:
              case Keywords::BackgroundAlpha:
              case Keywords::ForegroundRed:
              case Keywords::ForegroundGreen:
              case Keywords::ForegroundBlue:
              case Keywords::ForegroundAlpha: {
                if(object_node->_object_type == Keywords::LabelObject) {
                  const auto& label_object = std::static_pointer_cast<FesLabelObjectAST>(object_node);
                  switch(kw) {
                    case Keywords::BackgroundRed: {
                      label_object->_bg->_color.set_red(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::BackgroundGreen: {
                      label_object->_bg->_color.set_green(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::BackgroundBlue: {
                      label_object->_bg->_color.set_blue(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::BackgroundAlpha: {
                      label_object->_bg->_color.set_alpha(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::ForegroundRed: {
                      label_object->_fg->_color.set_red(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::ForegroundGreen: {
                      label_object->_fg->_color.set_green(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::ForegroundBlue: {
                      label_object->_fg->_color.set_blue(static_cast<idk::f32>(_value));
                      break;
                    }
                    case Keywords::ForegroundAlpha: {
                      label_object->_fg->_color.set_alpha(static_cast<idk::f32>(_value));
                      break;
                    }
                  }
                }
                break;
              }
              case Keywords::DefaultWindowSizeWidth:
              case Keywords::DefaultWindowSizeHeight: {
                if(object_node->_object_type == Keywords::Project) {
                  const auto& project_object = std::static_pointer_cast<FesProjectObjectAST>(object_node);
                  if(kw == Keywords::DefaultWindowSizeWidth) {
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
              case Keywords::GroupId: {
                if(var_kw == Keywords::Auto) {
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
        case Keywords::SpriteResource: {
          if(object_node->_object_type == Keywords::SpriteObject) {
            std::static_pointer_cast<FesSpriteObjectAST>(object_node)->set_sprite_path(var);
          }
          break;
        }
        case Keywords::Name: {
          object_node->set_name(var);
          break;
        }
        case Keywords::LabelText: {
          if(object_node->_object_type == Keywords::LabelObject) {
            std::static_pointer_cast<FesLabelObjectAST>(object_node)->set_label_text(var);
          }
          break;
        }
        case Keywords::FontResource: {
          if(object_node->_object_type == Keywords::LabelObject) {
            std::static_pointer_cast<FesLabelObjectAST>(object_node)->set_label_path(var);
          }
          break;
        }
        case Keywords::ScriptResource: {
          object_node->set_fescript_path(var);
          break;
        }
        case Keywords::Visible:
        case Keywords::Disabled: {
          if(kw == Keywords::Visible) {
            object_node->_visible = var_kw == Keywords::True;
          } else {
            object_node->_disabled = var_kw == Keywords::True;
          }
          break;
        }
        case Keywords::ProjectName: {
          if(object_node->_object_type == Keywords::Project) {
            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_project_name = var;
          }
          break;
        }
        case Keywords::DefaultFesFile: {
          if(object_node->_object_type == Keywords::Project) {
            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_fes_file = var;
          }
          break;
        }
        case Keywords::Path: {
          if(object_node->_object_type == Keywords::File) {
            std::static_pointer_cast<FesFileObjectAST>(object_node)->set_file_path(var);
          } else if(object_node->_object_type == Keywords::Import) {
            std::static_pointer_cast<FesImportObjectAST>(object_node)->set_import_path(var);
          }
          break;
        }
        case Keywords::DefaultClearColor: {
          if(object_node->_object_type == Keywords::Project) {
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

            std::static_pointer_cast<FesProjectObjectAST>(object_node)->_default_clear_color->_object_type = Keywords::Color;
          } else {
            log_error(src(), "FesParser cannot handle default_clear_color for this object type.");
            return;
          }
          break;
        }
        case Keywords::PreloadedFesFiles: {
          if(object_node->_object_type == Keywords::Project) {
            ++i;
            this->parse_list(object_node);
          }
          break;
        }
        case Keywords::SubGroups: {
          ++i;
          this->parse_list(object_node);
          break;
        }
        default: {
          log_error(src(), "invalid token: '{}'", var);
          break;
        }
      }
    } else { // accesstok(i).second != Keywords::Assign
      log_error(src(), "to assign a property to object; use '=' operator, not this: '{}'", accesstok(i).first);
    }
  } else { // accesstok(i).second == Keywords::Data
    log_error(src(), "invalid property name: '{}'.", kw_str);
  }
}

void FesParser::parse_list(std::shared_ptr<FesObjectAST> object_node) noexcept {
  if(accesstok(i).second == Keywords::ListObjectInit) {// {;}
    ++i;
    return;
  }

  while(accesstok(i).second == Keywords::NodeInit) {
    ++i;
    switch(accesstok(i).second) {
      case Keywords::Color: {
        check_project_object(
          object_node->_object_type,
          "cannot use ColorObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesColorObjectAST>());
        break;
      }
      case Keywords::File: {
        if(object_node->_object_type == Keywords::Project) {
          std::static_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.push_back(std::make_shared<FesFileObjectAST>());
        } else {
          object_node->_sub_groups.push_back(std::make_shared<FesFileObjectAST>());
        }
        break;
      }
      case Keywords::Project: {
        check_project_object(
          object_node->_object_type,
          "using ProjectObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesProjectObjectAST>());
        break;
      }
      case Keywords::Import: {
        check_project_object(
          object_node->_object_type,
          "using Import in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesImportObjectAST>());
        break;
      }
      case Keywords::AreaObject: {
        check_project_object(
          object_node->_object_type,
          "using AreaObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesAreaObjectAST>());
        break;
      }
      case Keywords::BaseObject: {
        check_project_object(
          object_node->_object_type,
          "using BaseObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesObjectAST>());
        break;
      }
      case Keywords::CameraObject: {
        check_project_object(
          object_node->_object_type,
          "using CameraObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesCameraObjectAST>());
        break;
      }
      case Keywords::LabelObject: {
        check_project_object(
          object_node->_object_type,
          "using LabelObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesLabelObjectAST>());
        break;
      }
      case Keywords::SpriteObject: {
        check_project_object(
          object_node->_object_type,
          "using SpriteObject in ProjectObject inside a list is not possible."
        );
        object_node->_sub_groups.push_back(std::make_shared<FesSpriteObjectAST>());
        break;
      }
    }

    if(object_node->_object_type == Keywords::Project) {
      if(auto ptr = std::static_pointer_cast<fes::FesProjectObjectAST>(object_node); !ptr->_preloaded_fes_files.empty()) {
        this->parse_object(std::static_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.back());
      }
    } else {
      this->parse_object(object_node->_sub_groups.back());
    }

    ++i;
    if(accesstok(i).second == Keywords::LastObject) {// {}; <-
      return;
    }
  }
}

void FesParser::parse_object(std::shared_ptr<FesObjectAST> object_node) noexcept {
  // between Keywords::PositionY and Keywords::Int; we have a range where all
  // object enumerations are defined.
  if(accesstok(i).second < Keywords::Int && accesstok(i).second > Keywords::PositionY) {
    object_node->_object_type = accesstok(i).second;
    ++i;

    if(accesstok(i).second == Keywords::NextObject) {
      while(true) {
        ++i;
        this->parse_variable(object_node);
        ++i;

        if(accesstok(i).second == Keywords::LastObject) {
          ++i;
          break;
        }
      }
    } else if(accesstok(i).second == Keywords::NodeEnd) {// [Object]
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
  if(kw == Keywords::Project) {
    log_error(src(), msg);
  }
}
} // namespace fresh::fes
#undef accesstok