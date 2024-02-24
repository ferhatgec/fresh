#include "../../include/editor/operation.hpp"
#include "../../include/editor/editor.hpp"

namespace fresh {
EditorOperation::EditorOperation() : _group_id(0),
                                     _action_base_object(fes::Keywords::Undefined),
                                     _changed_variable(fes::Keywords::Undefined),
                                     _from(""),
                                     _to("") {

}

EditorOperation::~EditorOperation() {

}

void EditorOperation::init_operation(idk::isize group_id,
                                     fes::Keywords action_base_object,
                                     fes::Keywords changed_variable,
                                     const idk::StringViewChar& from,
                                     const idk::StringViewChar& to) noexcept {
  this->_group_id = group_id;
  this->_action_base_object = action_base_object;
  this->_changed_variable = changed_variable;
  this->_from = from;
  this->_to = to;
}

EditorOperationHandler::EditorOperationHandler() {

}

EditorOperationHandler::~EditorOperationHandler() {

}

void EditorOperationHandler::add_operation(const fresh::EditorOperation& operation) noexcept {
  if(operation._from != operation._to)
    this->_operations.push(operation);
}

void EditorOperationHandler::add_operation(fresh::EditorOperation&& operation) noexcept {
  if(operation._from != operation._to)
    this->_operations.push(idk::move(operation));
}

void EditorOperationHandler::apply_last_change() noexcept {
  if(this->_operations.is_empty()) {
    std::cout << "EditorOperationHandler info: No more operation available.\n";
    return;
  }

  auto get_data = this->_operations.top();
  this->_operations.pop();

  if(get_data._group_id < 0) {
    std::cout << "EditorOperationHandler error: Group id is invalid.\n";
    return;
  }

  for(auto& render_object: RenderObjects::objects_to_render) {
    if(render_object->get_object_id() == get_data._group_id) {
      this->_do_operation(get_data, false);
      break;
    }
  }
}

void EditorOperationHandler::undo_last_change() noexcept {
  if(this->_operations.is_empty()) {
    std::cout << "EditorOperationHandler info: No more undo available.\n";
    return;
  }

  auto get_data = this->_operations.top();
  this->_operations.pop();

  if(get_data._group_id < 0) {
    std::cout << "EditorOperationHandler error: Group id is invalid.\n";
    return;
  }

  for(auto& render_object: RenderObjects::objects_to_render) {
    if(render_object->get_object_id() == get_data._group_id) {
      this->_do_operation(get_data, true);
      break;
    }
  }
}

__idk_nodiscard
EditorOperation& EditorOperationHandler::get_before_push() noexcept {
  return this->_before_push;
}
void
EditorOperationHandler::clear_before_push() noexcept {
  this->_before_push._from.clear();
  this->_before_push._to.clear();
  this->_before_push._group_id = 0;
  this->_before_push._changed_variable = fes::Keywords::Undefined;
  this->_before_push._action_base_object = fes::Keywords::Undefined; // unnecessary.
}

void
EditorOperationHandler::_do_operation(const EditorOperation& operation, bool is_undo_last_change) noexcept {
  auto& render_object = RenderObjects::objects_to_render[operation._group_id];
  switch(operation._changed_variable) {
  case fes::Keywords::Width: { render_object->get_position_info().w = std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data()); break; }
  case fes::Keywords::Height: { render_object->get_position_info().h = std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data()); break; }
  case fes::Keywords::PositionX: { render_object->get_position_info().x = std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data()); break; }
  case fes::Keywords::PositionY: { render_object->get_position_info().y = std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data()); break; }
  case fes::Keywords::Disabled: { render_object->get_is_disabled() = static_cast<bool>(std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data())); break; }
  case fes::Keywords::Visible: { render_object->get_is_visible() = static_cast<bool>(std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data())); break; }
  case fes::Keywords::LabelText: {
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_text() = is_undo_last_change ? operation._from : operation._to;
    std::dynamic_pointer_cast<LabelObject>(render_object)->initialize_label_font_surface();
    break;
  }
  case fes::Keywords::FontResource: {
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().get_font_path() = is_undo_last_change ? operation._from : operation._to;
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().load_font(std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().get_font_path());
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().sync_font_size();
    std::dynamic_pointer_cast<LabelObject>(render_object)->initialize_label_font_surface();
    break;
  }
  case fes::Keywords::SpriteResource: {
    std::dynamic_pointer_cast<SpriteObject>(render_object)->get_sprite_resource()._texture_path = is_undo_last_change ? operation._from : operation._to;
    std::dynamic_pointer_cast<SpriteObject>(render_object)->get_sprite_resource().load_resource(std::dynamic_pointer_cast<SpriteObject>(render_object)->get_sprite_resource()._texture_path);
    break;
  }
  case fes::Keywords::FontSize: {
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().get_font_size() = abs(std::atoi(is_undo_last_change ? operation._from.data() : operation._to.data()));
    std::dynamic_pointer_cast<LabelObject>(render_object)->get_label_font_resource().sync_font_size();
    std::dynamic_pointer_cast<LabelObject>(render_object)->initialize_label_font_surface();
    break;
  }
  default: {
    std::cout << "EditorOperationHandler error: Invalid or unsupported key change detected.\n";
    break;
  }
  }
}
}