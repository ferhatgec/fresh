#pragma once

#include "fescript_base_object.hpp"
#include "../modules/module_helpers.hpp"

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(GetRadius, CircleObjectMember, 0, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(GetSegments, CircleObjectMember, 0, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(GetIsFilled, CircleObjectMember, 0, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(SetRadius, CircleObjectMember, 1, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(SetSegments, CircleObjectMember, 1, fresh::CircleObject)
DEFINE_MEMBER_MODULE_CLASS(SetIsFilled, CircleObjectMember, 1, fresh::CircleObject)

class CircleObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<CircleObjectWrapper> {
public:
  CircleObjectWrapper();
  ~CircleObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return 0; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript