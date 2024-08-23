#pragma once

#include "fescript_body_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define POLYGON_BODY_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, PolygonBodyObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(SetIsStaticBody, PolygonBodyObjectMember, 1, fresh::PolygonBodyObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsStaticBody, PolygonBodyObjectMember, 0, fresh::PolygonBodyObject)

class PolygonBodyObjectWrapper : public BodyObjectWrapper {
public:
  PolygonBodyObjectWrapper();
  ~PolygonBodyObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript