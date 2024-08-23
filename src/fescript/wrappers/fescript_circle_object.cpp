#include <fescript/wrappers/fescript_circle_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/circle_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptCircleObjectMemberGetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_radius());
}

__idk_nodiscard Object FescriptCircleObjectMemberGetSegments::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(this->_self->get_circle_resource().get_segments());
}

__idk_nodiscard Object FescriptCircleObjectMemberGetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return this->_self->get_circle_resource().get_is_filled();
}

__idk_nodiscard Object FescriptCircleObjectMemberSetRadius::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("CircleObject.set_radius()", 1)
  this->_self->get_circle_resource().get_radius() = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptCircleObjectMemberSetSegments::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_DECIMAL("CircleObject.set_segments()", 1)
  this->_self->get_circle_resource().get_segments() = static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments.front()));
  return nullptr;
}

__idk_nodiscard Object FescriptCircleObjectMemberSetIsFilled::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_BOOL("CircleObject.set_is_filled()", 1)
  this->_self->get_circle_resource().get_is_filled() = std::get<BoolIndex>(arguments.front());
  return nullptr;
}

CircleObjectWrapper::CircleObjectWrapper() {
  this->_object_def = "circleobject";
}

CircleObjectWrapper::~CircleObjectWrapper() noexcept {

}

[[nodiscard]] std::string CircleObjectWrapper::to_string() {
  return "circleobject";
}

/// CircleObject()
/// CircleObject([x, y, w, h], [r, g, b, a], r: decimal, is_filled: bool)
[[nodiscard]] Object CircleObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  static constexpr auto color_min = [](const idk::f80& input) -> idk::u8 {
    if(input > 255.f)
      return 255;
    if(input < 0.f)
      return 0;
    return static_cast<idk::u8>(input);
  };

  auto circle_object = std::make_shared<fresh::CircleObject>();
  this->_object_id = circle_object->get_object_id();
  if(arguments.size() >= 4) {
    ERR_CHECK_TYPE_AT("CircleObject()", 0, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 1, "array", FescriptArrayIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 2, "decimal", LongDoubleIndex)
    ERR_CHECK_TYPE_AT("CircleObject()", 3, "bool", BoolIndex)
    const auto& pos_arr = std::get<FescriptArrayIndex>(arguments[0]);
    const auto& color_arr = std::get<FescriptArrayIndex>(arguments[1]);

    if(pos_arr->get_values().size() != 4) {
      std::cout << "Engine [language] error: CircleObject(\x1b[1;91m[x, y, w, h]x1b[0m, [r, g, b, a], r: decimal, is_filled: bool):"
                   " given array does not have size 4 for [x, y, w, h].\n";
      std::exit(1);
    }
    if(color_arr->get_values().size() != 4) {
      std::cout << "Engine [language] error: CircleObject([x, y, w, h], \x1b[1;91m[r, g, b, a]\x1b[0m, r: decimal, is_filled: bool):"
                   " given array does not have size 4 for [r, g, b, a].\n";
      std::exit(1);
    }
    const auto& radius = std::get<LongDoubleIndex>(arguments[2]);
    const auto& is_filled = std::get<BoolIndex>(arguments[3]);

    circle_object->get_raw_position_info() = SDL_FRect {
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::PosXIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::PosYIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::WidthIndex))),
      static_cast<idk::f32>(std::get<LongDoubleIndex>(pos_arr->get(fresh::HeightIndex)))
    };
    circle_object->get_color_resource().get_red() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::RedIndex)));
    circle_object->get_color_resource().get_green() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::GreenIndex)));
    circle_object->get_color_resource().get_blue() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::BlueIndex)));
    circle_object->get_color_resource().get_alpha() = color_min(std::get<LongDoubleIndex>(color_arr->get(fresh::AlphaIndex)));
    circle_object->get_circle_resource().get_radius() = static_cast<idk::f32>(radius);
    circle_object->get_circle_resource().get_is_filled() = is_filled;
  }
  return std::move(circle_object);
}
} // namespace fescript