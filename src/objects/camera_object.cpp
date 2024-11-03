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
}

CameraObject::CameraObject(idk::f32 width, idk::f32 height) {
  this->_camera = std::make_unique<fre2d::Camera>(width, height);
  this->set_position({this->get_x(), this->get_y(), width, height});
  this->reset_delta();
}

void CameraObject::sync() noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->apply_changes();
}

void CameraObject::set_camera_position(const PointResource& pt) noexcept {
  if(PointResource{this->_pos_info.get_x(), this->_pos_info.get_y()} == pt) {
    return;
  }
  this->_camera->set_position(glm::vec3{pt.get_x(), pt.get_y(), 1.f});
  this->set_position({ pt.get_x(), pt.get_y(), this->get_w(), this->get_h()});
}

void CameraObject::move_camera(const PointResource& pt) noexcept {
  if (pt == PointResource{0.f, 0.f}) {
    return;
  }
  this->_camera->set_position(
      glm::vec3{this->get_x() + pt.get_x(), this->get_y() + pt.get_y(), 1.f});
  this->set_position({this->get_x() + pt.get_x(), this->get_y() + pt.get_y()});
}

void CameraObject::resize_camera(idk::f32 w, idk::f32 h) noexcept {
  if(fre2d::detail::nearly_equals(this->get_w(), 0.f) && fre2d::detail::nearly_equals(this->get_h(), 0.f)) {
    return;
  }
  std::cout << std::format("w, h = {}, {} for camera\n", w, h);
  this->_camera->resize(static_cast<GLsizei>(w), static_cast<GLsizei>(h));
  this->set_position({this->get_x(), this->get_y(), w, h});
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