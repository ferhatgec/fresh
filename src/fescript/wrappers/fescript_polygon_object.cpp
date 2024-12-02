// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_polygon_object.hpp>
#include <objects/polygon_object.hpp>
#include <fescript/fescript_token.hpp>

namespace fescript {
[[nodiscard]] Object FescriptPolygonObjectMemberPushPolygon::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("PolygonObject.push_polygon()", 2)
  this->_self->get_polygon_resource().push_polygon(std::get<LongDoubleIndex>(arguments[0]),std::get<LongDoubleIndex>(arguments[1]));
  return nullptr;
}

[[nodiscard]] Object FescriptPolygonObjectMemberDeleteAllPolygons::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->get_polygon_resource().delete_all_polygons();
  return this->_self->get_polygon_resource().get_polygons().empty();
}

[[nodiscard]] Object FescriptPolygonObjectMemberGetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->_self->get_polygon_resource().get_filled();
}

[[nodiscard]] Object FescriptPolygonObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto polygon_object = std::make_shared<fresh::PolygonObject>();
  this->_object_id = polygon_object->get_id();
  return std::move(polygon_object);
}
} // namespace fresh