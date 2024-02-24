#include "../../include/fes/fes_parser.hpp"

#define accesstok(index) this->get_tokenizer()._tokens.at_without_check_reference(index)

inline bool is_valid_number(const idk::StringViewChar& data) {
  const char* p = data.data();
  if(!*p || *p == '?')
    return false;

  long long int s = 1;

  while(*p == ' ')
    p++;

  if(*p == '-') {
    s = -1;
    p++;
  }

  long double acc = 0;
  while(*p >= '0' && *p <= '9')
    acc = acc * 10 + *p++ - '0';

  if(*p == '.') {
    long double k = 0.1;
    p++;
    while(*p >= '0' && *p <= '9') {
      acc += (*p++ - '0') * k;
      k *= 0.1;
    }
  }

  if(*p)
    return false;

  return true;
}
inline long double return_num(const idk::StringViewChar& data) {
  const char* p = data.data();
  if(!*p || *p == '?' || *p == '"' || *p == '\'')
    return 0;

  long long int s = 1;

  while(*p == ' ')
    p++;

  if(*p == '-') {
    s = -1;
    p++;
  }

  long double acc = 0;
  while(*p >= '0' && *p <= '9')
    acc = acc * 10 + *p++ - '0';

  if(*p == '.') {
    long double k = 0.1;
    p++;
    while(*p >= '0' && *p <= '9') {
      acc += (*p++ - '0') * k;
      k *= 0.1;
    }
  }

  if(*p)
    return 0;

  return acc * s;
}

namespace fresh {
namespace fes {
FesParser::FesParser() {
  this->_objects = std::make_shared<FesObjectAST>();
}

FesParser::~FesParser() {
}

__idk_nodiscard
  FesTokenizer&
  FesParser::get_tokenizer() noexcept {
  return this->_tokenizer;
}

void FesParser::parse_variable(std::shared_ptr<FesObjectAST>& object_node) noexcept {
  // [aaa, x = y]
  if(auto _variable = accesstok(i); _variable._second != Keywords::Data) {
    ++i;

    if(accesstok(i)._second == Keywords::Assign) {
      ++i;

      auto _variable_data = accesstok(i);

      switch(_variable._second) {
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
        if(is_valid_number(_variable_data._first)) {
          auto _value = return_num(_variable_data._first);

          switch(_variable._second) {
          case Keywords::GroupId: {
            object_node->_group_id = static_cast<idk::usize>(_value);
            break;
          }

          case Keywords::Width: {
            object_node->_width = static_cast<idk::usize>(_value);
            break;
          }

          case Keywords::Height: {
            object_node->_height = static_cast<idk::usize>(_value);
            break;
          }

          case Keywords::PositionX: {
            object_node->_position_x = static_cast<idk::usize>(_value);
            break;
          }

          case Keywords::PositionY: {
            object_node->_position_y = static_cast<idk::usize>(_value);
            break;
          }

          case Keywords::FontSize: {
            if(object_node->_object_type == Keywords::SpriteObject)
              dynamic_cast<FesLabelObjectAST*>(object_node.get())->_font_size = static_cast<idk::u32>(_value);
            break;
          }

          case Keywords::Red:
          case Keywords::Green:
          case Keywords::Blue:
          case Keywords::Alpha: {
            if(object_node->_object_type == Keywords::Color) {
              switch(_variable._second) {
              case Keywords::Red: {
                dynamic_cast<FesColorObjectAST*>(object_node.get())->_red = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::Green: {
                dynamic_cast<FesColorObjectAST*>(object_node.get())->_green = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::Blue: {
                dynamic_cast<FesColorObjectAST*>(object_node.get())->_blue = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::Alpha: {
                dynamic_cast<FesColorObjectAST*>(object_node.get())->_alpha = static_cast<idk::u32>(_value);
                break;
              }
              default: {
                break;
              }// never reach
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
              switch(_variable._second) {
              case Keywords::BackgroundRed: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_bg_color->_red = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::BackgroundGreen: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_bg_color->_green = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::BackgroundBlue: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_bg_color->_blue = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::BackgroundAlpha: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_bg_color->_alpha = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::ForegroundRed: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_fg_color->_red = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::ForegroundGreen: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_fg_color->_green = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::ForegroundBlue: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_fg_color->_blue = static_cast<idk::u32>(_value);
                break;
              }
              case Keywords::ForegroundAlpha: {
                dynamic_cast<FesLabelObjectAST*>(object_node.get())->_fg_color->_alpha = static_cast<idk::u32>(_value);
                break;
              }
              default: {
                break;
              }// never reach
              }
            }
            break;
          }

          case Keywords::DefaultWindowSizeWidth:
          case Keywords::DefaultWindowSizeHeight: {
            if(object_node->_object_type == Keywords::Project) {
              if(_variable._second == Keywords::DefaultWindowSizeWidth) {
                dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_window_size_w = static_cast<idk::i32>(_value);
              } else {
                dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_window_size_h = static_cast<idk::i32>(_value);
              }
            }
            break;
          }
          }
        } else {
          switch(_variable._second) {
          case Keywords::GroupId: {
            if(_variable_data._second == Keywords::Auto)
              object_node->_group_id = -1;
            break;
          }

          default: {
            std::cout << "Engine error: Invalid property found in freshEngineScene file!\n";
            break;
          }
          }
        }

        break;
      }

      case Keywords::SpriteResource: {
        if(object_node->_object_type == Keywords::SpriteObject)
          dynamic_cast<FesSpriteObjectAST*>(object_node.get())->_sprite_path = _variable_data.first();

        break;
      }

      case Keywords::Name: {
        object_node->_name = _variable_data.first();
        break;
      }

      case Keywords::LabelText: {
        if(object_node->_object_type == Keywords::LabelObject)
          dynamic_cast<FesLabelObjectAST*>(object_node.get())->_label_text = _variable_data.first();
        break;
      }

      case Keywords::FontResource: {
        if(object_node->_object_type == Keywords::LabelObject)
          dynamic_cast<FesLabelObjectAST*>(object_node.get())->_label_path = _variable_data.first();
        break;
      }

      case Keywords::Visible:
      case Keywords::Disabled: {
        if(_variable.second() == Keywords::Visible)
          object_node->_visible = (_variable_data._second == Keywords::True);
        else
          object_node->_disabled = (_variable_data._second == Keywords::True);
        break;
      }

      case Keywords::ProjectName: {
        if(object_node->_object_type == Keywords::Project) {
          dynamic_cast<FesProjectObjectAST*>(object_node.get())->_project_name = _variable_data.first();
        }
        break;
      }

      case Keywords::DefaultFesFile: {
        if(object_node->_object_type == Keywords::Project) {
          dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_fes_file = _variable_data.first();
        }
        break;
      }

      case Keywords::Path: {
        if(object_node->_object_type == Keywords::File) {
          dynamic_cast<FesFileObjectAST*>(object_node.get())->_file_path = _variable_data.first();
        }
        break;
      }

      case Keywords::DefaultClearColor: {
        if(object_node->_object_type == Keywords::Project) {
          ++i;
          auto color_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(
            dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_clear_color);

          this->parse_list(color_object_ptr);

          if(color_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: DefaultClearColor, empty list detected. At least one member must be declared in that list.\n";
            return;
          }

          dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_clear_color =
            std::dynamic_pointer_cast<FesColorObjectAST>(color_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesProjectObjectAST*>(object_node.get())->_default_clear_color->_object_type = Keywords::Color;
        } else {
          std::cout << "Engine error: FesParser cannot handle DefaultClearColor for types that are not has member/s like that.\n";
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

      case Keywords::SpriteObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto sprite_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(
            dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_sprite_object);

          this->parse_list(sprite_object_ptr);

          if(sprite_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: SpriteObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            return;
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_sprite_object =
            std::dynamic_pointer_cast<FesSpriteObjectAST>(sprite_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_sprite_object->_object_type = Keywords::SpriteObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle SpriteObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::OnClickedSpriteObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto sprite_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(
            dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_sprite_object);

          this->parse_list(sprite_object_ptr);

          if(sprite_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: OnClickedSpriteObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            std::exit(1);
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_sprite_object =
            std::dynamic_pointer_cast<FesSpriteObjectAST>(sprite_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_sprite_object->_object_type = Keywords::SpriteObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle OnClickedSpriteObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::OnHoverSpriteObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto sprite_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(
            dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_sprite_object);

          this->parse_list(sprite_object_ptr);

          if(sprite_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: SpriteObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            std::exit(1);
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_sprite_object =
            std::dynamic_pointer_cast<FesSpriteObjectAST>(sprite_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_sprite_object->_object_type = Keywords::SpriteObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle SpriteObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::LabelObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto label_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_label_object);

          this->parse_list(label_object_ptr);

          if(label_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: LabelObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            std::exit(1);
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_label_object =
            std::dynamic_pointer_cast<FesLabelObjectAST>(label_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_label_object->_object_type = Keywords::LabelObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle LabelObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::OnClickedLabelObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto label_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_label_object);

          this->parse_list(label_object_ptr);

          if(label_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: OnClickedLabelObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            std::exit(1);
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_label_object =
            std::dynamic_pointer_cast<FesLabelObjectAST>(label_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_clicked_label_object->_object_type = Keywords::LabelObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle OnClickedLabelObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::OnHoverLabelObjectProperty: {
        if(object_node->_object_type == Keywords::GuiButtonObject) {
          ++i;
          auto label_object_ptr = std::dynamic_pointer_cast<FesObjectAST>(dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_label_object);

          this->parse_list(label_object_ptr);

          if(label_object_ptr->_sub_groups.is_empty()) {
            std::cout << "Engine error: OnHoverLabelObjectProperty, empty list detected. At least one member must be declared in that list.\n";
            std::exit(1);
          }

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_label_object =
            std::dynamic_pointer_cast<FesLabelObjectAST>(label_object_ptr->_sub_groups.at_without_check_reference(0));

          dynamic_cast<FesGuiButtonObjectAST*>(object_node.get())->_on_hover_label_object->_object_type = Keywords::LabelObject;
        } else {
          std::cout << "Engine error: FesParser cannot handle OnHoverLabelObjectProperty for types that are not has member/s like that.\n";
        }

        break;
      }

      case Keywords::SubGroups: {
        ++i;
        this->parse_list(object_node);
        break;
      }

      default: {
        std::cout << "Engine error: Invalid token : " << _variable_data._first << '\n';
        break;
      }
      }
    } else {
      std::cout << "Engine error: To assign data to variable use '=' symbol.\n";
    }
  } else {
    std::cout << "Engine error: Invalid variable name!\n";
  }
}

void FesParser::parse_list(std::shared_ptr<FesObjectAST>& object_node) noexcept {
  if(accesstok(i)._second == Keywords::ListObjectInit) {// {;}
    ++i;
    return;
  }

  while(accesstok(i)._second == Keywords::NodeInit) {
    ++i;
    switch(accesstok(i)._second) {
    case Keywords::Color: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using ColorObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesColorObjectAST())));
      break;
    }

    case Keywords::File: {
      if(object_node->_object_type == Keywords::Project) {
        std::dynamic_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.push_back(
          std::shared_ptr<FesFileObjectAST>(dynamic_cast<FesFileObjectAST*>(new FesFileObjectAST())));
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesFileObjectAST())));
      break;
    }

    case Keywords::Project: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using ProjectObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesProjectObjectAST())));
      break;
    }

    case Keywords::GuiButtonObject: {
      if(object_node->_object_type == Keywords::GuiButtonObject) {
        std::cout << "Fes error: Using ProjectObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesGuiButtonObjectAST())));
      break;
    }

    case Keywords::GuiBaseObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using GuiBaseObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesGuiBaseObjectAST())));
      break;
    }

    case Keywords::AreaObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using AreaObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesAreaObjectAST())));
      break;
    }

    case Keywords::BaseObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using BaseObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesObjectAST())));
      break;
    }

    case Keywords::CameraObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using CameraObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesCameraObjectAST())));
      break;
    }

    case Keywords::CollisionObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using CollisionObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesCollisionObjectAST())));
      break;
    }

    case Keywords::LabelObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using LabelObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesLabelObjectAST())));
      break;
    }

    case Keywords::SpriteObject: {
      if(object_node->_object_type == Keywords::Project) {
        std::cout << "Fes error: Using SpriteObject in ProjectObject within a list is not possible, no member can handle this.\n";
      } else
        object_node->_sub_groups.push_back(std::shared_ptr<FesObjectAST>(dynamic_cast<FesObjectAST*>(new FesSpriteObjectAST())));
      break;
    }
    }

    if(object_node->_object_type == Keywords::Project) {
      if(auto ptr = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(object_node); !ptr->_preloaded_fes_files.is_empty())
        this->parse_object(std::dynamic_pointer_cast<fes::FesProjectObjectAST>(object_node)->_preloaded_fes_files.back());
    } else {
      this->parse_object(object_node->_sub_groups.back());
    }

    ++i;

    if(accesstok(i)._second == Keywords::LastObject) {// {}; <-
      return;
    }
  }
}

// [asdasd, x = ..]
void FesParser::parse_object(std::shared_ptr<FesObjectAST> object_node) noexcept {
  if((accesstok(i)._second < Keywords::Int) && (accesstok(i)._second > Keywords::PositionY)) {
    object_node->_object_type = accesstok(i)._second;
    ++i;

    if(accesstok(i)._second == Keywords::NextObject) {
      while(true) {
        ++i;
        this->parse_variable(object_node);
        ++i;

        if(accesstok(i)._second == Keywords::LastObject) {
          ++i;
          break;
        }
      }
    } else if(accesstok(i)._second == Keywords::NodeEnd) {// [Object]
      ++i;
      return;
    }
  } else {
    std::cout << "Engine error: FesParser invalid Object type!\n";
  }
  ++i;
}

void FesParser::parse() noexcept {
  ++i;
  this->_objects = std::make_shared<fes::FesObjectAST>();
  this->parse_list(this->_objects);
}
}// namespace fes
}// namespace fresh