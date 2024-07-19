#include "../../include/freshengine.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"

namespace fresh {
CameraObject::CameraObject() : _zoom_level{1.0f}, _scale_ratio_w{1.0f}, _scale_ratio_h{1.0f} {
  this->_object_def = "cameraobject";
}

CameraObject::~CameraObject() {
}

__idk_nodiscard bool
CameraObject::is_visible_on_camera(std::shared_ptr<fresh::BaseObject> object) noexcept {
  if(!object.get()) {
    std::cout << "Engine warning: Invalid BaseObject passed as argument to is_visible_on_camera().\n";
    return false;
  }

  return !((object->_pos_info.x > _pos_info.w)
           || (object->_pos_info.x + object->_pos_info.w < 0)
           || (object->_pos_info.y > _pos_info.h)
           || (object->_pos_info.y + object->_pos_info.h < 0));
}

void CameraObject::sync(bool is_sync_with_camera) noexcept {
  this->_pos_info.w = 400;
  this->_pos_info.h = 300;
  this->_code.interpret_update();
  APPLY_DELTAS()
}

void CameraObject::apply(std::shared_ptr<BaseObject> obj) noexcept {
  SDL_FRect new_pos = obj->_pos_info;
  new_pos.x -= this->_pos_info.x * this->_zoom_level;
  new_pos.y -= this->_pos_info.y * this->_zoom_level;
  new_pos.w *= this->_zoom_level;
  new_pos.h *= this->_zoom_level;
  obj->_render_pos_info = new_pos;
}

void CameraObject::set_zoom(idk::f32 new_zoom) noexcept {
  this->_zoom_level = new_zoom;
}

void CameraObject::move(idk::f32 dx, idk::f32 dy) noexcept {
  this->_pos_info.x += dx;
  this->_pos_info.y += dy;
}

[[nodiscard]] void CameraObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CameraObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh