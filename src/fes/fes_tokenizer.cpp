#include "../../include/fes/fes_tokenizer.hpp"
#include <fstream>
#include <string>

namespace fresh {
namespace fes {
FesTokenizer::FesTokenizer() {
}

FesTokenizer::FesTokenizer(const idk::StringViewChar& fes_raw_text_data_or_file_path, bool file) {
  this->load_from(fes_raw_text_data_or_file_path, file);
}

FesTokenizer::FesTokenizer(idk::StringViewChar&& fes_raw_text_data_or_file_path, bool file) {
  this->load_from(idk::move(fes_raw_text_data_or_file_path));
}

FesTokenizer::~FesTokenizer() {
}

void FesTokenizer::load_from(const idk::StringViewChar& fes_raw_text_data_or_file_path, bool file) noexcept {
  this->_raw_file_data.clear();
  if(file) {
    std::ifstream file_stream(fes_raw_text_data_or_file_path.data());

    if(!file_stream) {
      std::cout << "Engine info: FesTokenizer cannot load file.\n";
      return;
    }

    for(std::string _temp; std::getline(file_stream, _temp);)
      this->_raw_file_data = this->_raw_file_data + idk::StringViewChar(const_cast<char*>(_temp.data())) + "\n";

    file_stream.close();
  } else {
    this->_raw_file_data = fes_raw_text_data_or_file_path;
  }
}

void FesTokenizer::load_from(idk::StringViewChar&& fes_raw_text_data_or_file_path, bool file) noexcept {
  this->_raw_file_data.clear();
  if(file) {
    std::ifstream file_stream(idk::move(fes_raw_text_data_or_file_path).data());

    if(!file_stream) {
      std::cout << "Engine info: FesTokenizer cannot load file.\n";
      return;
    }

    for(std::string _temp; std::getline(file_stream, _temp);)
      this->_raw_file_data = this->_raw_file_data + idk::StringViewChar(_temp.data()) + "\n";

    file_stream.close();
  } else {
    this->_raw_file_data = idk::move(fes_raw_text_data_or_file_path);
  }
}

void FesTokenizer::tokenize() noexcept {
  for(this->_i = 0; this->_i < this->_raw_file_data.length(); ++this->_i) {
    switch(this->_raw_file_data.at_without_check_reference(this->_i)) {
    case '#': {
      if(this->_is_string_data) {
        this->_temp.push_back('#');
        break;
      }

      for(++this->_i;
          (this->_raw_file_data.length() > this->_i) && (this->_raw_file_data.at_without_check_reference(this->_i) != '\n'); ++this->_i)
        ;// skipping until next line.

      --this->_i;
      break;
    }

    case '\\': {
      if(this->_is_string_data) {
        if(this->_i + 1 < this->_raw_file_data.length()) {
          ++this->_i;

          switch(this->_raw_file_data.at_without_check_reference(this->_i)) {
          case '"': {
            this->_temp.push_back('"');
            break;
          }

          case '\\': {
            this->_temp.push_back('\\');
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
            std::cout << "Engine info: Using undefined escape character has no effect.\n";
            break;
          }
          }
        } else {
          std::cout << "Engine error: freshEngineScene EOF detected before string ends!\n";
          return;
        }
      } else {
        std::cout << "Engine info: Using escape characters out of string initialization has no effect.\n";
      }
    }

    case '"': {
      if(this->_is_string_data) {
        this->_is_string_data = false;
        this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(this->_temp, Keywords::String));
        this->_temp.clear();
      } else {
        this->_is_string_data = true;
      }

      break;
    }

    case '[': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>("[", Keywords::NodeInit));
      break;
    }
    case ']': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>("]", Keywords::NodeEnd));
      break;
    }
    case ',': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(",", Keywords::NextObject));
      break;
    }
    case ';': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(";", Keywords::LastObject));
      break;
    }
    case '{': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>("{", Keywords::ListObjectInit));
      break;
    }
    case '}': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>("}", Keywords::ListObjectEnd));
      break;
    }
    case '=': {
      this->_check_and_push();
      this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>("=", Keywords::Assign));
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
      this->_temp.push_back(this->_raw_file_data.at_without_check_reference(this->_i));
      break;
    }
    }
  }
}

#define push(temp, as)    \
  if(this->_temp == temp) \
  this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(this->_temp, as))

#define pushe(temp, as) else if(this->_temp == temp) this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(this->_temp, as))

#define pushelse()                                                                                      \
  else {                                                                                                \
    this->_tokens.push_back(idk::MakePair<idk::StringViewChar, Keywords>(this->_temp, Keywords::Data)); \
  }

void FesTokenizer::_check_and_push() noexcept {
  if(this->_is_string_data) {
    this->_temp.push_back(this->_raw_file_data.at_without_check_reference(this->_i));
    return;
  }

  if(!this->_temp.is_empty()) {
    push("Color", Keywords::Color);
    pushe("File", Keywords::File);
    pushe("Project", Keywords::Project);
    pushe("Import", Keywords::Import);
    pushe("GuiButtonObject", Keywords::GuiButtonObject);
    pushe("GuiBaseObject", Keywords::GuiBaseObject);
    pushe("AreaObject", Keywords::AreaObject);
    pushe("BaseObject", Keywords::BaseObject);
    pushe("CameraObject", Keywords::CameraObject);
    pushe("CollisionObject", Keywords::CollisionObject);
    pushe("LabelObject", Keywords::LabelObject);
    pushe("SpriteObject", Keywords::SpriteObject);
    pushe("sprite_resource", Keywords::SpriteResource);
    pushe("background_red", Keywords::BackgroundRed);
    pushe("background_green", Keywords::BackgroundGreen);
    pushe("background_blue", Keywords::BackgroundBlue);
    pushe("background_alpha", Keywords::BackgroundAlpha);
    pushe("foreground_red", Keywords::ForegroundRed);
    pushe("foreground_green", Keywords::ForegroundGreen);
    pushe("foreground_blue", Keywords::ForegroundBlue);
    pushe("foreground_alpha", Keywords::ForegroundAlpha);
    pushe("red", Keywords::Red);
    pushe("green", Keywords::Green);
    pushe("blue", Keywords::Blue);
    pushe("alpha", Keywords::Alpha);
    pushe("project_name", Keywords::ProjectName);
    pushe("default_window_size_w", Keywords::DefaultWindowSizeWidth);
    pushe("default_window_size_h", Keywords::DefaultWindowSizeHeight);
    pushe("default_fes_file", Keywords::DefaultFesFile);
    pushe("preloaded_fes_files", Keywords::PreloadedFesFiles);
    pushe("path", Keywords::Path);
    pushe("default_clear_color", Keywords::DefaultClearColor);
    pushe("label_text", Keywords::LabelText);
    pushe("font_size", Keywords::FontSize);
    pushe("font_resource", Keywords::FontResource);
    pushe("script_resource", Keywords::ScriptResource);
    pushe("label_object", Keywords::LabelObjectProperty);
    pushe("sprite_object", Keywords::SpriteObjectProperty);
    pushe("on_clicked_sprite_object", Keywords::OnClickedSpriteObjectProperty);
    pushe("on_clicked_label_object", Keywords::OnClickedLabelObjectProperty);
    pushe("on_hover_sprite_object", Keywords::OnHoverSpriteObjectProperty);
    pushe("on_hover_label_object", Keywords::OnHoverLabelObjectProperty);
    pushe("group_id", Keywords::GroupId);
    pushe("disabled", Keywords::Disabled);
    pushe("visible", Keywords::Visible);
    pushe("sub_groups", Keywords::SubGroups);
    pushe("width", Keywords::Width);
    pushe("height", Keywords::Height);
    pushe("name", Keywords::Name);
    pushe("position_x", Keywords::PositionX);
    pushe("position_y", Keywords::PositionY);
    pushe("true", Keywords::True);
    pushe("false", Keywords::False);
    pushe("auto", Keywords::Auto);
    pushelse();
    this->_temp.clear();
  }
}
}// namespace fes
}// namespace fresh