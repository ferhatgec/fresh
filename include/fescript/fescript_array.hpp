#pragma once

#include "fescript_token.hpp"
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
  friend class fresh::CollisionObject;
  friend class fresh::CameraObject;
public:
  FescriptArray();
  ~FescriptArray();

  [[nodiscard]] Object get(const int index);
  [[nodiscard]] std::string to_string();

  [[nodiscard]]
  std::vector<Object>& get_values() noexcept;
private:
  std::vector<Object> values;
};
}