// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fes/fes_tokenizer.hpp>
#include <fstream>
#include <string>
#include <log/log.hpp>

namespace fresh::fes {
FesTokenizer::FesTokenizer() noexcept
  : _i{0}, _is_string_data{false} {}

/// most of the time, fes scenes contains not that big data.
/// so memory mapped i/o might be a bit overkill here, so we will use normal
/// way. if you want to read files fast, use that your own one, then pass file
/// argument as false. fes will automatically initialize _raw_file_data variable
/// with ctx.
void FesTokenizer::load_from(const std::string& ctx, bool file) noexcept {
  this->_raw_file_data.clear();
  if(file) {
    std::ifstream file_stream(ctx);
    if(!file_stream) {
      log_error(src(), "cannot load file.");
      return;
    }
    for(std::string _temp; std::getline(file_stream, _temp);) {
      this->_raw_file_data.append(_temp + "\n");
    }
    return;
  }
  this->_raw_file_data = ctx;
}

void FesTokenizer::tokenize() noexcept {
  for(this->_i = 0; this->_i < this->_raw_file_data.length(); ++this->_i) {
    switch(this->_raw_file_data[this->_i]) {
      // only single line comments are allowed in fes.
      case '#': {
        if(this->_is_string_data) {
          this->_temp.push_back('#');
          break;
        }
        // skipping until next line.
        for(++this->_i;
           this->_raw_file_data.length() > this->_i && this->_raw_file_data[this->_i] != '\n';
           ++this->_i)
          ;
        // we decrease by 1 because for loop will increase it after scope ends.
        --this->_i;
        break;
      }
      // some escape sequences are allowed such as
      // \" (")
      // \\ (\)
      // \w ( )
      // \n (
      // )
      case '\\': {
        if(this->_is_string_data) {
          if(this->_i + 1 < this->_raw_file_data.length()) {
            ++this->_i;
            switch(this->_raw_file_data[this->_i]) {
              case '"':
              case '\\': {
                this->_temp.push_back(this->_raw_file_data[this->_i]);
                break;
              }
              case 'w': {
                this->_temp.push_back(' ');
                break;
              }
              case 'n': {
                this->_temp.push_back('\n');
                break;
              }
              default: {
                log_info(src(), "undefined escape character: '{}'", this->_raw_file_data[this->_i]);
                break;
              }
            }
          } else {
            log_error(src(), "EOF detected before string literal ends.");
            return;
          }
        } else {
          log_info(src(), "using escape characters out of string literal has no effect.");
        }
        break;
      }
      case '"': {
        if(this->_is_string_data) {
          this->_is_string_data = false;
          this->_tokens.emplace_back(this->_temp, Keywords::String);
          this->_temp.clear();
        } else {
          this->_is_string_data = true;
        }
        break;
      }
      case '[':
      case ']':
      case ',':
      case ';':
      case '{':
      case '}':
      case '=': {
        auto ch = std::string(1, this->_raw_file_data[this->_i]);
        this->_check_and_push();
        this->_tokens.emplace_back(ch, FesTokenizer::keywords[ch]);
        break;
      }
      case '\n': {
        if(this->_is_string_data) {
          this->_temp.push_back('\n');
        }
        break;
      }
      case ' ': {
        if(this->_is_string_data) {
          this->_temp.push_back(' ');
        }
        break;
      }
      default: {
        this->_temp.push_back(this->_raw_file_data[this->_i]);
        break;
      }
    }
  }
}

#define push(temp, as) \
  if(this->_temp == temp) { \
    this->_tokens.emplace_back(this->_temp, as); \
  }

#define pushe(temp, as) \
  else if(this->_temp == temp) { \
    this->_tokens.emplace_back(this->_temp, as); \
  }

#define pushelse() \
  else { \
    this->_tokens.emplace_back(this->_temp, Keywords::Data); \
  }

void FesTokenizer::_check_and_push() noexcept {
  if(this->_is_string_data) {
    this->_temp.push_back(this->_raw_file_data[this->_i]);
    return;
  }
  if(!this->_temp.empty()) {
    push("Color", Keywords::Color)
    pushe("File", Keywords::File)
    pushe("Project", Keywords::Project)
    pushe("Import", Keywords::Import)
    pushe("Vertex", Keywords::Vertex)
    pushe("AreaObject", Keywords::AreaObject)
    pushe("CircleAreaObject", Keywords::CircleAreaObject)
    pushe("PolygonAreaObject", Keywords::PolygonAreaObject)
    pushe("RectangleAreaObject", Keywords::RectangleAreaObject)
    pushe("BodyObject", Keywords::BodyObject)
    pushe("CircleBodyObject", Keywords::CircleBodyObject)
    pushe("PolygonBodyObject", Keywords::PolygonBodyObject)
    pushe("RectangleBodyObject", Keywords::RectangleBodyObject)
    pushe("WorldObject", Keywords::WorldObject)
    pushe("AudioPlayerObject", Keywords::AudioPlayerObject)
    pushe("BaseObject", Keywords::BaseObject)
    pushe("CircleObject", Keywords::CircleObject)
    pushe("PolygonObject", Keywords::PolygonObject)
    pushe("RectangleObject", Keywords::RectangleObject)
    pushe("CameraObject", Keywords::CameraObject)
    pushe("LabelObject", Keywords::LabelObject)
    pushe("SpriteObject", Keywords::SpriteObject)
    pushe("PointLightObject", Keywords::PointLightObject)
    pushe("sprite_resource", Keywords::SpriteResource)
    pushe("red", Keywords::Red)
    pushe("green", Keywords::Green)
    pushe("blue", Keywords::Blue)
    pushe("alpha", Keywords::Alpha)
    pushe("radius", Keywords::Radius)
    pushe("thickness", Keywords::Thickness)
    pushe("fg_color", Keywords::FgColor)
    pushe("bg_color", Keywords::BgColor)
    pushe("project_name", Keywords::ProjectName)
    pushe("default_window_size_w", Keywords::DefaultWindowSizeWidth)
    pushe("default_window_size_h", Keywords::DefaultWindowSizeHeight)
    pushe("default_fes_file", Keywords::DefaultFesFile)
    pushe("preloaded_fes_files", Keywords::PreloadedFesFiles)
    pushe("vertices", Keywords::Vertices)
    pushe("ambient", Keywords::Ambient)
    pushe("diffuse", Keywords::Diffuse)
    pushe("att_constant", Keywords::AttConstant)
    pushe("att_linear", Keywords::AttLinear)
    pushe("att_quadratic", Keywords::AttQuadratic)
    pushe("path", Keywords::Path)
    pushe("default_clear_color", Keywords::DefaultClearColor)
    pushe("label_text", Keywords::LabelText)
    pushe("font_size", Keywords::FontSize)
    pushe("font_resource", Keywords::FontResource)
    pushe("script_resource", Keywords::ScriptResource)
    pushe("label_object", Keywords::LabelObjectProperty)
    pushe("sprite_object", Keywords::SpriteObjectProperty)
    pushe("group_id", Keywords::GroupId)
    pushe("disabled", Keywords::Disabled)
    pushe("visible", Keywords::Visible)
    pushe("sub_groups", Keywords::SubGroups)
    pushe("width", Keywords::Width)
    pushe("height", Keywords::Height)
    pushe("name", Keywords::Name)
    pushe("position_x", Keywords::PositionX)
    pushe("position_y", Keywords::PositionY)
    pushe("true", Keywords::True)
    pushe("false", Keywords::False)
    pushe("auto", Keywords::Auto)
    pushelse()
    this->_temp.clear();
  }
}
#undef push
#undef pushe
#undef pushelse
} // namespace fresh::fes
