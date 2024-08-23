#include <objects/base_object.hpp>
#include <objects/camera_object.hpp>

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_scanner.hpp>
#include <fescript/fescript_parser.hpp>
#include <fescript/fescript_resolver.hpp>
#include <fescript/fescript_array.hpp>

#include <freshengine.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <numbers>

namespace fresh {
BaseObject::BaseObject() {
  this->_pos_info = SDL_FRect { 0.f, 0.f, 0.f, 0.f };
  this->_rotation_degrees = this->_last_rotation_degrees = 0.f;
  this->_copy_last_pos_info = this->_pos_info;
  this->_object_id = Engine::get_instance()->get_global_id();
  this->_object_def = "baseobject";
  this->script_content = "";
  this->script_file_name = "";
  Engine::get_instance()->increase_global_id();
}

BaseObject::BaseObject(bool disabled, bool visible, idk::f32 pos_x, idk::f32 pos_y, idk::f32 width, idk::f32 height, idk::f32 rotation_degrees)
    : _disabled{disabled},
      _visible{visible},
      _rotation_degrees{rotation_degrees} {
  this->_last_rotation_degrees = 0.f;
  this->_pos_info = SDL_FRect {
    pos_x, pos_y, width, height
  };
  this->_copy_last_pos_info = this->_pos_info;
  this->_object_id = Engine::get_instance()->get_global_id();
  this->_object_def = "baseobject";
  this->script_content = "";
  this->script_file_name = "";
  Engine::get_instance()->increase_global_id();
}

BaseObject::~BaseObject() {}

__idk_nodiscard
bool& BaseObject::get_is_disabled() noexcept {
  return this->_disabled;
}

__idk_nodiscard
bool& BaseObject::get_is_visible() noexcept {
  return this->_visible;
}

void BaseObject::set_disabled(bool disabled) noexcept {
  this->_disabled = disabled;
}

void BaseObject::set_visible(bool visible) noexcept {
  this->_visible = visible;
}

void BaseObject::sync_pos_with_camera(bool is_sync_with_camera) noexcept {
  if(is_sync_with_camera) { // Object is child member of Camera, so we can't apply Camera
    this->_pos_info.x += this->delta_x();
    this->_pos_info.y += this->delta_y();
    this->_pos_info.w += this->delta_w();
    this->_pos_info.h += this->delta_h();
  } else {
    if(fresh::Engine::get_instance()->get_camera()) {
      fresh::Engine::get_instance()->get_camera()->apply(this->_give_shared_ptr());
      return;
    }
  }
  // no camera, so we use position as it is.
  this->_render_pos_info = this->_pos_info;
}

void BaseObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(!this->_visible || this->_disabled)
    return;
  APPLY_DELTAS()
}

__idk_nodiscard
SDL_FRect& BaseObject::get_position_info() noexcept {
  this->_copy_last_pos_info = this->_pos_info;
  return this->_pos_info;
}

__idk_nodiscard
SDL_FRect& BaseObject::get_raw_position_info() noexcept {
  return this->_pos_info;
}

__idk_nodiscard
SDL_FRect& BaseObject::get_render_position_info() noexcept {
  if(!Engine::get_instance()->get_camera()) {
    this->_render_pos_info = this->_pos_info; // if there is no camera, then CameraObject::apply won't be called,
                                              // so _render_pos_info is may be uninitialized. for now, we can directly access _render_pos_info and change it.
                                              // but we will change it with getters and setters, which will provide better API and checks.
  }
  return this->_render_pos_info;
}

__idk_nodiscard
const idk::u32& BaseObject::get_object_id() noexcept {
  return this->_object_id;
}

__idk_nodiscard
idk::f32 BaseObject::delta_x() noexcept {
  return this->_pos_info.x - this->_copy_last_pos_info.x;
}

__idk_nodiscard
idk::f32 BaseObject::delta_y() noexcept {
  return this->_pos_info.y - this->_copy_last_pos_info.y;
}

__idk_nodiscard
idk::f32 BaseObject::delta_w() noexcept {
  return this->_pos_info.w - this->_copy_last_pos_info.w;
}

__idk_nodiscard
idk::f32 BaseObject::delta_h() noexcept {
  return this->_pos_info.h - this->_copy_last_pos_info.h;
}

__idk_nodiscard
idk::f32 BaseObject::delta_rot() noexcept {
  return this->_rotation_degrees - this->_last_rotation_degrees;
}

void BaseObject::push_object(std::shared_ptr<BaseObject> sub_object) noexcept {
  if(!sub_object) [[unlikely]] {
    std::cout << "Engine warning: push_object argument contains an invalid pointer!\n";
    return;
  }

  this->push_to_sub_objects(sub_object);
  // this->_sub_objects.push_back(idk::move(sub_object));
}

void BaseObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: BaseObject has not field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
std::vector<std::shared_ptr<BaseObject>>& BaseObject::get_sub_objects() noexcept {
  return this->_sub_objects;
}

__idk_nodiscard
idk::StringViewChar& BaseObject::get_name() noexcept {
  return this->_name;
}

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
  this->_code.get_parent_object() = this->_give_shared_ptr();
  // we run interpreter first to calculate first values of variables.
  // it will prevent variable not found in scope style problems.
  this->_code.interpret(this->_code.get_statements());
  std::cout << this->_name << " " << this->script_file_name << '\n';
}

void BaseObject::push_to_sub_objects(const std::shared_ptr<BaseObject>& obj) noexcept {
  if(!obj) {
    std::cout << "Engine error: Invalid BaseObject/-inherited object passed to push_to_sub_objects()!\n";
    std::exit(1);
  }
  obj->_parent = this->_give_shared_ptr();
  this->_sub_objects.push_back(obj);
}

__idk_nodiscard
std::shared_ptr<BaseObject> BaseObject::get_object_by_path(const std::string& path) noexcept {
  std::shared_ptr<BaseObject> current = this->_give_shared_ptr();
  for(const auto& entry: std::filesystem::path(path))
    current = this->_get_object_by_single_path(entry.string());
  return current;
}

[[nodiscard]]
const idk::f32& BaseObject::get_rotation_by_radian_degrees() const noexcept {
  return this->_rotation_degrees;
}

void BaseObject::set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept {
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
}

[[nodiscard]] idk::f32 BaseObject::counter_clockwise_to_clockwise(idk::f32 rad_degrees) noexcept {
  return -std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
}

__idk_nodiscard
std::shared_ptr<BaseObject>
BaseObject::_get_object_by_single_path(const std::string& path) noexcept {
  if(path == "." || path.empty())
    return this->_give_shared_ptr();
  if(path == "..")
    return this->_parent;
  for(auto& sub_obj: this->_sub_objects) {
    if(sub_obj->_name == path.data()) {
      return sub_obj;
    }
  }
  std::cout << "Engine [language] error: Cannot find '" << path << "' in sub objects of" << this->_name << " object.\n";
  return this->_give_shared_ptr();
}

__idk_nodiscard PointResource BaseObject::_rectangle_convert_to_top_left(const SDL_FRect& pos) noexcept {
  return { pos.x - pos.w / 2.f, pos.y - pos.h / 2.f };
}

__idk_nodiscard PointResource BaseObject::_rectangle_convert_to_top_right(const SDL_FRect& pos) noexcept {
  return { pos.x + pos.w / 2.f, pos.y - pos.h / 2.f };
}

__idk_nodiscard PointResource BaseObject::_rectangle_convert_to_bottom_left(const SDL_FRect& pos) noexcept {
  return { pos.x - pos.w / 2.f, pos.y + pos.h / 2.f };
}

__idk_nodiscard PointResource BaseObject::_rectangle_convert_to_bottom_right(const SDL_FRect& pos) noexcept {
  return { pos.x + pos.w / 2.f, pos.y + pos.h / 2.f };
}

[[nodiscard]]
std::shared_ptr<BaseObject> BaseObject::_give_shared_ptr() noexcept {
  if(!this->_shared_ptr_this)
    this->_shared_ptr_this = std::shared_ptr<BaseObject>(this);
  return this->_shared_ptr_this;
}

[[nodiscard]]
SDL_FRect BaseObject::_center_to_top_left_pivot(SDL_FRect pos_size) noexcept  {
  return SDL_FRect {
    pos_size.x - pos_size.w / 2.f,
    pos_size.y - pos_size.h / 2.f,
    pos_size.w,
    pos_size.h
  };
}
}// namespace fresh