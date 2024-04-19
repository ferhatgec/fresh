#include "../../include/freshengine.hpp"

namespace fresh {
CameraObject::CameraObject() {
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

void CameraObject::sync() noexcept {
  this->_code.interpret_update();

  for(auto& object : fresh::RenderObjects::objects_to_render) {
    if(object->_object_def != "cameraobject") {
      object->get_position_info().x =
        object->get_position_info().x - this->delta_x();
      object->get_position_info().y =
        object->get_position_info().y - this->delta_y();
    }
  }

  for(auto& object : this->_sub_objects) {
    object->get_position_info().x += this->delta_x();
    object->get_position_info().y += this->delta_y();
    object->get_position_info().w += this->delta_w();
    object->get_position_info().h += this->delta_h();

    if(object->_object_def != "cameraobject")// we actually do sync cameraobject in engine::update()
      object->sync();
  }

  this->get_position_info();// update deltas
}
}// namespace fresh