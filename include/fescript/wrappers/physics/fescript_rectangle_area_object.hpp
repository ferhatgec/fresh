#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define RECTANGLE_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, RectangleAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, RectangleAreaObjectMember, 1, fresh::RectangleAreaObject)

class RectangleAreaObjectWrapper : public AreaObjectWrapper {
public:
  RectangleAreaObjectWrapper();
  ~RectangleAreaObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript