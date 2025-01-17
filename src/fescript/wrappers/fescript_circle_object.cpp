// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_circle_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/circle_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptCircleObjectMemberGetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_radius());
}

[[nodiscard]] Object FescriptCircleObjectMemberGetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->_self->get_circle_resource().get_filled();
}

[[nodiscard]] Object FescriptCircleObjectMemberSetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("CircleObject.set_radius()", 1)
  this->_self->get_circle_resource().set_radius(static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments.front())));
  return nullptr;
}

[[nodiscard]] Object FescriptCircleObjectMemberSetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("CircleObject.set_is_filled()", 1)
  this->_self->get_circle_resource().set_filled(std::get<BoolIndex>(arguments.front()));
  return nullptr;
}

/// CircleObject()
/// CircleObject([x, y, w, h], [r, g, b, a], r: decimal, thickness: decimal, is_filled: bool)
[[nodiscard]] Object FescriptCircleObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  static constexpr auto color_min = [](const idk::f80& input) -> idk::u8 {
    if(input > 255.f)
      return 255;
    if(input < 0.f)
      return 0;
    return static_cast<idk::u8>(input);
  };

  auto circle_object = std::make_shared<fresh::CircleObject>();
  this->_object_id = circle_object->get_id();
  if(arguments.size() >= 5) {
    ERR_CHECK_TYPE_AT("CircleObject()", 0, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 1, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 2, "decimal", LongDoubleIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 3, "decimal", LongDoubleIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 4, "bool", BoolIndex)
    const auto& pos_arr = std::get<FescriptArrayIndex>(arguments[0]);
    const auto& color_arr = std::get<FescriptArrayIndex>(arguments[1]);

    if(pos_arr->get_values().size() != 4) {
      std::cout << "Engine [language] error: CircleObject(\x1b[1;91m[x, y, w, h]\x1b[0m, [r, g, b, a], r: decimal, thickness: decimal, is_filled: bool):"
                   " given array does not have size 4 for [x, y, w, h].\n";
      std::exit(1);
    }
    if(color_arr->get_values().size() != 4) {
      std::cout << "Engine [language] error: CircleObject([x, y, w, h], \x1b[1;91m[r, g, b, a]\x1b[0m, r: decimal, thickness: decimal, is_filled: bool):"
                   " given array does not have size 4 for [r, g, b, a].\n";
      std::exit(1);
    }
    const auto& radius = std::get<LongDoubleIndex>(arguments[2]);
    const auto& thickness = std::get<LongDoubleIndex>(arguments[3]);
    const auto& is_filled = std::get<BoolIndex>(arguments[4]);

    circle_object->set_position(fresh::BBoxResource {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::PosXIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::PosYIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::WidthIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::HeightIndex)))
    });
    circle_object->get_color_resource().set_red(color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::RedIndex))));
    circle_object->get_color_resource().set_green(color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::GreenIndex))));
    circle_object->get_color_resource().set_blue(color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::BlueIndex))));
    circle_object->get_color_resource().set_alpha(color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::AlphaIndex))));
    circle_object->get_circle_resource().set_radius(static_cast<idk::f32>(radius));
    circle_object->get_circle_resource().set_thickness(static_cast<idk::f32>(thickness));
    circle_object->get_circle_resource().set_filled(is_filled);
  }
  return std::move(circle_object);
}
} // namespace fescript