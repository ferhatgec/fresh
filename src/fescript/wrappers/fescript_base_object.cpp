// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <log/log.hpp>

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

[[nodiscard]] Object FescriptBaseObjectMemberSetVisible::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BaseObject.set_visible()", 1)
  this->get_self()->set_visible(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetDisabled::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BaseObject.set_disabled()", 1)
  this->get_self()->set_disabled(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetX::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject.set_x()", 1)
  // FIXME: there might be some issues with that, using lazy_set_h could be better (for all xywh functions)
  this->get_self()->set_x(std::get<LongDoubleIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetY::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject.set_y()", 1)
  // FIXME: there might be some issues with that, using lazy_set_h could be better.
  this->get_self()->set_w(std::get<LongDoubleIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetW::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject.set_w()", 1)
  // FIXME: there might be some issues with that, using lazy_set_h could be better.
  this->get_self()->set_w(std::get<LongDoubleIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetH::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject.set_h()", 1)
  // FIXME: there might be some issues with that, using lazy_set_h could be better.
  this->get_self()->set_h(std::get<LongDoubleIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetXYWH::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_ARRAY("BaseObject.set_xywh()", 1)
  const auto& arr = std::get<FescriptArrayIndex>(arguments[0]);
  this->get_self()->set_x(static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(0))));
  this->get_self()->set_y(static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(1))));
  this->get_self()->set_w(static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(2))));
  this->get_self()->set_h(static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(3))));
  return nullptr;
}


[[nodiscard]] Object FescriptBaseObjectMemberSetRot::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BaseObject.set_rot()", 1)
  this->get_self()->set_rotation(std::get<LongDoubleIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetName::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("BaseObject.set_name()", 1)
  this->get_self()->set_name(std::get<StringIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetFlipVertically::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BaseObject.set_flip_vertically()", 1)
  this->get_self()->set_flip_vertically(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberSetFlipHorizontally::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BaseObject.set_flip_horizontally()", 1)
  this->get_self()->set_flip_horizontally(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBaseObjectMemberGetVisible::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->get_self()->get_visible();
}

[[nodiscard]] Object FescriptBaseObjectMemberGetDisabled::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->get_self()->get_disabled();
}

[[nodiscard]] Object FescriptBaseObjectMemberGetX::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we need float, double representation in fescript,
  // it's like waste of memory when C++ API uses float and fescript uses long double.
  return static_cast<idk::f80>(this->get_self()->get_x());
}

[[nodiscard]] Object FescriptBaseObjectMemberGetY::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we need float, double representation in fescript,
  // it's like waste of memory when C++ API uses float and fescript uses long double.
  return static_cast<idk::f80>(this->get_self()->get_y());
}

[[nodiscard]] Object FescriptBaseObjectMemberGetW::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we need float, double representation in fescript,
  // it's like waste of memory when C++ API uses float and fescript uses long double.
  return static_cast<idk::f80>(this->get_self()->get_w());
}

[[nodiscard]] Object FescriptBaseObjectMemberGetH::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we need float, double representation in fescript,
  // it's like waste of memory when C++ API uses float and fescript uses long double.
  return static_cast<idk::f80>(this->get_self()->get_h());
}

[[nodiscard]] Object FescriptBaseObjectMemberGetXYWH::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: cache FescriptArray in BaseObject.
  auto arr = std::make_shared<FescriptArray>();
  arr->set_array({
    static_cast<idk::f80>(this->get_self()->get_x()),
    static_cast<idk::f80>(this->get_self()->get_y()),
    static_cast<idk::f80>(this->get_self()->get_w()),
    static_cast<idk::f80>(this->get_self()->get_h())
  });
  return std::move(arr);
}

[[nodiscard]] Object FescriptBaseObjectMemberGetRot::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we need float, double representation in fescript,
  // it's like waste of memory when C++ API uses float and fescript uses long double.
  return static_cast<idk::f80>(this->get_self()->get_rotation());
}

[[nodiscard]] Object FescriptBaseObjectMemberGetName::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->get_self()->get_name();
}

[[nodiscard]] Object FescriptBaseObjectMemberGetFlipVertically::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->get_self()->get_flip_vertically();
}

[[nodiscard]] Object FescriptBaseObjectMemberGetFlipHorizontally::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->get_self()->get_flip_horizontally();
}

[[nodiscard]] Object FescriptBaseObjectMemberGetObject::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("BaseObject.get_object", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  return Interpreter::baseobject_to_fescript_object(
    this->get_self()->get_object_by_path(std::get<StringIndex>(arguments[0]))
  );
}

FescriptBaseObjectWrapper::FescriptBaseObjectWrapper(
  idk::u32 object_id,
  const std::vector <std::shared_ptr<FescriptBaseObjectWrapper>>& sub_objects
) : _object_id{object_id}, _sub_objects{sub_objects} {
}

[[nodiscard]] Object FescriptBaseObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return std::make_shared<fresh::BaseObject>();
}
} // namespace fescript