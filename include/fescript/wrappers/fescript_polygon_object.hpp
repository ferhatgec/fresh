#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(PushPolygon, PolygonObjectMember, 2, fresh::PolygonObject)
DEFINE_MEMBER_MODULE_CLASS(DeleteAllPolygons, PolygonObjectMember, 0, fresh::PolygonObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsFilled, PolygonObjectMember, 0, fresh::PolygonObject)

//  void push_polygon(idk::f32 x, idk::f32 y) noexcept;
//
//  void delete_all_polygons() noexcept;
//
//  __idk_nodiscard
//  bool& get_is_filled() noexcept;
class PolygonObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<PolygonObjectWrapper> {
public:
  PolygonObjectWrapper();
  ~PolygonObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return 0; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript