// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/physics/fescript_polygon_body_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/polygon_body_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptPolygonBodyObjectMemberSetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("PolygonBodyObject.set_is_static_body()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  this->_self->set_is_static_body(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptPolygonBodyObjectMemberGetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, [[maybe_unused]] const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("PolygonBodyObject.get_is_static_body()")
  return this->_self->get_is_static_body();
}

// PolygonBodyObject(WorldObject, [x, y, w, h], [[]], static)
[[nodiscard]] Object FescriptPolygonBodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we should use inline functions at rock bottom.
  ERR_CHECK_TYPE_AT("RectangleBodyObject()", 0, "worldobject", FescriptWorldObjectIndex)
  ERR_CHECK_TYPE_AT("RectangleBodyObject()", 1, "array", FescriptArrayIndex)
  ERR_CHECK_TYPE_AT("RectangleBodyObject()", 2, "array", FescriptArrayIndex)
  const auto& rect_arr = std::get<FescriptArrayIndex>(arguments[1]);
  if(rect_arr->get_values().size() < 4) {
    std::cout << "Engine [language] error: RectangleBodyObject(WorldObject, [x, y, w, h] <- \x1b[0;33mMust be 4 arguments there\x1b[0m, static)\n";
    std::exit(1);
  }
  // FIXME: we always assume that given arguments are same types. type checking is required.
  const auto& vertices_arr = std::get<FescriptArrayIndex>(arguments[2]);
  fresh::PolygonResource res;
  for(const auto& vertex_arr: vertices_arr->get_values()) {
    const auto& vertex = std::get<FescriptArrayIndex>(vertex_arr);
    res.push_polygon(
      static_cast<idk::f32>(std::get<LongDoubleIndex>(vertex->get_value(0))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(vertex->get_value(1)))
    );
  }
  auto polygon_body_object = std::make_shared<fresh::PolygonBodyObject>(
    std::get<FescriptWorldObjectIndex>(arguments[0])->get_world_id(),
    fresh::BBoxResource {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(0))), // x
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(1))), // y
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(2))), // w
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get_value(3)))  // h
    },
    res,
    arguments.size() == 4 ? std::get<BoolIndex>(arguments[3]) : fresh::BodyObject::IsStaticBodyDefault
  );
  this->_object_id = polygon_body_object->get_id();
  return std::move(polygon_body_object);
}
} // namespace fescript