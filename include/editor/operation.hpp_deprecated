//
// Created by gech on 2/22/2024.
//

#ifndef FRESHENGINE_INCLUDE_EDITOR_OPERATION_HPP
#define FRESHENGINE_INCLUDE_EDITOR_OPERATION_HPP

#include "../fes/fes_keywords.hpp"
#include <types/stringview.hpp>
#include "../../libs/idk/idk/containers/stack.hpp"
#include <string>

namespace fresh {
class EditorOperation {
public:
  friend class Editor;
  friend class EditorOperationHandler;

  EditorOperation();
  ~EditorOperation();

  void
  init_operation(idk::isize group_id,
                 fes::Keywords action_base_object,
                 fes::Keywords changed_variable,
                 const idk::StringViewChar& from,
                 const idk::StringViewChar& to) noexcept;
private:
  idk::isize _group_id;
  fes::Keywords _action_base_object;
  fes::Keywords _changed_variable;

  idk::StringViewChar _from;
  idk::StringViewChar _to;
};

class EditorOperationHandler {
public:
  friend class Editor;

  EditorOperationHandler();
  ~EditorOperationHandler();

  void
  add_operation(const EditorOperation& operation) noexcept;

  void
  add_operation(EditorOperation&& operation) noexcept;

  void
  apply_last_change() noexcept;

  void
  undo_last_change() noexcept;

  __idk_nodiscard
  EditorOperation&
  get_before_push() noexcept;

  void
  clear_before_push() noexcept;

  template<typename Type> void before_push_from_init(fes::Keywords property_type, const Type& from) noexcept { std::cout << "EditorOperationHandler error: Unsupported type.\n"; }
  template<typename Type> void before_push_to_init(const Type& to) noexcept { std::cout << "EditorOperationHandler error: Unsupported type.\n"; }

  template<>
  void before_push_from_init<idk::u32>(fes::Keywords property_type, const idk::u32& from) noexcept {
    if(this->_before_push._from.is_empty() || this->_before_push._changed_variable != property_type) {
      this->_before_push._from = idk::StringViewChar(std::to_string(from).data());
      this->_before_push._changed_variable = property_type;
    }
  }

  template<>
  void before_push_to_init<idk::u32>(const idk::u32& to) noexcept {
    this->_before_push._to = idk::StringViewChar(std::to_string(to).data());
    this->add_operation(fresh::EditorOperation { this->_before_push });
    this->clear_before_push();
  }

  template<> void before_push_from_init<idk::i32>(fes::Keywords property_type, const idk::i32& from) noexcept { this->before_push_from_init<idk::u32>(property_type, abs(from)); }
  template<> void before_push_to_init<idk::i32>(const idk::i32& to) noexcept { this->before_push_to_init<idk::u32>(abs(to)); }

  template<> void before_push_from_init<bool>(fes::Keywords property_type, const bool& from) noexcept { this->before_push_from_init<idk::u32>(property_type, (abs(from) > 0 ? 1 : 0)); }
  template<> void before_push_to_init<bool>(const bool& to) noexcept { this->before_push_to_init<idk::u32>((abs(to) > 0 ? 1 : 0)); }

  template<> void before_push_from_init<idk::StringViewChar>(fes::Keywords property_type, const idk::StringViewChar& from) noexcept {
    if(this->_before_push._from.is_empty() || this->_before_push._changed_variable != property_type) {
      this->_before_push._from = from;
      this->_before_push._changed_variable = property_type;
    }
  }

  template<> void before_push_to_init<idk::StringViewChar>(const idk::StringViewChar& to) noexcept {
    this->_before_push._to = to;
    this->add_operation(fresh::EditorOperation { this->_before_push });
    this->clear_before_push();
  }
private:
  void
  _do_operation(const EditorOperation& operation, bool is_undo_last_change = true) noexcept;

  idk::Stack<EditorOperation> _operations;
  EditorOperation _before_push;
};
}

#endif // FRESHENGINE_INCLUDE_EDITOR_OPERATION_HPP
