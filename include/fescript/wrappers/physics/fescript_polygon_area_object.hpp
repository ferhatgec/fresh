#pragma once

#include "fescript_area_object.hpp"
#include <fescript/modules/module_helpers.hpp>

#define POLYGON_AREA_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, PolygonAreaObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(IsCollidingWith, PolygonAreaObjectMember, 1, fresh::PolygonAreaObject)
DEFINE_MEMBER_MODULE_CLASS(PushPolygon, PolygonAreaObjectMember, 2, fresh::PolygonAreaObject)
DEFINE_MEMBER_MODULE_CLASS(DeleteAllPolygons, PolygonAreaObjectMember, 0, fresh::PolygonAreaObject)

class PolygonAreaObjectWrapper : public AreaObjectWrapper {
public:
  PolygonAreaObjectWrapper();
  ~PolygonAreaObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript