// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_rectangle_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/rectangle_object.hpp>
#include <resources/color_resource.hpp>

namespace fescript {
/// RectangleObject([x, y, w, h], [r, g, b, a], is_filled: bool)
[[nodiscard]] Object FescriptRectangleObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we've removed zero argument RectangleObject initialization; it's because we generate polygon table at initialization;
  // it would be great to add it again, should be not hard to implement (easy with get_position_info and set_position_info).
  ERR_CHECK_TYPE_AT("RectangleObject()", 0, "array", FescriptArrayIndex)
  ERR_CHECK_TYPE_AT("RectangleObject()", 1, "array", FescriptArrayIndex)
  ERR_CHECK_TYPE_AT("RectangleObject()", 2, "bool", BoolIndex)
  // check for rgba input bounds; and convert them into 8-bit unsigned integer.
  static constexpr auto color_min = [](const idk::f80& input) -> idk::u8 {
    if(input > 255.f)
      return 255;
    if(input < 0.f)
      return 0;
    return static_cast<idk::u8>(input);
  };

  const auto& pos_arr = std::get<FescriptArrayIndex>(arguments[0]);
  const auto& color_arr = std::get<FescriptArrayIndex>(arguments[1]);

  if(pos_arr->get_values().size() != 4) {
    std::cout << "Engine [language] error: RectangleObject(\x1b[1;91m[x, y, w, h]x1b[0m, [r, g, b, a], is_filled: bool):"
                 " given array does not have size 4 for [x, y, w, h].\n";
    std::exit(1);
  }
  if(color_arr->get_values().size() != 4) {
    std::cout << "Engine [language] error: RectangleObject([x, y, w, h], \x1b[1;91m[r, g, b, a]\x1b[0m, is_filled: bool):"
                 " given array does not have size 4 for [r, g, b, a].\n";
    std::exit(1);
  }
  auto rectangle_object = std::make_shared<fresh::RectangleObject>(
    fresh::BBoxResource {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::PosXIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::PosYIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::WidthIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get_value(fresh::HeightIndex)))
    },
    fresh::ColorResource(
      color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::RedIndex))),
      color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::GreenIndex))),
      color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::BlueIndex))),
      color_min(std::get<LongDoubleIndex>(color_arr->get_value(fresh::AlphaIndex)))
    ),
    std::get<BoolIndex>(arguments[2])
  );
  this->_object_id = rectangle_object->get_id();
  rectangle_object->init_signal();
  return std::move(rectangle_object);
}
} // namespace fescript