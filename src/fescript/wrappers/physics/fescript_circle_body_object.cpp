// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/fescript_array.hpp>
#include <objects/physics/polygon_body_object.hpp>

#include <fescript/wrappers/physics/fescript_circle_body_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <objects/physics/world_object.hpp>
#include <ranges>

namespace fescript {
/// CircleBodyObject.set_is_static_body(is_static_body: bool)
[[nodiscard]] Object FescriptCircleBodyObjectMemberSetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("CircleBodyObject().set_is_static_body()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  this->_self->set_is_static_body(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

/// CircleBodyObject.get_is_static_body()
[[nodiscard]] Object FescriptCircleBodyObjectMemberGetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("CircleBodyObject.get_is_static_body()")
  return this->_self->get_is_static_body();
}

/// CircleBodyObject.set_radius(radius: decimal)
[[nodiscard]] Object FescriptCircleBodyObjectMemberSetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("CircleBodyObject.set_radius()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  this->_self->set_radius(static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments.front())));
  return nullptr;
}

/// CircleBodyObject.get_radius()
[[nodiscard]] Object FescriptCircleBodyObjectMemberGetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("CircleBodyObject.get_radius()")
  return static_cast<idk::f80>(this->_self->get_radius());
}

/// CircleBodyObject(WorldObject, [x, y, w, h], r: decimal, static: bool)
[[nodiscard]] Object FescriptCircleBodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_TYPE_AT("CircleBodyObject()", 0, "worldobject", FescriptWorldObjectIndex)
  ERR_CHECK_TYPE_AT("CircleBodyObject()", 1, "array", FescriptArrayIndex)
  ERR_CHECK_TYPE_AT("CircleBodyObject()", 2, "decimal", LongDoubleIndex)
  const auto& rect_arr = std::get<FescriptArrayIndex>(arguments[1]);
  if(rect_arr->get_values().size() < 4) {
    std::cout << "Engine [language] error: CircleBodyObject(WorldObject, \x1b[1;91m[x, y, w, h]\x1b[0m, r: decimal, static: bool):"
                 " given array does not have size 4 for [x, y, w, h].\n";
    std::exit(1);
  }
  auto circle_body_object = std::make_shared<fresh::CircleBodyObject>(
    std::get<FescriptWorldObjectIndex>(arguments[0])->get_world_id(),
    fresh::BBoxResource {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(0))), // x
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(1))), // y
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(2))), // w
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(3)))  // h
    },
    static_cast<idk::f32>(std::get<LongDoubleIndex>(arguments[2])),
    arguments.size() == 4 ? std::get<BoolIndex>(arguments[3]) : fresh::BodyObject::IsStaticBodyDefault
  );
  this->_object_id = circle_body_object->get_id();
  return std::move(circle_body_object);
}
} // namespace fescript