//
// Created by gech on 2/7/2024.
//

#ifndef FRESHENGINE_GUI_BUTTON_OBJECT_HPP
#define FRESHENGINE_GUI_BUTTON_OBJECT_HPP

#include "gui_base_object.hpp"
#include "../label_object.hpp"
#include "../sprite_object.hpp"

namespace fresh {
class GuiButtonObject : public BaseObject {
public:
  GuiButtonObject();
  virtual ~GuiButtonObject();

  __idk_nodiscard
  std::function<void()>&
  get_button_clicked_callback() noexcept;

  __idk_nodiscard
  std::function<void()>&
  get_button_hover_callback() noexcept;

  __idk_nodiscard
  std::shared_ptr<LabelObject>&
  get_label_object() noexcept;

  __idk_nodiscard
  std::shared_ptr<LabelObject>&
  get_on_clicked_label_object() noexcept;

  __idk_nodiscard
  std::shared_ptr<LabelObject>&
  get_on_hover_label_object() noexcept;

  __idk_nodiscard
  std::shared_ptr<SpriteObject>&
  get_sprite_object() noexcept;

  __idk_nodiscard
  std::shared_ptr<SpriteObject>&
  get_on_clicked_sprite_object() noexcept;

  __idk_nodiscard
  std::shared_ptr<SpriteObject>&
  get_on_hover_sprite_object() noexcept;

  void
  sync() noexcept override;
protected:
  std::function<void()> _button_hover = []() -> void {};
  std::function<void()> _button_clicked = []() -> void {};

  std::shared_ptr<GuiBaseObject> _base_object;
  std::shared_ptr<LabelObject> _label_object;
  std::shared_ptr<LabelObject> _on_clicked_label_object;
  std::shared_ptr<LabelObject> _on_hover_label_object;

  std::shared_ptr<SpriteObject> _sprite_object;
  std::shared_ptr<SpriteObject> _on_clicked_sprite_object;
  std::shared_ptr<SpriteObject> _on_hover_sprite_object;
};
}

#endif // FRESHENGINE_GUI_BUTTON_OBJECT_HPP
