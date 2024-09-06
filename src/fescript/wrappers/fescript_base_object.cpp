#include <log/log.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptBaseObjectMemberPushSubObject::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.empty()) {
    fresh::log_error(fresh::src(), "BaseObject().push_sub_object() no argument provided.");
    return nullptr;
  }
  if(!Token::is_base_object(arguments[0])) {
    fresh::log_error(fresh::src(), "BaseObject().push_sub_object() argument must be derived from BaseObject; got: {}", Token::to_string(arguments[0]));
    return nullptr;
  }
  this->_self->push_to_sub_objects(std::move(Interpreter::fescript_object_to_baseobject(arguments[0])));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetRotationByRadianDegrees::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject().set_rotation_by_radian_degrees()", 1)
  this->_self->set_rotation_by_radian_degrees(static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])));
  return nullptr;
}

BaseObjectWrapper::BaseObjectWrapper()
  : _object_def("baseobject") {}

BaseObjectWrapper::BaseObjectWrapper(const idk::StringViewChar& object_def,
                                     idk::u32 object_id,
                                     const std::vector <std::shared_ptr<BaseObjectWrapper>>& sub_objects)
  : _object_def{object_def}, _object_id{object_id}, _sub_objects{sub_objects} {}

BaseObjectWrapper::~BaseObjectWrapper() {}

[[nodiscard]] std::string BaseObjectWrapper::to_string() {
  return "baseobject";
}

[[nodiscard]] Object BaseObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return std::make_shared<fresh::BaseObject>();
}
} // namespace fescript