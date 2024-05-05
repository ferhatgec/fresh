#include "../../include/resources/fes_loader_resource.hpp"
#include "../../include/freshengine.hpp"
#include <string>

// TODO: wrap scene name and resolution properties into BaseObject, so scene objects will not be pushed into Fes list;
// be pushed into sub_groups of this generated BaseObject's sub_groups.
namespace fresh {
idk::isize FesLoaderResource::_space_indentation{0_isize};

FesLoaderResource::FesLoaderResource() {
}

FesLoaderResource::~FesLoaderResource() {
}

__idk_nodiscard
fes::FesParser&
FesLoaderResource::get_fes_parser() noexcept {
  return this->_parser;
}

void FesLoaderResource::load_fes(const idk::StringViewChar& file_or_raw_text, bool file) noexcept {
  this->scene_fes_file_path = file_or_raw_text;
  this->_parser.get_tokenizer().load_from(this->scene_fes_file_path, file);
  this->_parser.get_tokenizer().tokenize();
  this->_parser.parse();
}

void FesLoaderResource::load_fes(idk::StringViewChar&& file_or_raw_text, bool file) noexcept {
  this->scene_fes_file_path = std::move(file_or_raw_text);
  this->_parser.get_tokenizer().load_from(this->scene_fes_file_path, file);
  this->_parser.get_tokenizer().tokenize();
  this->_parser.parse();
}

void FesLoaderResource::generate_objects() noexcept {
  this->_generate();
}

__idk_nodiscard
std::shared_ptr<BaseObject>
FesLoaderResource::return_generated_objects() noexcept {
  return std::move(this->_generate_with_return());
}

__idk_nodiscard
std::shared_ptr<BaseObject>
FesLoaderResource::_generate_object(std::shared_ptr<fes::FesObjectAST> object_node) noexcept {
  switch(object_node->_object_type) {
    case fes::Keywords::Import: {
      FesLoaderResource resource;
      resource.load_fes(std::dynamic_pointer_cast<fes::FesImportObjectAST>(object_node)->_import_path);
      auto obj = resource.return_generated_objects();
      obj->imported_from = std::dynamic_pointer_cast<fes::FesImportObjectAST>(object_node)->_import_path;
      // every .fes object must start with scene object (baseobject)
      // so, we wrap that baseobject into another baseobject's sub_groups. to verify that, we may check for
      // obj->_sub_objects.size() == 1. it always must be true if given conditions are passed.
      /*if(obj->_sub_objects.size() != 1) {
        std::cout << "Engine error: Given Import object found the scene file but that file does not start with BaseObject,"
                     "which contains name of scene, width and height parameters and child objects.\n";
        std::exit(1);
      }*/
      return std::move(obj);
    }

  case fes::Keywords::Color: {
    std::shared_ptr<fresh::EditorProjectColorObject> object = std::make_shared<fresh::EditorProjectColorObject>();
    auto casted_obj = std::dynamic_pointer_cast<fes::FesColorObjectAST>(object_node);

    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_object_def = "colorobject";
    object->_name = object_node->_name;

    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    object->_red = casted_obj->_red;
    object->_green = casted_obj->_green;
    object->_blue = casted_obj->_blue;
    object->_alpha = casted_obj->_alpha;

    return std::move(object);
  }

  case fes::Keywords::File: {
    std::shared_ptr<fresh::EditorProjectFileObject> object = std::make_shared<fresh::EditorProjectFileObject>();
    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_object_def = "fileobject";
    object->_name = object_node->_name;

    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    object->_file_path = std::dynamic_pointer_cast<fes::FesFileObjectAST>(object_node)->_file_path;

    return std::move(object);
  }

  case fes::Keywords::Project: {
    std::shared_ptr<fresh::EditorProjectObject> object = std::make_shared<fresh::EditorProjectObject>();
    auto casted_obj = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(object_node);

    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_object_def = "projectobject";
    object->_name = object_node->_name;

    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    object->_project_name = casted_obj->_project_name;
    object->_default_window_size_w = casted_obj->_default_window_size_w;
    object->_default_window_size_h = casted_obj->_default_window_size_h;

    if(casted_obj->_default_clear_color.get()) {
      object->_default_clear_color->_red = casted_obj->_default_clear_color->_red;
      object->_default_clear_color->_green = casted_obj->_default_clear_color->_green;
      object->_default_clear_color->_blue = casted_obj->_default_clear_color->_blue;
      object->_default_clear_color->_alpha = casted_obj->_default_clear_color->_alpha;
    }

    object->_default_fes_file = casted_obj->_default_fes_file;

    for(auto& preloaded_fes_file : casted_obj->_preloaded_fes_files) {
      object->_preloaded_fes_files.push_back(
        std::dynamic_pointer_cast<fresh::EditorProjectFileObject>(this->_generate_object(std::move(preloaded_fes_file)))
          );
    }

    return std::move(object);
  }

  case fes::Keywords::GuiButtonObject: {
    std::shared_ptr<fresh::GuiButtonObject> object = std::make_shared<fresh::GuiButtonObject>();
    auto casted_obj = std::dynamic_pointer_cast<fes::FesGuiButtonObjectAST>(object_node);

    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_object_def = "guibuttonobject";
    object->_name = object_node->_name;

    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    if(casted_obj->_sprite_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_sprite_object);

      object->get_sprite_object() = std::dynamic_pointer_cast<SpriteObject>(this->_generate_object(x));
    }

    if(casted_obj->_on_clicked_sprite_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_clicked_sprite_object);

      object->get_on_clicked_sprite_object() = std::dynamic_pointer_cast<SpriteObject>(this->_generate_object(x));
    }

    if(casted_obj->_on_hover_sprite_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_hover_sprite_object);

      object->get_on_hover_sprite_object() = std::dynamic_pointer_cast<SpriteObject>(this->_generate_object(x));
    }

    if(casted_obj->_label_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_label_object);

      object->get_label_object() = std::dynamic_pointer_cast<LabelObject>(this->_generate_object(x));
    }

    if(casted_obj->_on_clicked_label_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_clicked_label_object);

      object->get_on_clicked_label_object() = std::dynamic_pointer_cast<LabelObject>(this->_generate_object(x));
    }

    if(casted_obj->_on_hover_label_object.get()) {
      auto x = std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_hover_label_object);

      object->get_on_hover_label_object() = std::dynamic_pointer_cast<LabelObject>(this->_generate_object(x));
    }

    for(auto& node : object_node->_sub_groups) {
      object->push_object(std::move(this->_generate_object(node)));
    }

    return std::move(object);
  }

  case fes::Keywords::GuiBaseObject: {
    auto ptr = this->_generate_baseobject_ptr<fresh::GuiBaseObject>(std::move(object_node));
    ptr->_object_def = "guibaseobject";
    return ptr;
  }

  case fes::Keywords::AreaObject: {
    auto ptr = this->_generate_baseobject_ptr<fresh::AreaObject>(std::move(object_node));
    ptr->_object_def = "areaobject";
    return ptr;
  }

  case fes::Keywords::BaseObject: {
    auto ptr = this->_generate_baseobject_ptr<fresh::BaseObject>(std::move(object_node));
    ptr->_object_def = "baseobject";
    return ptr;
  }

  case fes::Keywords::CameraObject: {
    auto ptr = this->_generate_baseobject_ptr<fresh::CameraObject>(std::move(object_node));
    ptr->_object_def = "cameraobject";
    return ptr;
  }

  case fes::Keywords::CollisionObject: {
    auto ptr = this->_generate_baseobject_ptr<fresh::CollisionObject>(std::move(object_node));
    ptr->_object_def = "collisionobject";
    return ptr;
  }

  case fes::Keywords::LabelObject: {
    std::shared_ptr<fresh::LabelObject> object = std::make_shared<fresh::LabelObject>();
    auto casted_obj = std::dynamic_pointer_cast<fresh::fes::FesLabelObjectAST>(object_node);

    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_name = object_node->_name;
    object->_object_def = "labelobject";
    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    object->get_label_font_resource().load_font(casted_obj->_label_path);
    object->get_label_font_resource().get_font_size() = casted_obj->_font_size;

    object->_bg.r = casted_obj->_bg_color->_red;
    object->_bg.g = casted_obj->_bg_color->_green;
    object->_bg.b = casted_obj->_bg_color->_blue;
    object->_bg.a = casted_obj->_bg_color->_alpha;

    object->_fg.r = casted_obj->_fg_color->_red;
    object->_fg.g = casted_obj->_fg_color->_green;
    object->_fg.b = casted_obj->_fg_color->_blue;
    object->_fg.a = casted_obj->_fg_color->_alpha;

    object->initialize_text(casted_obj->_label_text,
                            object->_fg,
                            object->_bg,
                            fresh::LabelRenderType::Solid);

    for(auto& node : object_node->_sub_groups) {
      object->push_object(std::move(this->_generate_object(node)));
    }

    object->load_fescript_rt(casted_obj->_fescript_path, true);
    return std::move(object);
  } // change this

  case fes::Keywords::SpriteObject: {
    std::shared_ptr<fresh::SpriteObject> object = std::make_shared<fresh::SpriteObject>();

    object->get_position_info().x = object_node->_position_x;
    object->get_position_info().y = object_node->_position_y;
    object->get_position_info().w = object_node->_width;
    object->get_position_info().h = object_node->_height;
    object->_name = object_node->_name;
    object->_object_def = "spriteobject";
    object->_object_id = this->_object_ids;
    ++this->_object_ids;

    if(object->_name.is_empty()) {
      object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
    }

    object->_disabled = object_node->_disabled;
    object->_visible = object_node->_visible;

    object->_sprite_resource.load_resource(std::dynamic_pointer_cast<fresh::fes::FesSpriteObjectAST>(object_node)->_sprite_path);

    for(auto& node : object_node->_sub_groups) {
      auto _object = this->_generate_object(node);
      if((_object->_object_def == "projectobject") || (_object->_object_def == "fileobject") || (_object->_object_def == "colorobject")) {
        continue;
      }
      object->push_object(std::move(_object));
    }

    object->load_fescript_rt(object_node->_fescript_path, true);
    return std::move(object);
  }

  default: {
    std::cout << "Engine error: Undefined object type found in FesLoaderResource.\n";
    auto ptr = this->_generate_baseobject_ptr<fresh::BaseObject>(std::move(object_node));
    ptr->_object_def = "baseobject";
    return ptr;
  }
  }
}

void FesLoaderResource::_generate() noexcept {
  for(auto& node: this->_parser._objects->_sub_groups) {
    auto _object = this->_generate_object(node);

    if((_object->_object_def == "projectobject") ||
      (_object->_object_def == "fileobject") ||
      (_object->_object_def == "colorobject")) {
      continue;
    }

    /*if(_object->_object_def == "baseobject") {
      for(auto& render_object: _object->_sub_objects)
        RenderObjects::objects_to_render.push_back(render_object);
    }*/
    RenderObjects::objects_to_render.push_back(_object);
  }
}

__idk_nodiscard
std::shared_ptr<BaseObject>
FesLoaderResource::_generate_with_return() noexcept {
  std::shared_ptr<BaseObject> obj = std::make_shared<BaseObject>();
  if(this->_parser._objects->_sub_groups.size() != 1) {
    std::cout << "Engine error: Scene files must contain BaseObject, child objects must be inside of that BaseObject's sub_groups.\n";
    std::exit(1);
  }
  return std::move(this->_generate_object(this->_parser._objects->_sub_groups.front()));
}

template<typename ObjectClassType>
__idk_nodiscard
std::shared_ptr<BaseObject>
FesLoaderResource::_generate_baseobject_ptr(std::shared_ptr<fes::FesObjectAST> object_node) noexcept {
  std::shared_ptr<ObjectClassType> object = std::make_shared<ObjectClassType>();

  object->get_position_info().x = object_node->_position_x;
  object->get_position_info().y = object_node->_position_y;
  object->get_position_info().w = object_node->_width;
  object->get_position_info().h = object_node->_height;
  object->_name = object_node->_name;
  object->_object_id = this->_object_ids;
  ++this->_object_ids;

  if(object->_name.is_empty()) {
    object->_name = object->_object_def + idk::StringViewChar(std::to_string(object->_object_id).data());
  }

  object->_disabled = object_node->_disabled;
  object->_visible = object_node->_visible;

  for(auto& node : object_node->_sub_groups) {
    object->push_object(std::move(this->_generate_object(node)));
  }

  object->load_fescript_rt(object_node->_fescript_path, true);
  return std::move(object);
}

#define INDENT() fes_data.push_back(idk::StringViewChar(" ") * FesLoaderResource::_space_indentation)

__idk_nodiscard
idk::StringViewChar
FesLoaderResource::convert_into_fes() noexcept {
  return this->_convert_list(this->_parser._objects);
}

__idk_nodiscard
  idk::StringViewChar
  FesLoaderResource::_convert_list(std::shared_ptr<fes::FesObjectAST> list_node) noexcept {
  idk::StringViewChar fes_data;
  INDENT();
  fes_data.push_back("{\n");

  if(list_node->_sub_groups.is_empty()) {
    fes_data.pop_back();
    fes_data.push_back("};\n");
    return fes_data;
  } else {
    for(idk::usize i = 0; i < list_node->_sub_groups.size(); ++i) {
      ++FesLoaderResource::_space_indentation;
      fes_data.push_back(this->_convert_object(
        list_node->_sub_groups.at_without_check_reference(i)));

      if(i + 1 >= list_node->_sub_groups.size()) {
        fes_data.push_back(";\n");
      } else {
        fes_data.push_back(",\n");
      }
      --FesLoaderResource::_space_indentation;
    }
  }

  INDENT();
  fes_data.push_back("};\n");
  return fes_data;
}

__idk_nodiscard
  idk::StringViewChar
  FesLoaderResource::_convert_object(std::shared_ptr<fes::FesObjectAST> object_node) noexcept {
  idk::StringViewChar fes_data;
  INDENT();
  fes_data.push_back('[');

  switch(object_node->_object_type) {
    case fes::Keywords::Import: {
      auto casted_obj = std::dynamic_pointer_cast<fes::FesImportObjectAST>(object_node);
      fes_data.push_back("Import,\n");
      ++FesLoaderResource::_space_indentation;
      INDENT();
      fes_data.push_back("path = " + casted_obj->_import_path + ";\n");
      --FesLoaderResource::_space_indentation;
      break;
    }

  case fes::Keywords::Color: {
    auto casted_obj = std::dynamic_pointer_cast<fes::FesColorObjectAST>(object_node);
    fes_data.push_back("Color,\n");
    ++FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("red = " + idk::StringViewChar(std::to_string(casted_obj->_red).data()) + ",\n");
    INDENT();
    fes_data.push_back("green = " + idk::StringViewChar(std::to_string(casted_obj->_green).data()) + ",\n");
    INDENT();
    fes_data.push_back("blue = " + idk::StringViewChar(std::to_string(casted_obj->_blue).data()) + ",\n");
    INDENT();
    fes_data.push_back("alpha = " + idk::StringViewChar(std::to_string(casted_obj->_alpha).data()) + ";\n");
    --FesLoaderResource::_space_indentation;
    break;
  }

  case fes::Keywords::File: {
    auto casted_obj = std::dynamic_pointer_cast<fes::FesFileObjectAST>(object_node);
    fes_data.push_back("File,\n");
    ++FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("name = \"" + casted_obj->_name + "\",\n");
    INDENT();
    fes_data.push_back("path = \"" + casted_obj->_file_path + "\";\n");
    --FesLoaderResource::_space_indentation;
    break;
  }

  case fes::Keywords::Project: {
    auto casted_obj = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(object_node);

    fes_data.push_back("Project,\n");
    ++FesLoaderResource::_space_indentation;

    INDENT();
    fes_data.push_back("project_name = \"" + casted_obj->_project_name + "\",\n");
    INDENT();
    fes_data.push_back("default_window_size_w = " + idk::StringViewChar(std::to_string(casted_obj->_default_window_size_w).data()) + ",\n");
    INDENT();
    fes_data.push_back("default_window_size_h = " + idk::StringViewChar(std::to_string(casted_obj->_default_window_size_h).data()) + ",\n");
    INDENT();
    fes_data.push_back("default_clear_color = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_default_clear_color))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");
    INDENT();
    fes_data.push_back("default_fes_file = \"" + casted_obj->_default_fes_file + "\",\n");

    INDENT();
    fes_data.push_back("preloaded_fes_files = {\n");
    ++FesLoaderResource::_space_indentation;
    for(idk::isize i = 0; i < casted_obj->_preloaded_fes_files.size(); ++i) {
      fes_data.push_back(this->_convert_object(
        std::dynamic_pointer_cast<fes::FesObjectAST>(
          casted_obj->_preloaded_fes_files.at_without_check_reference(i))));

      if(i + 1 < casted_obj->_preloaded_fes_files.size()) {
        fes_data.push_back(",\n");
      } else {
        fes_data.push_back(";\n");
      }
    }

    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("};\n");
    break;
  }

  case fes::Keywords::GuiButtonObject: {
    auto casted_obj = std::dynamic_pointer_cast<fes::FesGuiButtonObjectAST>(object_node);

    fes_data.push_back("GuiButtonObject,\n");
    ++FesLoaderResource::_space_indentation;

    INDENT();
    fes_data.push_back("name = \"" + object_node->_name + "\",\n");
    INDENT();
    fes_data.push_back("group_id = " + ((object_node->_group_id == -1) ? "auto" : (idk::StringViewChar(std::to_string(object_node->_group_id).data()))) + ",\n");
    INDENT();
    fes_data.push_back("disabled = " + idk::StringViewChar(object_node->_disabled ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("visible = " + idk::StringViewChar(object_node->_visible ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("width = " + idk::StringViewChar(std::to_string(object_node->_width).data()) + ",\n");
    INDENT();
    fes_data.push_back("height = " + idk::StringViewChar(std::to_string(object_node->_height).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_x = " + idk::StringViewChar(std::to_string(object_node->_position_x).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_y = " + idk::StringViewChar(std::to_string(object_node->_position_y).data()) + ",\n");

    INDENT();
    fes_data.push_back("on_clicked_sprite_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_clicked_sprite_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");

    INDENT();
    fes_data.push_back("on_clicked_label_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_clicked_label_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");

    INDENT();
    fes_data.push_back("on_hover_sprite_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_hover_sprite_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");

    INDENT();
    fes_data.push_back("on_hover_label_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_on_hover_label_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");

    INDENT();
    fes_data.push_back("sprite_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_sprite_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");

    INDENT();
    fes_data.push_back("label_object = {\n");
    ++FesLoaderResource::_space_indentation;
    fes_data.push_back(this->_convert_object(
                         std::dynamic_pointer_cast<fes::FesObjectAST>(casted_obj->_label_object))
                       + ";\n");
    --FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("},\n");
    INDENT();
    fes_data.push_back("script_resource = \"" + casted_obj->_fescript_path + "\",\n");

    idk::StringViewChar sub_groups = this->_convert_list(object_node);
    sub_groups.trim_spaces_left();

    INDENT();
    fes_data.push_back("sub_groups = " + sub_groups);
    break;
  }

  case fes::Keywords::GuiBaseObject:
  case fes::Keywords::AreaObject:
  case fes::Keywords::BaseObject:
  case fes::Keywords::CameraObject:
  case fes::Keywords::CollisionObject: {
    fes_data.push_back([&]() -> idk::StringViewChar { switch(object_node->_object_type) { case fes::Keywords::GuiBaseObject: return "GuiBaseObject";
                                                                                                       case fes::Keywords::AreaObject: return "AreaObject";
                                                                                                       case fes::Keywords::BaseObject: return "BaseObject";
                                                                                                       case fes::Keywords::CameraObject: return "CameraObject";
                                                                                                       case fes::Keywords::CollisionObject: return "CollisionObject";
                                                                                                       default: return "BaseObject"; /* never reach*/ } }() + ",\n");
    ++FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("name = \"" + object_node->_name + "\",\n");
    INDENT();
    fes_data.push_back("group_id = " + ((object_node->_group_id == -1) ? "auto" : (idk::StringViewChar(std::to_string(object_node->_group_id).data()))) + ",\n");
    INDENT();
    fes_data.push_back("disabled = " + idk::StringViewChar(object_node->_disabled ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("visible = " + idk::StringViewChar(object_node->_visible ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("width = " + idk::StringViewChar(std::to_string(object_node->_width).data()) + ",\n");
    INDENT();
    fes_data.push_back("height = " + idk::StringViewChar(std::to_string(object_node->_height).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_x = " + idk::StringViewChar(std::to_string(object_node->_position_x).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_y = " + idk::StringViewChar(std::to_string(object_node->_position_y).data()) + ",\n");
    INDENT();
    fes_data.push_back("script_resource = \"" + object_node->_fescript_path + "\",\n");

    idk::StringViewChar sub_groups = this->_convert_list(object_node);
    sub_groups.trim_spaces_left();

    INDENT();
    fes_data.push_back("sub_groups = " + sub_groups);
    break;
  }

  case fes::Keywords::LabelObject: {
    fes_data.push_back("LabelObject,\n");
    ++FesLoaderResource::_space_indentation;
    auto casted_obj = std::move(std::dynamic_pointer_cast<fes::FesLabelObjectAST>(object_node));

    INDENT();
    fes_data.push_back("name = \"" + object_node->_name + "\",\n");
    INDENT();
    fes_data.push_back("group_id = " + ((object_node->_group_id == -1) ? "auto" : (idk::StringViewChar(std::to_string(object_node->_group_id).data()))) + ",\n");
    INDENT();
    fes_data.push_back("disabled = " + idk::StringViewChar(object_node->_disabled ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("visible = " + idk::StringViewChar(object_node->_visible ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("width = " + idk::StringViewChar(std::to_string(object_node->_width).data()) + ",\n");
    INDENT();
    fes_data.push_back("height = " + idk::StringViewChar(std::to_string(object_node->_height).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_x = " + idk::StringViewChar(std::to_string(object_node->_position_x).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_y = " + idk::StringViewChar(std::to_string(object_node->_position_y).data()) + ",\n");
    INDENT();
    fes_data.push_back("background_red = " + idk::StringViewChar(std::to_string(casted_obj->_bg_color->_red).data()) + ",\n");
    INDENT();
    fes_data.push_back("background_green = " + idk::StringViewChar(std::to_string(casted_obj->_bg_color->_green).data()) + ",\n");
    INDENT();
    fes_data.push_back("background_blue = " + idk::StringViewChar(std::to_string(casted_obj->_bg_color->_blue).data()) + ",\n");
    INDENT();
    fes_data.push_back("background_alpha = " + idk::StringViewChar(std::to_string(casted_obj->_bg_color->_alpha).data()) + ",\n");
    INDENT();
    fes_data.push_back("foreground_red = " + idk::StringViewChar(std::to_string(casted_obj->_fg_color->_red).data()) + ",\n");
    INDENT();
    fes_data.push_back("foreground_green = " + idk::StringViewChar(std::to_string(casted_obj->_fg_color->_green).data()) + ",\n");
    INDENT();
    fes_data.push_back("foreground_blue = " + idk::StringViewChar(std::to_string(casted_obj->_fg_color->_blue).data()) + ",\n");
    INDENT();
    fes_data.push_back("foreground_alpha = " + idk::StringViewChar(std::to_string(casted_obj->_fg_color->_alpha).data()) + ",\n");
    INDENT();
    fes_data.push_back("label_text = \"" + casted_obj->_label_text + "\",\n");
    INDENT();
    fes_data.push_back("font_size = " + idk::StringViewChar(std::to_string(casted_obj->_font_size).data()) + ",\n");
    INDENT();
    fes_data.push_back("font_resource = \"" + casted_obj->_label_path + "\",\n");
    INDENT();
    fes_data.push_back("script_resource = \"" + casted_obj->_fescript_path + "\",\n");

    idk::StringViewChar sub_groups = this->_convert_list(object_node);
    sub_groups.trim_spaces_left();

    INDENT();
    fes_data.push_back("sub_groups = " + sub_groups);
    break;
  }

  case fes::Keywords::SpriteObject: {
    fes_data.push_back("SpriteObject,\n");
    ++FesLoaderResource::_space_indentation;
    INDENT();
    fes_data.push_back("name = \"" + object_node->_name + "\",\n");
    INDENT();
    fes_data.push_back("group_id = " + ((object_node->_group_id == -1) ? "auto" : (idk::StringViewChar(std::to_string(object_node->_group_id).data()))) + ",\n");
    INDENT();
    fes_data.push_back("disabled = " + idk::StringViewChar(object_node->_disabled ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("visible = " + idk::StringViewChar(object_node->_visible ? "true,\n" : "false,\n"));
    INDENT();
    fes_data.push_back("width = " + idk::StringViewChar(std::to_string(object_node->_width).data()) + ",\n");
    INDENT();
    fes_data.push_back("height = " + idk::StringViewChar(std::to_string(object_node->_height).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_x = " + idk::StringViewChar(std::to_string(object_node->_position_x).data()) + ",\n");
    INDENT();
    fes_data.push_back("position_y = " + idk::StringViewChar(std::to_string(object_node->_position_y).data()) + ",\n");
    INDENT();
    fes_data.push_back("sprite_resource = \"" + std::dynamic_pointer_cast<fes::FesSpriteObjectAST>(object_node)->_sprite_path + "\",\n");
    INDENT();
    fes_data.push_back("script_resource = \"" + object_node->_fescript_path + "\",\n");

    idk::StringViewChar sub_groups = this->_convert_list(object_node);
    sub_groups.trim_spaces_left();

    INDENT();
    fes_data.push_back("sub_groups = " + sub_groups);
    break;
  }

  default: {
    std::cout << "Engine info: Invalid object type found."
                 "If directly some operations do applied into a node, please don't."
                 "freshEngine doing it automatically.\n";
    break;
  }
  }

  --FesLoaderResource::_space_indentation;
  INDENT();
  fes_data.push_back(']');

  return fes_data;
}

__idk_nodiscard
idk::StringViewChar
FesLoaderResource::_convert_render_objects() noexcept {
  std::shared_ptr<fes::FesObjectAST> render_object_list = std::make_shared<fes::FesObjectAST>();

  for(auto& obj: RenderObjects::objects_to_render) {
    render_object_list->_sub_groups.push_back(std::move(this->_convert_object_from_render_objects(obj)));
  }

  return this->_convert_list(render_object_list);
}

__idk_nodiscard
std::shared_ptr<fes::FesObjectAST>
FesLoaderResource::_convert_object_from_render_objects(std::shared_ptr<BaseObject> object_node) noexcept {
  if(!object_node->imported_from.is_empty()) {
    return std::move(this->_convert_object_from_base_object<fes::FesImportObjectAST>(
      object_node, [](std::shared_ptr<fes::FesImportObjectAST>& obj, const std::shared_ptr<BaseObject>& object_node) {
        obj->_import_path = object_node->imported_from;
      }));
  }
  if(object_node->_object_def == "guibaseobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesGuiBaseObjectAST>(object_node));
  } else if(object_node->_object_def == "guibuttonobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesGuiButtonObjectAST>(
        object_node,
        [this](std::shared_ptr<fes::FesGuiButtonObjectAST>& obj, const std::shared_ptr<BaseObject>& object_node){
        obj->_on_clicked_sprite_object =
          std::move(std::dynamic_pointer_cast<fes::FesSpriteObjectAST>(
            this->_convert_object_from_render_objects(
              std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_on_clicked_sprite_object()
            )));

        obj->_on_clicked_label_object =
          std::move(std::dynamic_pointer_cast<fes::FesLabelObjectAST>(
            this->_convert_object_from_render_objects(
              std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_on_clicked_label_object()
                )));

        obj->_on_hover_sprite_object =
          std::move(std::dynamic_pointer_cast<fes::FesSpriteObjectAST>(
            this->_convert_object_from_render_objects(
                std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_on_hover_sprite_object()
              )));

        obj->_on_hover_label_object =
          std::move(std::dynamic_pointer_cast<fes::FesLabelObjectAST>(
            this->_convert_object_from_render_objects(
                std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_on_hover_label_object()
              )));

        obj->_sprite_object =
          std::move(std::dynamic_pointer_cast<fes::FesSpriteObjectAST>(
            this->_convert_object_from_render_objects(
                std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_sprite_object()
              )));

        obj->_label_object =
          std::move(std::dynamic_pointer_cast<fes::FesLabelObjectAST>(
            this->_convert_object_from_render_objects(
                std::dynamic_pointer_cast<GuiButtonObject>(object_node)->get_label_object()
              )));
      }
      ));
  } else if(object_node->_object_def == "areaobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesAreaObjectAST>(object_node));
  } else if(object_node->_object_def == "cameraobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesCameraObjectAST>(object_node));
  } else if(object_node->_object_def == "collisionobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesCollisionObjectAST>(object_node));
  } else if(object_node->_object_def == "labelobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesLabelObjectAST>(
      object_node,
      [](std::shared_ptr<fes::FesLabelObjectAST>& obj, const std::shared_ptr<BaseObject>& object_node) {
          auto casted_obj = std::dynamic_pointer_cast<LabelObject>(object_node);
          obj->_bg_color->_red = casted_obj->_bg.r;
          obj->_bg_color->_green = casted_obj->_bg.g;
          obj->_bg_color->_blue = casted_obj->_bg.b;
          obj->_bg_color->_alpha = casted_obj->_bg.a;

          obj->_fg_color->_red = casted_obj->_fg.r;
          obj->_fg_color->_green = casted_obj->_fg.g;
          obj->_fg_color->_blue = casted_obj->_fg.b;
          obj->_fg_color->_alpha = casted_obj->_fg.a;

          obj->_label_text = casted_obj->_label_text;
          obj->_font_size = casted_obj->get_label_font_resource().get_font_size();
          obj->_label_path = casted_obj->get_label_font_resource().get_font_path();
        }
      ));
  } else if(object_node->_object_def == "spriteobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesSpriteObjectAST>(
             object_node,
             [](std::shared_ptr<fes::FesSpriteObjectAST>& obj, const std::shared_ptr<BaseObject>& object_node) {
                obj->_sprite_path = std::dynamic_pointer_cast<SpriteObject>(object_node)->get_sprite_resource()._texture_path;
             }
    ));
  } else if(object_node->_object_def == "baseobject") {
    return std::move(this->_convert_object_from_base_object<fes::FesGuiBaseObjectAST>(object_node));
  }
}

void
FesLoaderResource::_convert_base_object_properties(std::shared_ptr<fes::FesObjectAST> conv_obj,
                                                  const std::shared_ptr<BaseObject>& object_node) noexcept {
  conv_obj->_group_id = -1; // automatically assigns synced group id to object.
  conv_obj->_name = object_node->_name;
  conv_obj->_width = object_node->get_position_info().w;
  conv_obj->_height = object_node->get_position_info().h;
  conv_obj->_position_x = object_node->get_position_info().x;
  conv_obj->_position_y = object_node->get_position_info().y;
  conv_obj->_disabled = object_node->_disabled;
  conv_obj->_visible = object_node->_visible;
  conv_obj->_fescript_path = object_node->script_file_name;
  for(auto& sub_obj: object_node->_sub_objects) {
    conv_obj->_sub_groups.push_back(std::move(this->_convert_object_from_render_objects(sub_obj)));
  }
}
} // namespace fresh