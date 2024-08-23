#include <fescript/wrappers/fescript_rectangle_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/rectangle_object.hpp>
#include <resources/color_resource.hpp>

namespace fescript {
RectangleObjectWrapper::RectangleObjectWrapper() {
  this->_object_def = "rectangleobject";
}

RectangleObjectWrapper::~RectangleObjectWrapper() noexcept {
}

[[nodiscard]] std::string RectangleObjectWrapper::to_string() {
  return "rectangleobject";
}

/// RectangleObject([x, y, w, h], [r, g, b, a], is_filled: bool)
/// RectangleObject()
[[nodiscard]] Object RectangleObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  static constexpr auto color_min = [](const idk::f80& input) -> idk::u8 {
    if(input > 255.f)
      return 255;
    if(input < 0.f)
      return 0;
    return static_cast<idk::u8>(input);
  };

  auto rectangle_object = std::make_shared<fresh::RectangleObject>();

  if(arguments.size() >= 3) {
    ERR_CHECK_TYPE_AT("RectangleObject()", 0, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("RectangleObject()", 1, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("RectangleObject()", 2, "bool", BoolIndex)
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
    rectangle_object->get_raw_position_info() = SDL_FRect {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::PosXIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::PosYIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::WidthIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::HeightIndex)))
    };
    rectangle_object->get_color_resource().get_red() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::RedIndex)));
    rectangle_object->get_color_resource().get_green() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::GreenIndex)));
    rectangle_object->get_color_resource().get_blue() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::BlueIndex)));
    rectangle_object->get_color_resource().get_alpha() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::AlphaIndex)));
    rectangle_object->get_is_filled() = std::get<BoolIndex>(arguments[2]);
  }

  this->_object_id = rectangle_object->get_object_id();
  return std::move(rectangle_object);
}
} // namespace fescript