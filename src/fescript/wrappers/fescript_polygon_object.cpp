#include <fescript/wrappers/fescript_polygon_object.hpp>
#include <objects/polygon_object.hpp>
#include <fescript/fescript_token.hpp>

namespace fescript {
__idk_nodiscard Object FescriptPolygonObjectMemberPushPolygon::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("PolygonObject.push_polygon()", 2)
  this->_self->get_polygon_resource().push_polygon(std::get<LongDoubleIndex>(arguments[0]),std::get<LongDoubleIndex>(arguments[1]));
  return nullptr;
}

__idk_nodiscard Object FescriptPolygonObjectMemberDeleteAllPolygons::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->get_polygon_resource().delete_all_polygons();
  return this->_self->get_polygon_resource().get_polygons().empty();
}

__idk_nodiscard Object FescriptPolygonObjectMemberGetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->_self->get_polygon_resource().get_is_filled();
}

PolygonObjectWrapper::PolygonObjectWrapper() {
  this->_object_def = "polygonobject";
}

PolygonObjectWrapper::~PolygonObjectWrapper() noexcept {

}

[[nodiscard]] std::string PolygonObjectWrapper::to_string() {
  return "polygonobject";
}

[[nodiscard]] Object PolygonObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto polygon_object = std::make_shared<fresh::PolygonObject>();
  this->_object_id = polygon_object->get_object_id();
  return std::move(polygon_object);
}
} // namespace fresh