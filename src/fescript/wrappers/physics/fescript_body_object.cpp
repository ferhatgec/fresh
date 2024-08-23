#include <fescript/wrappers/physics/fescript_body_object.hpp>
#include <objects/physics/body_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
BodyObjectWrapper::BodyObjectWrapper() {
  this->_object_def = "bodyobject";
}

BodyObjectWrapper::~BodyObjectWrapper() {

}

[[nodiscard]] std::string BodyObjectWrapper::to_string() {
  return "bodyobject";
}

[[nodiscard]] Object BodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto body_object = std::make_shared<fresh::BodyObject>();
  this->_object_id = body_object->get_object_id();
  return std::move(body_object);
}
} // namespace fescript