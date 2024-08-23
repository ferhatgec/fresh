#include <fescript/wrappers/physics/fescript_rectangle_body_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <fescript/fescript_array.hpp>

namespace fescript {
__idk_nodiscard Object FescriptRectangleBodyObjectMemberSetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("RectangleBodyObject.set_is_static_body()", 1)
  ERR_CHECK_UNINITIALIZED_AUTO()
  this->_self->set_is_static_body(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptRectangleBodyObjectMemberGetIsStaticBody::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_UNINITIALIZED("RectangleBodyObject.get_is_static_body()")
  return this->_self->get_is_static_body();
}

RectangleBodyObjectWrapper::RectangleBodyObjectWrapper() {
  this->_object_def = "rectanglebodyobject";
}

RectangleBodyObjectWrapper::~RectangleBodyObjectWrapper() {

}

[[nodiscard]] std::string RectangleBodyObjectWrapper::to_string() {
  return "rectanglebodyobject";
}

// RectangleBodyObject(WorldObject, [x, y, w, h], static)
[[nodiscard]] Object RectangleBodyObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_TYPE_AT("RectangleBodyObject()", 0, "worldobject", FescriptWorldObjectIndex)
  ERR_CHECK_TYPE_AT("RectangleBodyObject()", 1, "array", FescriptArrayIndex)
  const auto& rect_arr = std::get<FescriptArrayIndex>(arguments[1]);
  if(rect_arr->get_values().size() < 4) {
    std::cout << "Engine [language] error: RectangleBodyObject(WorldObject, [x, y, w, h] <- \x1b[0;33mMust be 4 arguments there\x1b[0m, static)\n";
    std::exit(1);
  }
  auto rectangle_body_object = std::make_shared<fresh::RectangleBodyObject>(
    std::get<FescriptWorldObjectIndex>(arguments[0])->get_world_id(),
    SDL_FRect {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get(0))), // x
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get(1))), // y
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get(2))), // w
      static_cast<idk::f32>(std::get<LongDoubleIndex>(rect_arr->get(3)))  // h
    },
    arguments.size() == 3 ? std::get<BoolIndex>(arguments[2]) : fresh::BodyObject::IsStaticBodyDefault
  );
  this->_object_id = rectangle_body_object->get_object_id();
  return std::move(rectangle_body_object);
}
} // namespace fescript