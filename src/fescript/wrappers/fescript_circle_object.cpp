#include <fescript/wrappers/fescript_circle_object.hpp>
#include <objects/circle_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptCircleObjectMemberGetRadius::call(Interpreter& interpreter, std::vector<Object> arguments) {
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_radius());
}

__idk_nodiscard Object FescriptCircleObjectMemberGetSegments::call(Interpreter& interpreter, std::vector<Object> arguments) {
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_segments());
}

__idk_nodiscard Object FescriptCircleObjectMemberGetIsFilled::call(Interpreter& interpreter, std::vector<Object> arguments) {
  return this->_self->get_circle_resource().get_is_filled();
}

__idk_nodiscard Object FescriptCircleObjectMemberSetRadius::call(Interpreter& interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("CircleObject.set_radius()", 1)
  this->_self->get_circle_resource().get_radius() = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptCircleObjectMemberSetSegments::call(Interpreter& interpreter, std::vector<Object> arguments) {
  ERR_CHECK_DECIMAL("CircleObject.set_segments()", 1)
  this->_self->get_circle_resource().get_segments() = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptCircleObjectMemberSetIsFilled::call(Interpreter& interpreter, std::vector<Object> arguments) {
  ERR_CHECK_BOOL("CircleObject.set_is_filled()", 1)
  this->_self->get_circle_resource().get_is_filled() = std::get<BoolIndex>(arguments.front());
  return nullptr;
}

CircleObjectWrapper::CircleObjectWrapper() {
  this->_object_def = "circleobject";
}

CircleObjectWrapper::~CircleObjectWrapper() noexcept {

}

[[nodiscard]] std::string CircleObjectWrapper::to_string() {
  return "circleobject";
}

[[nodiscard]] Object CircleObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto circle_object = std::make_shared<fresh::CircleObject>();
  this->_object_id = circle_object->get_object_id();
  return std::move(circle_object);
}
} // namespace fescript