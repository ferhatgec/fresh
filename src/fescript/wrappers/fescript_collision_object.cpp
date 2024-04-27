#include "../../../include/fescript/wrappers/fescript_collision_object.hpp"
#include "../../../include/objects/collision_object.hpp"

namespace fescript {
CollisionObjectWrapper::CollisionObjectWrapper() {
  this->_object_def = "collisionobject";
}

CollisionObjectWrapper::~CollisionObjectWrapper() {

}

[[nodiscard]] std::string CollisionObjectWrapper::to_string() {
  return "collisionobject";
}

[[nodiscard]] Object CollisionObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto collision_object = std::make_shared<fresh::CollisionObject>();
  this->_object_id = collision_object->get_object_id();
  return std::move(collision_object);
}
} // namespace fescript