//
// Created by gech on 2/6/2024.
//

#ifndef FRESHENGINE_GUI_BASE_OBJECT_HPP
#define FRESHENGINE_GUI_BASE_OBJECT_HPP

#include "../base_object.hpp"
#include <functional>

namespace fresh {
class GuiBaseObject : public BaseObject {
public:
  GuiBaseObject();
  virtual ~GuiBaseObject();

  __idk_nodiscard
  virtual std::function<void()>&
  get_mouse_hover_callback() noexcept;

  __idk_nodiscard
  bool
  is_mouse_hover() noexcept;

  void
  sync() noexcept override;
protected:
  std::function<void()> _mouse_hover_cb = []() -> void {};
};
}

#endif // FRESHENGINE_GUI_BASE_OBJECT_HPP
