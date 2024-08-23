#include <fescript/wrappers/physics/fescript_polygon_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptPolygonAreaObjectMemberIsCollidingWith::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: PolygonAreaObject is not initialized, yet using PolygonAreaObject.is_colliding_with() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "PolygonAreaObject.is_colliding_with() must take 1 argument.\n";
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

__idk_nodiscard Object FescriptPolygonAreaObjectMemberPushPolygon::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: PolygonAreaObject is not initialized, yet using PolygonAreaObject.push_polygon() is not possible.\n";
    std::exit(1);
  }
  ERR_CHECK_DECIMAL("PolygonAreaObject.push_polygon()", 2)
  this->_self->get_polygon_resource().push_polygon(static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])),
                                                   static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[1])));
  return nullptr;
}

__idk_nodiscard Object FescriptPolygonAreaObjectMemberDeleteAllPolygons::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: PolygonAreaObject is not initialized, yet using PolygonAreaObject.delete_all_polygons() is not possible.\n";
    std::exit(1);
  }
  this->_self->get_polygon_resource().delete_all_polygons();
  return nullptr;
}

PolygonAreaObjectWrapper::PolygonAreaObjectWrapper() {
  this->_object_def = "polygonareaobject";
}

PolygonAreaObjectWrapper::~PolygonAreaObjectWrapper() {
}

// TODO: just return _object_def. do not override to_string from BaseObjectWrapper, remove virtual.
[[nodiscard]] std::string PolygonAreaObjectWrapper::to_string() {
  return "polygonareaobject";
}

[[nodiscard]] Object PolygonAreaObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto polygon_area_object = std::make_shared<fresh::PolygonAreaObject>();
  this->_object_id = polygon_area_object->get_object_id();
  return std::move(polygon_area_object);
}
} // namespace fescript