// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
CameraObject::CameraObject() {
  if(!Engine::get_instance()->get_window()->get_raw_window()) {
    log_info(src(), "camera size not specified directly and "
                    "it's not possible to detect automatically since window is not initialized.");
    return;
  }
  const auto& [width, height] = Engine::get_instance()->get_window()->get_window_size();
  this->_camera = std::make_unique<fre2d::Camera>(width, height);
  this->set_position({this->get_x(), this->get_y(), static_cast<idk::f32>(width), static_cast<idk::f32>(height)});
  this->reset_delta();
  this->_member_of_camera = true;
}

CameraObject::CameraObject(idk::f32 width, idk::f32 height) {
  this->_camera = std::make_unique<fre2d::Camera>(width, height);
  this->set_position({this->get_x(), this->get_y(), width, height});
  this->reset_delta();
  this->_member_of_camera = true;
}

void CameraObject::sync(bool is_member_of_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes(true);
}

void CameraObject::set_camera_position(const PointResource& pt) noexcept {
  if(PointResource{this->_pos_info.get_x(), this->_pos_info.get_y()} == pt) {
    return;
  }
  this->_camera->set_position(glm::vec3{pt.get_x(), pt.get_y(), 1.f});
  this->set_position({ pt.get_x(), pt.get_y(), this->get_w(), this->get_h()});
  // we apply delta at the time because there might be more than one calls to changing
  // position of an object; that is because there still at least one delta waits to be
  // applied into its child objects; in the end of apply_changes; it will reset the delta.
  //this->apply_changes(true);
}

void CameraObject::move_camera(const PointResource& pt) noexcept {
  if (pt == PointResource{0.f, 0.f}) {
    return;
  }
  this->_camera->set_position(
      glm::vec3{this->get_x() + pt.get_x(), this->get_y() + pt.get_y(), 1.f});
  this->set_position({this->get_x() + pt.get_x(), this->get_y() + pt.get_y()});
  //this->apply_changes(true);
}

void CameraObject::resize_camera(idk::f32 w, idk::f32 h) noexcept {
  if(fre2d::detail::nearly_equals(this->get_w(), 0.f) && fre2d::detail::nearly_equals(this->get_h(), 0.f)) {
    return;
  }
  this->_camera->resize(w, h);
  this->set_position({this->get_x(), this->get_y(), w, h});
  //this->apply_changes(true);
}

[[nodiscard]] const std::unique_ptr<fre2d::Camera>& CameraObject::get_camera()
    const noexcept {
  return this->_camera;
}

void CameraObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CameraObject has no field named as '"
              << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}  // namespace fresh