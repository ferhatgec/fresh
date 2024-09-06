#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define RECTANGLE_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, RectangleBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, RectangleBodyObjectMember, 1, fresh::RectangleBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, RectangleBodyObjectMember, 0, fresh::RectangleBodyObject)

class RectangleBodyObjectWrapper : public BodyObjectWrapper {
public:
  RectangleBodyObjectWrapper();
  ~RectangleBodyObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript