// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/physics/fescript_body_object.hpp>
#include <objects/physics/body_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptBodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto body_object = std::make_shared<fresh::BodyObject>();
  this->_object_id = body_object->get_id();
  return std::move(body_object);
}
} // namespace fescript