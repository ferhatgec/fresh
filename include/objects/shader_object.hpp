// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <string>
#include <shader.hpp>

namespace fresh {
class ShaderObject {
public:
  ShaderObject() noexcept = default;
  virtual ~ShaderObject() noexcept = default;

  void init_shader(
    const std::string& vertex_path,
    const std::string& fragment_path
  ) noexcept;

  // used for predefined fre2d shaders where shaders are
  // hardcoded into fre2d source code.
  void init_shader(const std::string& key) noexcept;

  [[nodiscard]] const fre2d::Shader& get_shader() const noexcept;
  [[nodiscard]] fre2d::Shader& get_shader_mutable() noexcept;
  [[nodiscard]] bool is_shader_initialized() const noexcept;
protected:
  fre2d::Shader _shader;
};
} // namespace fresh