// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <string>
#include <types/predefined.hpp>
#include <texture.hpp>

namespace fresh {
struct SpriteMetadata {
  fre2d::Texture tex;
  idk::i32 width;
  idk::i32 height;
  idk::i32 channels;
};
} // namespace fresh