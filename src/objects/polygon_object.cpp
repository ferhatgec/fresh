#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/polygon_object.hpp>
#include <freshengine.hpp>
#include <algorithm>

namespace fresh {
PolygonObject::PolygonObject() {
  this->_object_def = "polygonobject";
}

PolygonObject::PolygonObject(PolygonResource resource, ColorResource color)
  : _resource{std::move(resource)}, _color{std::move(color)} {
  this->_object_def = "polygonobject";
}

PolygonObject::~PolygonObject() {
}

void PolygonObject::sync(bool is_sync_with_camera) noexcept {
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  if(this->_disabled)
    return;
  this->_draw_polygon();
  APPLY_DELTAS()
}

void PolygonObject::_draw_polygon() noexcept {
  if(this->_resource.get_is_filled())
    this->_draw_filled_polygon();
  else
    this->_draw_unfilled_polygon();
}

// very slow way to draw polygon, we may do some optimizations here, but for now it's okay for prototype.
// update: SDL2 seems got SDL_RenderGeometry in 2022, we can use it later but we may need to change
// pointresource a bit.
void PolygonObject::_draw_filled_polygon() noexcept {
  this->_add_render_objects(); // what a optimized way! at least we don't do that crap for unfilled polygons.
  auto& vertices = this->get_polygon_resource().get_polygons();

  if(vertices.size() < 3)
    return;

  auto min_y = vertices[0].get_y();
  auto max_y = vertices[0].get_y();

  for(auto& vert: vertices) {
    min_y = std::fminf(vert.get_y(), min_y);
    max_y = std::fmaxf(vert.get_y(), max_y);
  }

  for(auto y = static_cast<std::int32_t>(min_y); y <= max_y; ++y) {
    std::vector<idk::f32> node_x;

    for(std::size_t i = 0; i < vertices.size(); ++i) {
      auto point_1 = vertices[i];
      auto point_2 = vertices[(i + 1) % vertices.size()];

      const auto y_cast = static_cast<idk::f32>(y);

      if (point_1.get_y() < y_cast && point_2.get_y() >= y_cast || point_2.get_y() < y_cast && point_1.get_y() >= y_cast) {
        auto x = point_1.get_x() + (y_cast - point_1.get_y()) * (point_2.get_x() - point_1.get_x()) / (point_2.get_y() - point_1.get_y());
        node_x.push_back(x);
      }
    }
    std::sort(node_x.begin(), node_x.end());

    for(std::size_t i = 0; i < node_x.size(); i += 2) {
      if(i + 1 < node_x.size()) {
        const auto y_cast = static_cast<idk::f32>(y);
        SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(), node_x[i] + this->get_render_position_info().x,
          y_cast + this->get_render_position_info().y, node_x[i + 1] + this->get_render_position_info().x, y_cast + this->get_render_position_info().y);
      }
    }
  }
  this->_sub_render_objects();
}

void PolygonObject::_draw_unfilled_polygon() noexcept {
  const auto& vertices_size = this->_resource.get_polygons().size();
  const auto& render_pos = this->get_render_position_info();

  SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                         this->_color.get_red(),
                         this->_color.get_green(),
                         this->_color.get_blue(),
                         this->_color.get_alpha());
  for(std::size_t i = 0; i < vertices_size; ++i) {
    const std::size_t j = (i + 1) % vertices_size;
    SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(),
                        this->_resource.get_polygons()[i].get_x() + render_pos.x,
                        this->_resource.get_polygons()[i].get_y() + render_pos.y,
                        this->_resource.get_polygons()[j].get_x() + render_pos.x,
                        this->_resource.get_polygons()[j].get_y() + render_pos.y);
  }
}

void PolygonObject::_add_render_objects() noexcept {
  const auto& render_pos = this->get_render_position_info();
  for(auto& vert: this->get_polygon_resource().get_polygons()) {
    vert += PointResource(render_pos.x, render_pos.y);
  }
}

void PolygonObject::_sub_render_objects() noexcept {
  const auto& render_pos = this->get_render_position_info();
  for(auto& vert: this->get_polygon_resource().get_polygons()) {
    vert -= PointResource(render_pos.x, render_pos.y);
  }
}

void PolygonObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: PolygonObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

__idk_nodiscard
PolygonResource& PolygonObject::get_polygon_resource() noexcept {
  return this->_resource;
}

__idk_nodiscard
ColorResource& PolygonObject::get_color_resource() noexcept {
  return this->_color;
}

void PolygonObject::set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept {
  if(f32_nearly_equals(this->_rotation_degrees, rad_degrees))
    return;
  this->_last_rotation_degrees = this->_rotation_degrees;
  this->_rotation_degrees = std::fmodf(rad_degrees, mul_2_pi_v<idk::f32>);
  this->get_polygon_resource() = this->get_polygon_resource().rotate(this->_rotation_degrees);
}
} // namespace fresh