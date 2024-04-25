#include "../../../include/fescript/wrappers/fescript_label_object.hpp"
#include "../../../include/objects/label_object.hpp"

namespace fescript {
LabelObjectWrapper::LabelObjectWrapper() {
  this->_object_def = "labelobject";
}

LabelObjectWrapper::~LabelObjectWrapper() {

}

[[nodiscard]] std::string LabelObjectWrapper::to_string() {
  return "labelobject";
}

[[nodiscard]] Object LabelObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto label_object = std::make_shared<fresh::LabelObject>();
  this->_object_id = label_object->get_object_id();
  return std::move(label_object);
}
} // namespace fescript