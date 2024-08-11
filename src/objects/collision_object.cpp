#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

#include <objects/collision_object.hpp>
#include <objects/camera_object.hpp>
#include <render_objects.hpp>

#include <iostream>

namespace fresh {
CollisionObject::CollisionObject() {
  this->_object_def = "collisionobject";
}

CollisionObject::~CollisionObject() {
}

void CollisionObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);

  if(this->_disabled)
    return;

  for(auto& object : RenderObjects::objects_to_render) {
    if(object && (object->_object_def != "cameraobject"))
      object->_block_transform = this->is_colliding_with(object);
  }
  APPLY_DELTAS()
}

void CollisionObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CollisionObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}
}// namespace fresh