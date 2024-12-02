// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
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
  this->_self->push_object(std::move(Interpreter::fescript_object_to_baseobject(arguments[0])));
  // TODO: make init_signal as a fescript member function. so users can call it whenever they want explicitly.
  this->_self->get_childs().back()->init_signal();
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetRotationByRadianDegrees::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject().set_rotation()", 1)
  this->_self->set_rotation(static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])));
  return nullptr;
}

FescriptBaseObjectWrapper::FescriptBaseObjectWrapper(
  idk::u32 object_id,
  const std::vector <std::shared_ptr<FescriptBaseObjectWrapper>>& sub_objects
) : _object_id{object_id}, _sub_objects{sub_objects} {}

[[nodiscard]] Object FescriptBaseObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return std::make_shared<fresh::BaseObject>();
}
} // namespace fescript