#include <objects/circle_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <freshengine.hpp>

namespace fresh {
CircleObject::CircleObject(SDL_FRect info, CircleResource resource, ColorResource color)
  : _resource{std::move(resource)}, _color{std::move(color)} {
  this->_pos_info = info;
  if(this->get_circle_resource().get_is_filled() && this->get_circle_resource().get_segments() > 0) {
    std::cout << "Engine info: Segments are only for unfilled circles. So, segments are reset to 0\n";
    this->get_circle_resource().get_segments() = 0;
  }
}

void CircleObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_disabled || !this->_visible)
    return;
  this->_draw_circle();
  APPLY_DELTAS()
}

void CircleObject::set(const fescript::Token& name, fescript::Object value) {
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
  if(const auto& radius = this->_resource.get_radius();
    (radius < 0.f) || f32_nearly_equals(radius, 0.f))
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

  if(f32_nearly_equals(this->get_circle_resource().get_segments(), 0.f)) {
    idk::f32 x = this->get_circle_resource().get_radius();
    idk::f32 y { 0.f };
    idk::f32 p = 1.f - this->get_circle_resource().get_radius();
    const auto& render_pos = this->get_render_position_info();

    if(this->get_circle_resource().get_is_filled()) {
      while((x > y) || f32_nearly_equals(x, y)) {
        this->_draw_horizontal_line(render_pos.x - x, render_pos.x + x, render_pos.y + y);
        this->_draw_horizontal_line(render_pos.x - y, render_pos.x + y, render_pos.y + x);
        this->_draw_horizontal_line(render_pos.x - x, render_pos.x + x, render_pos.y - y);
        this->_draw_horizontal_line(render_pos.x - y, render_pos.x + y, render_pos.y - x);

        ++y;

        if((p < 0.f) || f32_nearly_equals(p, 0.f)) {
          p += 2.f * y + 1.f;
        } else {
          --x;
          p += 2.f * (y - x) + 1.f;
        }
      }
    } else {
      while((x > y) || f32_nearly_equals(x, y)) {
        this->_draw_single_point(render_pos.x + x, render_pos.y - y);
        this->_draw_single_point(render_pos.x + x, render_pos.y + y);
        this->_draw_single_point(render_pos.x - x, render_pos.y - y);
        this->_draw_single_point(render_pos.x - x, render_pos.y + y);
        this->_draw_single_point(render_pos.x + y, render_pos.y - x);
        this->_draw_single_point(render_pos.x + y, render_pos.y + x);
        this->_draw_single_point(render_pos.x - y, render_pos.y - x);
        this->_draw_single_point(render_pos.x - y, render_pos.y + x);

        ++y;

        if((p < 0.f) || f32_nearly_equals(p, 0.f)) {
          p += 2.f * y + 1.f;
        } else {
          --x;
          p += 2.f * (y - x) + 1.f;
        }
      }
    }
  } else {
    this->_draw_unfilled_circle();
  }
}

// this uses segments so trig functions which is slow when segments are large.
void CircleObject::_draw_unfilled_circle() noexcept {
  // Use segment-based approach
  const auto& seg = this->get_circle_resource().get_segments();
  const auto& rad = this->get_circle_resource().get_radius();
  const auto& xc = this->get_render_position_info().x;
  const auto& yc = this->get_render_position_info().y;

  idk::f32 angle_step = 2.f * idk::pi / static_cast<idk::f32>(seg);

  for(std::size_t i = 0; i < seg; i++) {
    const idk::f32 angle = static_cast<idk::f32>(i) * angle_step;
    this->_draw_single_point(xc + rad * Engine::get_instance()->cos(angle), yc + rad * Engine::get_instance()->sin(angle));
  }
}

void CircleObject::_draw_horizontal_line(idk::f32 x1, idk::f32 x2, idk::f32 y) noexcept {
  SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(), x1, y, x2, y);
}

void CircleObject::_draw_single_point(idk::f32 x, idk::f32 y) noexcept {
  SDL_RenderDrawPointF(Engine::get_instance()->get_window()->get_renderer(), x, y);
}
} // namespace fresh