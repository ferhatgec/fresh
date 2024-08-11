#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>
#include <objects/polygon_object.hpp>
#include <freshengine.hpp>
#include <algorithm>

namespace fresh {
PolygonObject::PolygonObject() {
}

PolygonObject::PolygonObject(PolygonResource resource, ColorResource color)
  : _resource{std::move(resource)}, _color{std::move(color)} {
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
  if(this->_resource.get_is_filled()) [[likely]]
    this->_draw_filled_polygon();
  else [[unlikely]]
    this->_draw_unfilled_polygon();
}

void PolygonObject::_draw_filled_polygon() noexcept {
  this->_build_edge_resource_table(); // FIXME: build only at first initialization and when vertices changed.
  if(this->_edges.empty())
    return;
  auto y_min = this->_edges[0].get_y_min();
  auto y_max = this->_edges[0].get_y_max();
  for(auto& edge: this->_edges) {
    y_min = std::fmin(y_min, edge.get_y_min());
    y_max = std::fmax(y_max, edge.get_y_max());
  }
  for(auto y = y_min; y <= y_max; ++y) {
    this->_active_edges.erase(std::remove_if(this->_active_edges.begin(), this->_active_edges.end(),
                                             [y](EdgeResource& edge) { return edge.get_y_max() <= y; }),
                                             this->_active_edges.end());
    for(auto& edge: this->_edges) {
      if(edge.get_y_min() == y) {
        this->_active_edges.push_back(edge);
      }
    }
    std::sort(this->_active_edges.begin(), this->_active_edges.end(),
              [](EdgeResource& edge_a, EdgeResource& edge_b) { return edge_a.get_x_min() < edge_b.get_x_min(); });
    for(idk::isize i = 0; i < this->_active_edges.size(); i += 2) {
      if(i + 1 < this->_active_edges.size()) {
        const auto x1 = this->_active_edges[i].get_x_min();
        const auto x2 = this->_active_edges[i + 1].get_x_min();
        SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                               this->_color.get_red(),
                               this->_color.get_green(),
                               this->_color.get_blue(),
                               this->_color.get_alpha());
        SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(), x1, y, x2, y);
      }
    }
    for(auto& active_edge: this->_active_edges) {
      active_edge.get_x_min() += active_edge.get_slope();
    }
  }
  this->_active_edges.clear();
}

void PolygonObject::_draw_unfilled_polygon() noexcept {
  const auto vertices_size = this->_resource.get_polygons().size();
  SDL_SetRenderDrawColor(Engine::get_instance()->get_window()->get_renderer(),
                         this->_color.get_red(),
                         this->_color.get_green(),
                         this->_color.get_blue(),
                         this->_color.get_alpha());
  for(idk::isize i = 0; i < vertices_size; ++i) {
    const idk::isize j = (i + 1) % vertices_size;
    SDL_RenderDrawLineF(Engine::get_instance()->get_window()->get_renderer(),
                        this->_resource.get_polygons()[i].get_x(),
                        this->_resource.get_polygons()[i].get_y(),
                        this->_resource.get_polygons()[j].get_x(),
                        this->_resource.get_polygons()[j].get_y());
  }
}

void PolygonObject::_build_edge_resource_table() noexcept {
  this->_edges.clear();
  const auto vertices_size = this->_resource.get_polygons().size();
  for(idk::isize i = 0; i < vertices_size; ++i) {
    const auto j = (i + 1) % vertices_size;
    if(this->_resource.get_polygons()[i].get_y() != this->_resource.get_polygons()[j].get_y()) {
      this->_edges.emplace_back(this->_resource.get_polygons()[i].get_y(),
                                this->_resource.get_polygons()[j].get_y(),
                                this->_resource.get_polygons()[i].get_x(),
                                this->_resource.get_polygons()[j].get_x());
    }
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
} // namespace fresh