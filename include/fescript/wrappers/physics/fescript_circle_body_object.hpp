#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define CIRCLE_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, CircleBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, CircleBodyObjectMember, 1, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, CircleBodyObjectMember, 0, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleBodyObjectMember, 0, fresh::CircleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleBodyObjectMember, 1, fresh::CircleBodyObject)

class CircleBodyObjectWrapper : public BodyObjectWrapper {
public:
  CircleBodyObjectWrapper();
  ~CircleBodyObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript