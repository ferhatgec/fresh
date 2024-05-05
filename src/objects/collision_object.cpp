#include "../../include/objects/collision_object.hpp"
#include "../../include/render_objects.hpp"
#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/fescript_array.hpp"
#include "../../include/objects/camera_object.hpp"
#include <iostream>

namespace fresh {
CollisionObject::CollisionObject() {
  this->_object_def = "collisionobject";
}

CollisionObject::~CollisionObject() {
}

void CollisionObject::sync() noexcept {
  this->get_position_info(); // update deltas
  this->_code.interpret_update();

  if(this->_disabled)
    return;

  for(auto& object : RenderObjects::objects_to_render) {
    if(object && (object->_object_def != "cameraobject"))
      object->_block_transform = this->is_colliding_with(object);
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

[[nodiscard]] void CollisionObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CollisionObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh