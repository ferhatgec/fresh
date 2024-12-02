// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/physics/fescript_rectangle_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptRectangleAreaObjectMemberIsCollidingWith::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: RectangleAreaObject is not initialized, yet using RectangleAreaObject.is_colliding_with() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "RectangleAreaObject.is_colliding_with() must take 1 argument.\n";
    std::exit(1);
  }
  // duplicate code, but there won't be too much different areaobjects. maybe ellipse as extra.
  switch(arguments.front().index()) {
  case FescriptBaseObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptBaseObjectIndex>(arguments.front())); }
  case FescriptRectangleAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptRectangleAreaObjectIndex>(arguments.front())); }
  case FescriptCircleAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptCircleAreaObjectIndex>(arguments.front())); }
  case FescriptPolygonAreaObjectIndex: { return this->_self->is_colliding_with(std::get<FescriptPolygonAreaObjectIndex>(arguments.front())); }
  }
  return false;
}

[[nodiscard]] Object FescriptRectangleAreaObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto rectangle_area_object = std::make_shared<fresh::RectangleAreaObject>();
  this->_object_id = rectangle_area_object->get_id();
  return std::move(rectangle_area_object);
}
} // namespace fescript