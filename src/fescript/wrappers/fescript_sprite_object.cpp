#include "../../../include/fescript/wrappers/fescript_sprite_object.hpp"
#include "../../../include/objects/sprite_object.hpp"

#include <fescript/wrappers/fescript_sprite_object.hpp>
#include <objects/sprite_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptSpriteObjectMemberInitSprite::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: SpriteObject is not initialized, yet using SpriteObject.init_sprite() is not possible.\n";
    std::exit(1);
  }
  if(!arguments.empty()) {
    std::cout << "SpriteObject.init_sprite() must have not take any argument/s.\n";
    std::exit(1);
  }
  this->_self->get_sprite_resource().load_resource(this->_self->get_sprite_resource()._texture_path);
  return nullptr;
}

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