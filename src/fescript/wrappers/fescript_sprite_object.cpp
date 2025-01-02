// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_sprite_object.hpp>
#include <objects/sprite_object.hpp>
#include <freshengine.hpp>

namespace fescript {
[[nodiscard]] Object FescriptSpriteObjectMemberInitSprite::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: SpriteObject is not initialized, yet using SpriteObject.init_sprite() is not possible.\n";
    std::exit(1);
  }
  if(!arguments.empty()) {
    std::cout << "SpriteObject.init_sprite() must have not take any argument/s.\n";
    std::exit(1);
  }
  this->get_self()->get_sprite_resource().load_resource(
    this->get_self()->get_sprite_resource().get_path(),
    this->get_self()
  );
  return nullptr;
}

[[nodiscard]] Object FescriptSpriteObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto sprite_object = std::make_shared<fresh::SpriteObject>();
  this->_object_id = sprite_object->get_id();
  return std::move(sprite_object);
}
} // namespace fescript