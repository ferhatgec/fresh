#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../include/objects/base_object.hpp"
#include "../../include/fescript/fescript_scanner.hpp"
#include "../../include/fescript/fescript_parser.hpp"
#include "../../include/fescript/fescript_resolver.hpp"
#include "../../include/fescript/fescript_array.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/objects/camera_object.hpp"

namespace fresh {
bool is_first { false };
BaseObject::BaseObject() {
  this->_pos_info.x = 0;
  this->_pos_info.y = 0;
  this->_pos_info.w = 0;
  this->_pos_info.h = 0;
  this->_copy_last_pos_info.x = 0;
  this->_copy_last_pos_info.y = 0;
  this->_object_id = id::object_id;
  this->_object_def = "baseobject";
  this->script_content = "";
  this->script_file_name = "";
  ++id::object_id;
}

BaseObject::BaseObject(bool disabled, bool visible, idk::i32 pos_x, idk::i32 pos_y, idk::i32 width, idk::i32 height)
    : _disabled(disabled),
      _visible(visible) {
  this->_pos_info.x = pos_x;
  this->_pos_info.y = pos_y;
  this->_pos_info.w = width;
  this->_pos_info.h = height;
  this->_copy_last_pos_info.x = width;
  this->_copy_last_pos_info.y = height;
  this->_object_id = id::object_id;
  this->_object_def = "baseobject";
  this->script_content = "";
  this->script_file_name = "";
  ++id::object_id;
}

BaseObject::~BaseObject() {}

__idk_nodiscard bool&
BaseObject::get_is_disabled() noexcept {
  return this->_disabled;
}

__idk_nodiscard bool&
BaseObject::get_is_visible() noexcept {
  return this->_visible;
}

void BaseObject::set_disabled(bool disabled) noexcept {
  this->_disabled = disabled;
}

void BaseObject::set_visible(bool visible) noexcept {
  this->_visible = visible;
}

void BaseObject::sync() noexcept {
  this->get_position_info();
  this->_code.interpret_update();

  for(auto& object : this->_sub_objects) {
    if(object->_object_def != "cameraobject") // we actually sync cameraobject in engine::update()
      object->sync();
  }
}

__idk_nodiscard
SDL_FRect&
  BaseObject::get_position_info() noexcept {
  if(this->_block_transform) {
    this->_block_transform = false;
    if(this->delta_x() >= 0) {
      this->_pos_info.x += (this->delta_x() != 0) ? -1 : 0;
    } else {
      this->_pos_info.x += 1;
    }

    if(this->delta_y() >= 0) {
      this->_pos_info.y += (this->delta_y() != 0) ? -1 : 0;
    } else {
      this->_pos_info.y += 1;
    }

    for(auto& object : this->_sub_objects) {
      if(object) {
        object->get_position_info().x += this->delta_x();
        object->get_position_info().y += this->delta_y();
        // object->get_position_info().w += this->delta_w();
        // object->get_position_info().h += this->delta_h();
      }
    }

    return this->_blocked_pos_info;
  }

  for(auto& object : this->_sub_objects) {
    if(object) {
      object->get_position_info().x += this->delta_x();
      object->get_position_info().y += this->delta_y();
      // FIXME: height change of parent object generates delta_h > 0,
      //   * which shouldn't happen outside of editor.
      // object->get_position_info().w += this->delta_w();
      // object->get_position_info().h += this->delta_h();
    }
  }
  this->_copy_last_pos_info = this->_pos_info;
  return this->_pos_info;
}

__idk_nodiscard const idk::u64&
BaseObject::get_object_id() noexcept {
  return this->_object_id;
}

__idk_nodiscard
idk::f32
BaseObject::delta_x() noexcept {
  return this->_pos_info.x - this->_copy_last_pos_info.x;
}

__idk_nodiscard
idk::f32
BaseObject::delta_y() noexcept {
  return this->_pos_info.y - this->_copy_last_pos_info.y;
}

__idk_nodiscard
idk::f32
BaseObject::delta_w() noexcept {
  return this->_pos_info.w - this->_copy_last_pos_info.w;
}

__idk_nodiscard
idk::f32
BaseObject::delta_h() noexcept {
  return this->_pos_info.h - this->_copy_last_pos_info.h;
}

void BaseObject::push_object(std::shared_ptr<BaseObject> sub_object) noexcept {
  if(!sub_object.get()) {
    std::cout << "Engine warning: push_object argument contains an invalid pointer!\n";
    return;
  }

  this->push_to_sub_objects(sub_object);
  // this->_sub_objects.push_back(idk::move(sub_object));
}

[[nodiscard]] void BaseObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: BaseObject has not field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>&
  BaseObject::get_sub_objects() noexcept {
  return this->_sub_objects;
}

__idk_nodiscard
idk::StringViewChar&
BaseObject::get_name() noexcept {
  return this->_name;
}

__idk_nodiscard
void BaseObject::load_fescript_rt(const idk::StringViewChar& script, bool is_file) noexcept {
  if(script.is_empty())
    return;
  idk::StringViewChar script_content = "";
  if(is_file) {
    std::ifstream script_stream(script.data());
    for(std::string temp_str = ""; std::getline(script_stream, temp_str); script_content.push_back(temp_str.data()))
      script_content.push_back('\n');
    script_stream.close();
    this->script_file_name = script;
  } else
    script_content = script;
  
  this->script_content = script_content;

  fescript::Scanner scanner(script_content.data());
  std::vector<fescript::Token> tokens = scanner.scan_tokens();
  fescript::Parser parser(tokens);
  auto statements = parser.parse();
  if (fescript::had_error || fescript::had_runtime_error)
    return;
  fescript::Resolver resolver{this->_code};
  resolver.resolve(statements);
  if (fescript::had_error || fescript::had_runtime_error) {
    std::cout << "Engine error: Unable to handle runtime error.\n";
    std::exit(1);
  }
  this->_code.get_statements() = statements;
  this->_code.get_render_object_id() = this->_object_id;
  this->_code.get_parent_object() = shared_from_this();
  // we run interpreter first to calculate first values of variables.
  // it will prevent variable not found in scope style problems.
  this->_code.interpret(this->_code.get_statements());
  std::cout << this->_name << " " << this->script_file_name << '\n';
}

void BaseObject::push_to_sub_objects(std::shared_ptr<BaseObject> obj) noexcept {
  if(!obj) {
    std::cout << "Engine error: Invalid BaseObject/-inherited object passed to push_to_sub_objects()!\n";
    std::exit(1);
  }
  obj->_parent = shared_from_this();
  this->_sub_objects.push_back(obj);
}

__idk_nodiscard
std::shared_ptr<BaseObject>
BaseObject::get_object_by_path(const std::string& path) noexcept {
  std::shared_ptr<BaseObject> current = shared_from_this();
  for(const auto& entry: std::filesystem::path(path))
    current = this->_get_object_by_single_path(entry.string());
  return current;
}

__idk_nodiscard
std::shared_ptr<BaseObject>
BaseObject::_get_object_by_single_path(const std::string& path) noexcept {
  if(path == "." || path.empty())
    return shared_from_this();
  if(path == "..")
    return this->_parent;
  for(auto& sub_obj: this->_sub_objects) {
    if(sub_obj->_name == path.data()) {
      return sub_obj;
    }
  }
  std::cout << "Engine [language] error: Cannot find '" << path << "' in sub objects of" << this->_name << " object.\n";
  return shared_from_this();
}

/*
template<typename KeyType>
KeyType&
BaseObject::get_property() noexcept {
  std::cout << "Engine info: Override BaseObject<KeyType>::get_property() to access animation functionality.\n";
}*/
}// namespace fresh