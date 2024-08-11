#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define CIRCLE_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, CircleAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, CircleAreaObjectMember, 1, fresh::CircleAreaObject)
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleAreaObjectMember, 0, fresh::CircleAreaObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleAreaObjectMember, 1, fresh::CircleAreaObject)

class CircleAreaObjectWrapper : public AreaObjectWrapper {
public:
  CircleAreaObjectWrapper();
  ~CircleAreaObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript