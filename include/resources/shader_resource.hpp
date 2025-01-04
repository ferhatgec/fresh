// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <array>
#include <string>
#include <utility>
#include "cache_resource.hpp"
#include "circle.hpp"
#include "framebuffer.hpp"
#include "label.hpp"
#include "meta_data_resource.hpp"

namespace fresh {
using CacheShaderResource = CacheResource<std::pair<std::string, std::string>, ShaderMetadata>;
using PathShaderPair = CacheShaderResource::KeyValueType;

// do not use these filenames for custom shaders.
static const std::string circle_shader_key = "fresh::default::circle_shaders";
static const std::string framebuffer_shader_key = "fresh::default::framebuffer_shaders";
static const std::string label_shader_key = "fresh::default::label_shaders";
static const std::string generic_shader_key = "fresh::default::generic_shaders";

void init_cache_shader_map() noexcept;

static inline const std::array default_shaders = {
  std::pair{circle_shader_key, std::pair{fre2d::detail::circle::default_vertex, fre2d::detail::circle::default_fragment}},
  std::pair{framebuffer_shader_key, std::pair{fre2d::detail::framebuffer::default_vertex, fre2d::detail::framebuffer::default_fragment}},
  std::pair{label_shader_key, std::pair{fre2d::detail::label::default_vertex, fre2d::detail::label::default_fragment}},
  std::pair{generic_shader_key, std::pair{fre2d::detail::shader::default_vertex, fre2d::detail::shader::default_fragment}}
};
} // namespace fresh