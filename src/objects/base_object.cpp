// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <objects/base_object.hpp>
#include <objects/camera_object.hpp>

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_scanner.hpp>
#include <fescript/fescript_parser.hpp>
#include <fescript/fescript_resolver.hpp>
#include <fescript/fescript_array.hpp>

#include <freshengine.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numbers>

#include "log/log.hpp"

namespace fresh {
static inline int i = 0;

BaseObject::BaseObject()
  : _disabled{false}, _visible{true} {
  this->_pos_info = BBoxResource { 0.f, 0.f, 0.f, 0.f };
  this->_rotation_degrees = this->_last_rotation_degrees = 0.f;
  this->_copy_last_pos_info = this->_pos_info;
  this->_object_id = FreshInstance->get_id();
  this->script_content = "";
  this->script_file_name = "";
  this->_initialized = false;
  FreshInstance->increase_global_id();
}

[[nodiscard]] const bool& BaseObject::get_disabled() const noexcept {
  return this->_disabled;
}

[[nodiscard]] const bool& BaseObject::get_visible() const noexcept {
  return this->_visible;
}

[[nodiscard]] const bool& BaseObject::get_initialized() const noexcept {
  return this->_initialized;
}

void BaseObject::set_disabled(bool disabled) noexcept {
  this->_disabled = disabled;
}

void BaseObject::set_visible(bool visible) noexcept {
  this->_visible = visible;
}

void BaseObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes();
}

void BaseObject::apply_changes() noexcept {
  for (const auto& object: this->_sub_objects) {
    if(!object) {
      log_error(src(), "invalid object.");
      return;
    }
    if(this->get_delta() != 0.f) {
      object->set_position(object->get_position() + this->get_delta());
    }
    if(!fre2d::detail::nearly_equals(this->get_delta_rot(), 0.f)) {
      object->set_rotation(object->get_rotation() + this->get_delta_rot());
    }
    object->set_visible(this->get_visible());
    object->set_disabled(this->get_disabled());
    // child objects of 'object' now have delta.
    object->sync();
    // reset delta values since we already applied them.
    object->reset_delta();
  }
  this->reset_delta();
}

[[nodiscard]] const BBoxResource& BaseObject::get_position() const noexcept {
  return this->_pos_info;
}

void BaseObject::set_position(const BBoxResource& pos) noexcept {
  this->_copy_last_pos_info = this->_pos_info;
  this->_pos_info = pos;
}

[[nodiscard]] const idk::f32& BaseObject::get_x() const noexcept {
  return this->_pos_info.get_x();
}

[[nodiscard]] const idk::f32& BaseObject::get_y() const noexcept {
  return this->_pos_info.get_y();
}

[[nodiscard]] const idk::f32& BaseObject::get_w() const noexcept {
  return this->_pos_info.get_w();
}

[[nodiscard]] const idk::f32& BaseObject::get_h() const noexcept {
  return this->_pos_info.get_h();
}

[[nodiscard]] const ColorResource& BaseObject::get_color() const noexcept {
  return this->_color;
}

[[nodiscard]] bool BaseObject::is_imported_from_somewhere() const noexcept {
  return !this->imported_from.empty();
}

void BaseObject::set_x(idk::f32 x, const std::source_location& instance) noexcept {
  this->_copy_last_pos_info.set_x(this->_pos_info.get_x());
  this->_pos_info.set_x(x);
}

void BaseObject::set_y(idk::f32 y) noexcept {
  this->_copy_last_pos_info.set_y(this->_pos_info.get_y());
  this->_pos_info.set_y(y);
}

void BaseObject::set_w(idk::f32 w) noexcept {
  this->_copy_last_pos_info.set_w(this->_pos_info.get_w());
  this->_pos_info.set_w(w);
}

void BaseObject::set_h(idk::f32 h) noexcept {
  this->_copy_last_pos_info.set_h(this->_pos_info.get_h());
  this->_pos_info.set_h(h);
}

void BaseObject::set_color(const ColorResource& res) noexcept {
  this->_color = res;
}

[[nodiscard]] const idk::u32& BaseObject::get_id() const noexcept {
  return this->_object_id;
}

[[nodiscard]] BBoxResource BaseObject::get_delta() const noexcept {
  return {
    this->get_delta_x(),
    this->get_delta_y(),
    this->get_delta_w(),
    this->get_delta_h()
  };
}

[[nodiscard]] idk::f32 BaseObject::get_delta_x() const noexcept {
  return this->_pos_info.get_x() - this->_copy_last_pos_info.get_x();
}

[[nodiscard]] idk::f32 BaseObject::get_delta_y() const noexcept {
  return this->_pos_info.get_y() - this->_copy_last_pos_info.get_y();
}

[[nodiscard]] idk::f32 BaseObject::get_delta_w() const noexcept {
  return this->_pos_info.get_w() - this->_copy_last_pos_info.get_w();
}

[[nodiscard]] idk::f32 BaseObject::get_delta_h() const noexcept {
  return this->_pos_info.get_h() - this->_copy_last_pos_info.get_h();
}

[[nodiscsard]] idk::f32 BaseObject::get_delta_rot() const noexcept {
  return this->_rotation_degrees - this->_last_rotation_degrees;
}

[[nodiscard]] const std::string& BaseObject::get_fescript_path() const noexcept {
  return this->script_file_name;
}

void BaseObject::reset_delta() noexcept {
  this->_copy_last_pos_info = this->_pos_info;
  this->_last_rotation_degrees = this->_rotation_degrees;
}

void BaseObject::push_object(std::shared_ptr<BaseObject> sub_object) noexcept {
  if(!sub_object) [[unlikely]] {
    log_warning(src(), "BaseObject::push_object(): invalid pointer.");
    return;
  }
  sub_object->_parent = this->_give_shared_ptr();
  this->_sub_objects.push_back(std::move(sub_object));
}

void BaseObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: BaseObject has not field named as '"
              << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void BaseObject::sync_init() noexcept {
  this->init_signal();
  for(auto& child: this->_sub_objects) {
    child->init_signal();
    child->sync_init();
  }
}

[[nodiscard]] std::vector<std::shared_ptr<BaseObject>>& BaseObject::get_childs() noexcept {
  return this->_sub_objects;
}

[[nodiscard]] const std::string& BaseObject::get_name() const noexcept {
  return this->_name;
}

void BaseObject::set_name(const std::string& name) noexcept {
  this->_name = name;
}

void BaseObject::load_fescript_rt(const std::string& script, bool is_file) noexcept {
  if(script.empty()) {
    return;
  }
  {
    std::string script_content;
    if(is_file) {
      std::ifstream script_stream(script);

      for(std::string temp_str; std::getline(script_stream, temp_str); script_content.append(temp_str)) {
        script_content.push_back('\n');
      }

      this->script_file_name = script;
    } else {
      script_content = script;
    }
    this->script_content = script_content;
  }
  const auto& tokens = fescript::Scanner(this->script_content).scan_tokens();
  auto statements = fescript::Parser(tokens).parse();

  if (fescript::had_error || fescript::had_runtime_error) {
    log_error(src(), "caught fescript parse error.");
    return;
  }
  fescript::Resolver(this->_code).resolve(statements);

  if (fescript::had_error || fescript::had_runtime_error) {
    log_error(src(), "caught fescript resolve error.");
    return;
  }

  this->_code.get_statements() = statements;
  this->_code.get_render_object_id() = this->_object_id;
  this->_code.get_parent_object() = this->_give_shared_ptr();

  // we run interpreter first to calculate first values of variables.
  // it prevents "variable not found in scope" style problems.
  this->_code.interpret(this->_code.get_statements());

  if (fescript::had_error || fescript::had_runtime_error) {
    log_error(src(), "caught fescript interpret error.");
    return;
  }
  log_info(src(), "script loaded: '{}', '{}'", this->_name, this->script_file_name);
}

[[nodiscard]] const std::shared_ptr<BaseObject>& BaseObject::get_object_by_path(const std::string& path) noexcept {
  auto current = this->_give_shared_ptr();
  for(const auto& entry: std::filesystem::path(path)) {
    current = current->_get_object_by_single_path(entry.string());
  }
  return current;
}

[[nodiscard]] const idk::f32& BaseObject::get_rotation() const noexcept {
  return this->_rotation_degrees;
}

void BaseObject::set_rotation(idk::f32 rad_degrees) noexcept {
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
}

[[nodiscard]] idk::f32 BaseObject::counter_clockwise_to_clockwise(idk::f32 rad_degrees) noexcept {
  return std::fmodf(rad_degrees + mul_2_pi_v<idk::f32>, mul_2_pi_v<idk::f32>);
}

[[nodiscard]] const std::shared_ptr<BaseObject>& BaseObject::_get_object_by_single_path(const std::string& path) noexcept {
  if(path == "." || path.empty()) {
    return this->_give_shared_ptr();
  }
  if(path == "..") {
    if(!this->_parent) {
      log_warning(src(), "parent object is invalid; {} might be top on the list.", this->get_name());
    }
    return this->_parent;
  }
  for(auto& sub_obj: this->_sub_objects) {
    if(sub_obj->_name == path) {
      return sub_obj;
    }
  }
  log_warning(src(), "cannot find '{}' in members of {}.", this->get_name());
  return nullptr;
}

[[nodiscard]] const std::shared_ptr<BaseObject>& BaseObject::_give_shared_ptr() noexcept {
  if(!this->_shared_ptr_this) {
    this->_shared_ptr_this = std::shared_ptr<BaseObject>(this);
  }
  return this->_shared_ptr_this;
}
}// namespace fresh