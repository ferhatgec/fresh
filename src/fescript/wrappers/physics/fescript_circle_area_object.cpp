#include <fescript/wrappers/physics/fescript_circle_area_object.hpp>
#include <objects/physics/circle_area_object.hpp>

namespace fescript {
// TODO: change base function to take const Interpreter&, we've never changed interpreter (Interpreter&)
__idk_nodiscard Object FescriptCircleAreaObjectMemberIsCollidingWith::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: CircleAreaObject is not initialized, yet using CircleAreaObject.is_colliding_with() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "CircleAreaObject.is_colliding_with() must take 1 argument.\n";
    std::exit(1);
  }
  // we can use lambda this->_self->is_colliding_with([](){}()) but this is is_colliding_with, which possibly hundreds of called
  // every second to check for any collision of any AreaObject. we have not any optimization to cache collisions between static objects for now.
  // but for compiler it's probably easy to optimize this case but i did not test it, maybe later.
  switch(arguments.front().index()) {
  case FescriptBaseObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptBaseObjectIndex>(arguments.front())); }
  case FescriptRectangleAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptRectangleAreaObjectIndex>(arguments.front())); }
  case FescriptCircleAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptCircleAreaObjectIndex>(arguments.front())); }
  case FescriptPolygonAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptPolygonAreaObjectIndex>(arguments.front())); }
  }
  return false;
}

__idk_nodiscard Object FescriptCircleAreaObjectMemberGetRadius::call(Interpreter& interpreter, std::vector<Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: CircleAreaObject is not initialized, yet using CircleAreaObject.get_radius() is not possible.\n";
    std::exit(1);
  }
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_radius());
}

__idk_nodiscard Object FescriptCircleAreaObjectMemberSetRadius::call(Interpreter& interpreter, std::vector<Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: CircleAreaObject is not initialized, yet using CircleAreaObject.set_radius() is not possible.\n";
    std::exit(1);
  }
  ERR_CHECK_DECIMAL("CircleAreaObject.set_radius()", 1)
  if(const idk::f80& value = std::get<LongDoubleIndex>(arguments.front()); value >= 0.f) {
    this->_self->get_circle_resource().get_radius() = static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments.front()));
  } else {
    // TODO: we need more descriptive error messages. we can do it as storing a token that refers to current variable or object,
    // so we can directly access at which line our error has happened.
    std::cout << "Engine [language] error: CircleAreaObject.set_radius() is cannot take negative decimals.\n";
  }
  return nullptr;
}

CircleAreaObjectWrapper::CircleAreaObjectWrapper() {
  this->_object_def = "circleareaobject";
}

CircleAreaObjectWrapper::~CircleAreaObjectWrapper() {
}

// TODO: just return _object_def. do not override to_string from BaseObjectWrapper, remove virtual.
[[nodiscard]] std::string CircleAreaObjectWrapper::to_string() {
  return "circleareaobject";
}

[[nodiscard]] Object CircleAreaObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto circle_area_object = std::make_shared<fresh::CircleAreaObject>();
  this->_object_id = circle_area_object->get_object_id();
  return std::move(circle_area_object);
}
} // namespace fescript