#include <fescript/wrappers/fescript_base_object.hpp>

namespace fescript {
BaseObjectWrapper::BaseObjectWrapper()
  : _object_def("baseobject") {}

BaseObjectWrapper::BaseObjectWrapper(const idk::StringViewChar& object_def,
                                     idk::u32 object_id,
                                     const std::vector <std::shared_ptr<BaseObjectWrapper>>& sub_objects)
  : _object_def{std::move(object_def)}, _object_id{std::move(object_id)}, _sub_objects{std::move(sub_objects)} {}

BaseObjectWrapper::~BaseObjectWrapper() {}

[[nodiscard]] std::string BaseObjectWrapper::to_string() {
  return "baseobject";
}

[[nodiscard]] Object BaseObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  return std::make_shared<fresh::BaseObject>();
}
} // namespace fescript