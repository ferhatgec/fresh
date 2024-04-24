#include "../../../include/fescript/wrappers/fescript_sprite_object.hpp"
#include "../../../include/objects/sprite_object.hpp"

namespace fescript {
SpriteObjectWrapper::SpriteObjectWrapper() {
  this->_object_def = "spriteobject";
}

SpriteObjectWrapper::~SpriteObjectWrapper() {

}

[[nodiscard]] std::string SpriteObjectWrapper::to_string() {
  return "spriteobject";
}

[[nodiscard]] Object SpriteObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto sprite_object = std::make_shared<fresh::SpriteObject>();
  this->_object_id = sprite_object->get_object_id();
  return std::move(sprite_object);
}
} // namespace fescript