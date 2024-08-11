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

#define StringIndex 0
#define LongDoubleIndex 1
#define BoolIndex 2
#define NullptrIndex 3
#define FescriptFunctionIndex 4
#define FescriptClassIndex 5
#define FescriptInstanceIndex 6
#define FescriptArrayIndex 7
#define FescriptDictIndex 8
#define FescriptCallableIndex 9
#define FescriptBaseObjectIndex 10
#define FescriptSpriteObjectIndex 11
#define FescriptLabelObjectIndex 12
#define FescriptAreaObjectIndex 13
#define FescriptCollisionObjectIndex 14
#define FescriptCameraObjectIndex 15
#define FescriptAnimationPlayerObjectIndex 16
#define FescriptAnimationFrameObjectIndex 17
#define FescriptMusicPlayerObjectIndex 18
#define FescriptAudioPlayerObjectIndex 19
#define FescriptCircleObjectIndex 20
#define FescriptPolygonObjectIndex 21
#define FescriptRectangleObjectIndex 22
#define FescriptRectangleAreaObjectIndex 23
#define FescriptCircleAreaObjectIndex 24
#define FescriptPolygonAreaObjectIndex 25

namespace fresh {
class BaseObject;
class SpriteObject;
class LabelObject;
class AreaObject;
class CollisionObject;
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
               std::shared_ptr<fresh::CollisionObject>,
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
               std::shared_ptr<fresh::PolygonAreaObject>>;

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