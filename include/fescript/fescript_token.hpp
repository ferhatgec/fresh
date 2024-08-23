// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <variant>

#include "fescript_token_type.hpp"

enum : std::uint8_t {
  StringIndex,
  LongDoubleIndex,
  BoolIndex,
  NullptrIndex,
  FescriptFunctionIndex,
  FescriptClassIndex,
  FescriptInstanceIndex,
  FescriptArrayIndex,
  FescriptDictIndex,
  FescriptCallableIndex,
  FescriptBaseObjectIndex,
  FescriptSpriteObjectIndex,
  FescriptLabelObjectIndex,
  FescriptAreaObjectIndex,
  FescriptCameraObjectIndex,
  FescriptAnimationPlayerObjectIndex,
  FescriptAnimationFrameObjectIndex,
  FescriptMusicPlayerObjectIndex,
  FescriptAudioPlayerObjectIndex,
  FescriptCircleObjectIndex,
  FescriptPolygonObjectIndex,
  FescriptRectangleObjectIndex,
  FescriptRectangleAreaObjectIndex,
  FescriptCircleAreaObjectIndex,
  FescriptPolygonAreaObjectIndex,
  FescriptWorldObjectIndex,
  FescriptBodyObjectIndex,
  FescriptRectangleBodyObjectIndex,
  FescriptCircleBodyObjectIndex,
  FescriptPolygonBodyObjectIndex
};

namespace fresh {
class BaseObject;
class SpriteObject;
class LabelObject;
class AreaObject;
class CameraObject;
class AnimationPlayerObject;
class AnimationFrameObject;
class MusicPlayerObject;
class AudioPlayerObject;
class CircleObject;
class PolygonObject;
class RectangleObject;
class RectangleAreaObject;
class CircleAreaObject;
class PolygonAreaObject;
class WorldObject;
class BodyObject;
class RectangleBodyObject;
class CircleBodyObject;
class PolygonBodyObject;
} // namespace fresh

namespace fescript {
class FescriptFunction;
class FescriptClass;
class FescriptInstance;
class FescriptArray;
class FescriptDict;
class FescriptCallable;

using Object =
  std::variant<std::string,
               long double,
               bool,
               std::nullptr_t,
               std::shared_ptr<FescriptFunction>,
               std::shared_ptr<FescriptClass>,
               std::shared_ptr<FescriptInstance>,
               std::shared_ptr<FescriptArray>,
               std::shared_ptr<FescriptDict>,
               std::shared_ptr<FescriptCallable>,
               std::shared_ptr<fresh::BaseObject>,
               std::shared_ptr<fresh::SpriteObject>,
               std::shared_ptr<fresh::LabelObject>,
               std::shared_ptr<fresh::AreaObject>,
               std::shared_ptr<fresh::CameraObject>,
               std::shared_ptr<fresh::AnimationPlayerObject>,
               std::shared_ptr<fresh::AnimationFrameObject>,
               std::shared_ptr<fresh::MusicPlayerObject>,
               std::shared_ptr<fresh::AudioPlayerObject>,
               std::shared_ptr<fresh::CircleObject>,
               std::shared_ptr<fresh::PolygonObject>,
               std::shared_ptr<fresh::RectangleObject>,
               std::shared_ptr<fresh::RectangleAreaObject>,
               std::shared_ptr<fresh::CircleAreaObject>,
               std::shared_ptr<fresh::PolygonAreaObject>,
               std::shared_ptr<fresh::WorldObject>,
               std::shared_ptr<fresh::BodyObject>,
               std::shared_ptr<fresh::RectangleBodyObject>,
               std::shared_ptr<fresh::CircleBodyObject>,
               std::shared_ptr<fresh::PolygonBodyObject>>;

class Token {
public:
  Token(TokenType type, std::string lexeme, Object literal, int line, bool is_variadic = false) noexcept;
  Token(const Token& token) noexcept;
  Token() {}
  ~Token() noexcept;
  [[nodiscard]] std::string to_string() const noexcept;
  [[nodiscard]] static std::string to_string(const Object& object) noexcept;
public:
  TokenType type;
  std::string lexeme;
  Object literal;
  int line;
  bool is_variadic;
};
} // namespace fescript