#include <objects/physics/polygon_body_object.hpp>
#include <objects/camera_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/fescript_array.hpp>

namespace fresh {
// TODO: Box2D uses counter clockwise winding; we need to use clockwise to counter clockwise winding.
PolygonBodyObject::PolygonBodyObject(const b2WorldId& world_id, SDL_FRect pos, PolygonResource vertices, bool is_static_body) {
  this->_world_id = world_id;
  this->_pos_info = pos;
  this->_vertices = vertices;
  this->_is_static_body = is_static_body;
  this->_object_def = "polygonbodyobject";
  this->_create_body();
}

void PolygonBodyObject::sync(bool is_sync_with_camera) noexcept {
  CHECK_DISABLED()
  this->_code.interpret_update();
  this->sync_pos_with_camera(is_sync_with_camera);
  auto position = b2Body_GetPosition(this->_body_id);
  // auto rotation = b2Body_GetRotation(this->_body_id); // TODO: we don't have rotation for BaseObject.
  this->get_position_info() = SDL_FRect { position.x, position.y, this->_pos_info.w, this->_pos_info.h };
  APPLY_DELTAS()
}

void PolygonBodyObject::set(const fescript::Token& name, fescript::Object value) {
  SET_BASE_OBJECT_PROPERTIES()
  else {
    std::cout << "Engine [language] error: PolygonBodyObject has no field named as '" << name.lexeme << "'.\n";
    std::exit(1);
  }
}

void PolygonBodyObject::set_is_static_body(bool is_static_body) noexcept {
  if(this->_is_static_body == is_static_body)
    return;
  b2DestroyBody(this->_body_id);
  this->_body_id = b2_nullBodyId;
  this->_is_static_body = is_static_body;
  this->_create_body();
}

void PolygonBodyObject::_create_body() noexcept {
  b2BodyDef body_def = b2DefaultBodyDef();
  body_def.position.x = this->_pos_info.x;
  body_def.position.y = this->_pos_info.y;
  if(!this->_is_static_body)
    body_def.type = b2_dynamicBody;
  this->_body_id = b2CreateBody(this->_world_id, &body_def);
  auto* points = new b2Vec2[this->_vertices.get_polygons().size()];
  for(std::size_t i = 0; i < this->_vertices.get_polygons().size(); ++i) {
    auto& vert = this->_vertices.get_polygons()[i];
    points[i] = { vert.get_x(), vert.get_y() };
  }

  b2Hull hull = b2ComputeHull(points, static_cast<std::int32_t>(this->_vertices.get_polygons().size()));
  if(hull.count == 0) {
    std::cout << "Engine error: PolygonBodyObject failed to create hull.\n";
    if(points)
      delete points;
    std::exit(1);
  }
  b2Polygon polygon = b2MakePolygon(&hull, 0.f);
  b2ShapeDef shape_def = b2DefaultShapeDef();
  b2CreatePolygonShape(this->_body_id, &shape_def, &polygon);
  if(points)
    delete points;
}
} // namespace fresh