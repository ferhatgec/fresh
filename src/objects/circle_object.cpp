#include <objects/circle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
CircleObject::CircleObject() {
}

CircleObject::CircleObject(CircleResource resource, ColorResource color)
  : _resource{std::move(resource)}, _color{std::move(color)} {
}

CircleObject::~CircleObject() noexcept {
}

void CircleObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  if(this->_disabled)
    return;
  this->_draw_circle();
  APPLY_DELTAS()
}

[[nodiscard]] void CircleObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: CircleObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
CircleResource& CircleObject::get_circle_resource() noexcept {
  return this->_resource;
}

__idk_nodiscard
ColorResource& CircleObject::get_color_resource() noexcept {
  return this->_color;
}

void CircleObject::_draw_circle() noexcept {
  if(this->_resource.get_radius() <= 0)
    return;
  if(SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                            this->_color.get_red(),
                            this->_color.get_green(),
                            this->_color.get_blue(),
                            this->_color.get_alpha()) != 0) {
    std::cout << "Engine warning: CircleObject::_draw_circle() cannot set drawing color: " << SDL_GetError() << '\n';
    this->_disabled = true;
    return;
  }
  SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                         this->_color.get_red(),
                         this->_color.get_green(),
                         this->_color.get_blue(),
                         this->_color.get_alpha());
  if(this->_resource.get_is_filled()) [[likely]]
    this->_draw_filled_circle();
  else [[unlikely]]
    this->_draw_unfilled_circle();
}

void CircleObject::_draw_filled_circle() noexcept {
  float x = 0.0f;
  float y = this->_resource.get_radius();
  float d = 3.0f - 2.0f * this->_resource.get_radius();
  float centerX = this->_pos_info.x;
  float centerY = this->_pos_info.y;

  while (y >= x) {
    this->_draw_horizontal_line(centerX - x, centerX + x, centerY + y);
    this->_draw_horizontal_line(centerX - y, centerX + y, centerY + x);
    this->_draw_horizontal_line(centerX - x, centerX + x, centerY - y);
    this->_draw_horizontal_line(centerX - y, centerX + y, centerY - x);

    x++;

    if(d > 0.0f) {
      y--;
      d = d + 4.0f * (x - y) + 10.0f;
    } else
      d = d + 4.0f * x + 6.0f;
  }
}

void CircleObject::_draw_unfilled_circle() noexcept {
  idk::f32 x = 0;
  idk::f32 y = this->_resource.get_radius();
  idk::f32 d = 3.0f - 2.0f * this->_resource.get_radius();
  idk::f32 centerX = this->_pos_info.x;
  idk::f32 centerY = this->_pos_info.y;

  while (y >= x) {
    // Draw the eight octants
    this->_draw_single_point(centerX + x, centerY + y);
    this->_draw_single_point(centerX - x, centerY + y);
    this->_draw_single_point(centerX + x, centerY - y);
    this->_draw_single_point(centerX - x, centerY - y);
    this->_draw_single_point(centerX + y, centerY + x);
    this->_draw_single_point(centerX - y, centerY + x);
    this->_draw_single_point(centerX + y, centerY - x);
    this->_draw_single_point(centerX - y, centerY - x);

    x++;

    if (d > 0.0f) {
      y--;
      d = d + 4.0f * (x - y) + 10.0f;
    } else
      d = d + 4.0f * x + 6.0f;
  }
}

void CircleObject::_draw_horizontal_line(idk::f32 x1, idk::f32 x2, idk::f32 y) noexcept {
  SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(), x1, y, x2, y);
}

void CircleObject::_draw_single_point(idk::f32 x, idk::f32 y) noexcept {
  SDL_RenderDrawPointF(Engine::get_instance()->get_window()->get_renderer(), x, y);
}
} // namespace fresh