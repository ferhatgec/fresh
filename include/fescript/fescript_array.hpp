#pragma once

#include "fescript_token.hpp"
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <vector>

namespace fescript {
class Array;
class Interpreter;
class FescriptArray : public std::enable_shared_from_this<FescriptArray> {
  friend class Token;
  friend class Parser;
  friend class Interpreter;
  friend class fresh::BaseObject;
  friend class fresh::SpriteObject;
  friend class fresh::LabelObject;
  friend class fresh::AreaObject;
  friend class fresh::RectangleAreaObject;
  friend class fresh::CircleAreaObject;
  friend class fresh::PolygonAreaObject;
  friend class fresh::CollisionObject;
  friend class fresh::CameraObject;
  friend class fresh::AnimationPlayerObject;
  friend class fresh::AnimationFrameObject;
  friend class fresh::MusicPlayerObject;
  friend class fresh::AudioPlayerObject;
  friend class fresh::CircleObject;
  friend class fresh::PolygonObject;
  friend class fresh::RectangleObject;
public:
  FescriptArray();
  ~FescriptArray();

  [[nodiscard]] Object get(const int index);
  [[nodiscard]] std::string to_string();

  [[nodiscard]]
  std::vector<Object>& get_values() noexcept;

  void push_value(Object value) noexcept;
private:
  std::vector<Object> values;
};
}