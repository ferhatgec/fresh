#include <objects/rectangle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
RectangleObject::RectangleObject(bool is_filled)
  : _is_filled(is_filled) {
}

RectangleObject::RectangleObject(SDL_FRect info, ColorResource color, bool is_filled)
  : _color{std::move(color)}, _is_filled(is_filled) {
  this->_pos_info = info;
}

void RectangleObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_disabled || !this->_visible)
    return;
  SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                         this->get_color_resource().get_red(),
                         this->get_color_resource().get_green(),
                         this->get_color_resource().get_blue(),
                         this->get_color_resource().get_alpha());
  if(this->get_is_filled()) {
    SDL_RenderFillRectF(Engine::get_instance()->get_window()->get_renderer(),
                        &this->_render_pos_info);
  } else {
    SDL_RenderDrawRectF(Engine::get_instance()->get_window()->get_renderer(),
                        &this->_render_pos_info);
  }
  APPLY_DELTAS()
}

void RectangleObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: RectangleObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
ColorResource& RectangleObject::get_color_resource() noexcept {
  return this->_color;
}

__idk_nodiscard
bool& RectangleObject::get_is_filled() noexcept {
  return this->_is_filled;
}
} // namespace fresh