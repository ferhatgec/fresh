#include "../../../include/fescript/wrappers/fescript_area_object.hpp"
#include "../../../include/objects/area_object.hpp"

namespace fescript {
// first argument must be self, second argument must be object that handles if there any collision between
// that two object.
__idk_nodiscard Object FescriptAreaObjectMemberIsCollidingWith::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: AreaObject is not initialized, yet using AreaObject.is_colliding_with() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "AreaObject.is_colliding_with() must take 1 argument.\n";
    std::exit(1);
  }
  switch(arguments.front().index()) {
    case FescriptBaseObjectIndex: {
      return this->_self->is_colliding_with(
        std::get<FescriptBaseObjectIndex>(arguments.front())
        );
    }
    case FescriptSpriteObjectIndex: {
      return this->_self->is_colliding_with(
        std::get<FescriptSpriteObjectIndex>(arguments.front())
      );
    }
    case FescriptLabelObjectIndex: {
      return this->_self->is_colliding_with(
        std::get<FescriptLabelObjectIndex>(arguments.front())
      );
    }
    case FescriptAreaObjectIndex: {
      return this->_self->is_colliding_with(
        std::get<FescriptAreaObjectIndex>(arguments.front())
      );
    }
    default: {
      std::cout << "Engine [language] error: AreaObject.is_colliding_with() requires objects those inherited from BaseObject.\n";
      std::exit(1);
    }
  }
}

AreaObjectWrapper::AreaObjectWrapper() {
  this->_object_def = "areaobject";
}

AreaObjectWrapper::~AreaObjectWrapper() {

}

[[nodiscard]] std::string AreaObjectWrapper::to_string() {
  return "areaobject";
}

[[nodiscard]] Object AreaObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto area_object = std::make_shared<fresh::AreaObject>();
  this->_object_id = area_object->get_object_id();
  return std::move(area_object);
}
} // namespace fescript