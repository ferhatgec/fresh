#include <freshengine.hpp>

namespace fresh {
GuiButtonObject::GuiButtonObject() {
  this->_base_object = std::make_shared<GuiBaseObject>();
  this->_object_def = "guibuttonobject";
  this->_sprite_object = std::make_shared<SpriteObject>();
  this->_on_clicked_sprite_object = std::make_shared<SpriteObject>();
  this->_on_hover_sprite_object = std::make_shared<SpriteObject>();

  this->_label_object = std::make_shared<LabelObject>();
  this->_on_clicked_label_object = std::make_shared<LabelObject>();
  this->_on_hover_label_object = std::make_shared<LabelObject>();
}

GuiButtonObject::~GuiButtonObject() {
}

__idk_nodiscard
  std::function<void()>&
  GuiButtonObject::get_button_clicked_callback() noexcept {
  return this->_button_clicked;
}

__idk_nodiscard
  std::function<void()>&
  GuiButtonObject::get_button_hover_callback() noexcept {
  return this->_button_hover;
}

__idk_nodiscard
  std::shared_ptr<LabelObject>&
  GuiButtonObject::get_label_object() noexcept {
  return this->_label_object;
}

__idk_nodiscard
  std::shared_ptr<LabelObject>&
  GuiButtonObject::get_on_clicked_label_object() noexcept {
  return this->_on_clicked_label_object;
}

__idk_nodiscard
  std::shared_ptr<LabelObject>&
  GuiButtonObject::get_on_hover_label_object() noexcept {
  return this->_on_hover_label_object;
}

__idk_nodiscard
  std::shared_ptr<SpriteObject>&
  GuiButtonObject::get_sprite_object() noexcept {
  return this->_sprite_object;
}

__idk_nodiscard
  std::shared_ptr<SpriteObject>&
  GuiButtonObject::get_on_clicked_sprite_object() noexcept {
  return this->_on_clicked_sprite_object;
}

__idk_nodiscard
  std::shared_ptr<SpriteObject>&
  GuiButtonObject::get_on_hover_sprite_object() noexcept {
  return this->_on_hover_sprite_object;
}

void GuiButtonObject::sync(bool is_sync_with_camera) noexcept {
  this->_base_object->get_position_info() = this->_pos_info;

  // sorry for that but i don't think there is any better way. if there, please let me know thank you
  this->get_on_clicked_sprite_object()->get_position_info().x += this->_base_object->delta_x();
  this->get_on_clicked_sprite_object()->get_position_info().y += this->_base_object->delta_y();
  this->get_on_clicked_sprite_object()->get_position_info().w += this->_base_object->delta_w();
  this->get_on_clicked_sprite_object()->get_position_info().h += this->_base_object->delta_h();

  this->get_on_clicked_label_object()->get_position_info().x += this->_base_object->delta_x();
  this->get_on_clicked_label_object()->get_position_info().y += this->_base_object->delta_y();
  this->get_on_clicked_label_object()->get_position_info().w += this->_base_object->delta_w();
  this->get_on_clicked_label_object()->get_position_info().h += this->_base_object->delta_h();

  this->get_on_hover_sprite_object()->get_position_info().x += this->_base_object->delta_x();
  this->get_on_hover_sprite_object()->get_position_info().y += this->_base_object->delta_y();
  this->get_on_hover_sprite_object()->get_position_info().w += this->_base_object->delta_w();
  this->get_on_hover_sprite_object()->get_position_info().h += this->_base_object->delta_h();

  this->get_on_hover_label_object()->get_position_info().x += this->_base_object->delta_x();
  this->get_on_hover_label_object()->get_position_info().y += this->_base_object->delta_y();
  this->get_on_hover_label_object()->get_position_info().w += this->_base_object->delta_w();
  this->get_on_hover_label_object()->get_position_info().h += this->_base_object->delta_h();

  if(this->_base_object->is_mouse_hover()) {
    if(Engine::get_instance()->get_mouse_input().is_button_pressed(SDL_BUTTON_LEFT)) {
      if(std::shared_ptr<SpriteObject>& _ref_on_clicked_sprite_obj = this->get_on_clicked_sprite_object(); _ref_on_clicked_sprite_obj.get()) {
        this->_sprite_object.swap(_ref_on_clicked_sprite_obj);

        if(std::shared_ptr<LabelObject>& _ref_on_clicked_label_obj = this->get_on_clicked_label_object(); _ref_on_clicked_label_obj.get())
          this->_label_object.swap(_ref_on_clicked_label_obj);
      } else if(std::shared_ptr<LabelObject>& _ref_on_clicked_label_obj = this->get_on_clicked_label_object(); _ref_on_clicked_label_obj.get())
        this->_label_object.swap(_ref_on_clicked_label_obj);

      this->get_button_clicked_callback()();
      this->_sprite_object->sync(is_sync_with_camera);
      this->_label_object->sync(is_sync_with_camera);

      if(std::shared_ptr<SpriteObject>& _ref_sprite_obj = this->_sprite_object; _ref_sprite_obj.get()) {
        _ref_sprite_obj.swap(this->get_on_clicked_sprite_object());

        if(std::shared_ptr<LabelObject>& _ref_label_obj = this->_label_object; _ref_label_obj.get())
          _ref_label_obj.swap(this->get_on_clicked_label_object());
      } else if(std::shared_ptr<LabelObject>& _ref_label_obj = this->_label_object; _ref_label_obj.get())
        _ref_label_obj.swap(this->get_on_clicked_label_object());
    } else {
      if(std::shared_ptr<SpriteObject>& _ref_on_hover_sprite_obj = this->get_on_hover_sprite_object(); _ref_on_hover_sprite_obj.get()) {
        this->_sprite_object.swap(_ref_on_hover_sprite_obj);

        if(std::shared_ptr<LabelObject>& _ref_on_hover_label_obj = this->get_on_hover_label_object(); _ref_on_hover_label_obj.get())
          this->_label_object.swap(_ref_on_hover_label_obj);
      } else if(std::shared_ptr<LabelObject>& _ref_on_hover_label_obj = this->get_on_hover_label_object(); _ref_on_hover_label_obj.get())
        this->_label_object.swap(_ref_on_hover_label_obj);

      this->get_button_hover_callback()();
      this->_sprite_object->sync(is_sync_with_camera);
      this->_label_object->sync(is_sync_with_camera);

      if(std::shared_ptr<SpriteObject>& _ref_sprite_obj = this->_sprite_object; _ref_sprite_obj.get()) {
        _ref_sprite_obj.swap(this->get_on_hover_sprite_object());

        if(std::shared_ptr<LabelObject>& _ref_label_obj = this->_label_object; _ref_label_obj.get())
          _ref_label_obj.swap(this->get_on_hover_label_object());
      } else if(std::shared_ptr<LabelObject>& _ref_label_obj = this->_label_object; _ref_label_obj.get())
        _ref_label_obj.swap(this->get_on_hover_label_object());
    }

    return;
  }

  this->_sprite_object->sync(is_sync_with_camera);
  this->_label_object->sync(is_sync_with_camera);
}
}// namespace fresh