// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/wrappers/fescript_label_object.hpp>
#include <objects/label_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptLabelObjectMemberInitFont::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: LabelObject is not initialized, yet using LabelObject.init_font() is not possible.\n";
    std::exit(1);
  }
  if(!arguments.empty()) {
    std::cout << "LabelObject.init_font() must have not take any argument/s.\n";
    std::exit(1);
  }
  this->_self->get_label_font_resource().load_font(this->_self->get_label_font_resource().get_font_path());
  return nullptr;
}

[[nodiscard]] Object FescriptLabelObjectMemberInitText::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: LabelObject is not initialized, yet using LabelObject.init_font() is not possible.\n";
    std::exit(1);
  }
  if(!arguments.empty()) {
    std::cout << "LabelObject.init_font() must have not take any argument/s.\n";
    std::exit(1);
  }
  this->_self->initialize_text(this->_self->get_label_text(),
                               this->_self->get_foreground_color(),
                               this->_self->get_background_color());
  return nullptr;
}

[[nodiscard]] Object FescriptLabelObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto label_object = std::make_shared<fresh::LabelObject>();
  this->_object_id = label_object->get_id();
  return std::move(label_object);
}
} // namespace fescript