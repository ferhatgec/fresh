// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/physics/fescript_body_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/body_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptBodyObjectMemberSetFixedRot::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BodyObject.set_fixed_rot()", 1)
  this->get_self()->set_fixed_rotation(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptBodyObjectMemberGetFixedRot::call([[maybe_unused]] Interpreter& interpreter, [[maybe_unused]] const std::vector<Object>& arguments) {
  return this->get_self()->get_fixed_rotation();
}


[[nodiscard]] Object FescriptBodyObjectMemberSetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("BodyObject.set_is_static_body()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  this->_self->set_is_static_body(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptBodyObjectMemberGetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("BodyObject.get_is_static_body()")
  return this->_self->get_is_static_body();
}

[[nodiscard]] Object FescriptBodyObjectMemberSetLinearVelocity::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BodyObject.set_linear_velocity()", 2)
  this->get_self()->set_linear_velocity( {
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])),
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[1]))
  });
  return nullptr;
}

[[nodiscard]] Object FescriptBodyObjectMemberGetLinearVelocity::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto arr = std::make_shared<FescriptArray>();
  arr->push_value(this->get_self()->get_linear_velocity(), true);
  return std::move(arr);
}

[[nodiscard]] Object FescriptBodyObjectMemberApplyForceCenter::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_ARRAY("BodyObject.apply_force_center()", 1)
  const auto& arr = std::get<FescriptArrayIndex>(arguments[0]);
  if (arr->get_size() < 2) {
    fresh::log_error(fresh::src(), "RectangleBodyObject.apply_force_center([x, y]): array must be greater than 1");
    return nullptr;
  }
  this->get_self()->apply_force_center(
    fresh::PointResource {
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(0))),
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arr->get_value(1))),
    }
  );
  return nullptr;
}

[[nodiscard]] Object FescriptBodyObjectMemberApplyLinearImpulseCenter::call(Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("BodyObject.apply_linear_impulse_center()", 2)
  this->get_self()->apply_linear_impulse_center(fresh::PointResource {
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[0])),
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[1]))
  });
  return nullptr;
}

[[nodiscard]] Object FescriptBodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto body_object = std::make_shared<fresh::BodyObject>();
  this->_object_id = body_object->get_id();
  return std::move(body_object);
}
} // namespace fescript