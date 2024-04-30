#include "../../include/objects/area_object.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"
#include "../../include/objects/camera_object.hpp"
#include <iostream>

namespace fresh {
AreaObject::AreaObject() {
}

AreaObject::AreaObject(SDL_Rect pos_info) {
  this->_object_def = "areaobject";
  this->_pos_info = pos_info;
}

AreaObject::AreaObject(std::shared_ptr<BaseObject> base_object) {
  if(!base_object.get()) {
    std::cout << "Engine error: Passed null pointer to AreaObject ctor.\n";
    return;
  }

  this->_object_def = "areaobject";
  this->_pos_info = base_object->_pos_info;
}

AreaObject::~AreaObject() {
}

void AreaObject::sync() noexcept {
  this->get_position_info();// update deltas
  this->_code.interpret_update();

  if(!this->_visible || this->_disabled)
    return;

  for(auto& object : this->_sub_objects) {
    object->sync();
  }

  for(auto& object : this->_sub_objects) {
    object->get_position_info().x += this->delta_x();
    object->get_position_info().y += this->delta_y();
    object->get_position_info().w += this->delta_w();
    object->get_position_info().h += this->delta_h();

    if(object->_object_def != "cameraobject")// we actually sync cameraobject in engine::update()
      object->sync();
  }
}

__idk_nodiscard bool
AreaObject::is_colliding_with(std::shared_ptr<BaseObject> object) noexcept {// simple aabb collision detection.
  if(this->_disabled)
    return false;

  return (_pos_info.x < object->_pos_info.x + object->_pos_info.w && _pos_info.x + _pos_info.w > object->_pos_info.x && _pos_info.y < object->_pos_info.y + object->_pos_info.h && _pos_info.y + _pos_info.h > object->_pos_info.y);
}

[[nodiscard]] void AreaObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: AreaObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh