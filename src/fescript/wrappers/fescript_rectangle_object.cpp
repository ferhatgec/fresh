#include <fescript/wrappers/fescript_rectangle_object.hpp>
#include <objects/rectangle_object.hpp>

namespace fescript {
RectangleObjectWrapper::RectangleObjectWrapper() {
  this->_object_def = "rectangleobject";
}

RectangleObjectWrapper::~RectangleObjectWrapper() noexcept {
}

[[nodiscard]] std::string RectangleObjectWrapper::to_string() {
  return "rectangleobject";
}

[[nodiscard]] Object RectangleObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto rectangle_object = std::make_shared<fresh::RectangleObject>();
  this->_object_id = rectangle_object->get_object_id();
  return std::move(rectangle_object);
}
} // namespace fescript