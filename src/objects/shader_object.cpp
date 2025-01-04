// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <filesystem>
#include <fstream>
#include <objects/shader_object.hpp>
#include <log/log.hpp>
#include <freshengine.hpp>

namespace fresh {
void ShaderObject::init_shader(const std::string& vertex_path, const std::string& fragment_path) noexcept {
  auto& shader_res = FreshInstance->get_cache_shader_resource();
  auto& shader_map = shader_res.get_map();
  const auto& it = shader_res.get_sprite_iter(std::make_pair(vertex_path, fragment_path));
  // shader pair not found
  if(it == shader_map.end()) {
    const bool vert_exists = std::filesystem::exists(vertex_path);
    const bool frag_exists = std::filesystem::exists(fragment_path);

    if(vert_exists && frag_exists) {
      std::string vert_glsl, frag_glsl;
      {
        std::ifstream vert_is(vertex_path), frag_is(fragment_path);

        for(std::string temp; std::getline(vert_is, temp); vert_glsl.append(temp + "\n"))
          ;
        for(std::string temp; std::getline(frag_is, temp); frag_glsl.append(temp + "\n"))
          ;
      }
      this->_shader.initialize(vert_glsl.c_str(), frag_glsl.c_str());
      if(!this->is_shader_initialized()) {
        log_error(src(), "vertex or fragment shader compilation failed; vertex path: '{}', fragment path: '{}'.", vertex_path, fragment_path);
      }
      shader_res.push_overwrite(std::make_pair(vertex_path, fragment_path), ShaderMetadata{.prog = this->_shader});
      return;
    }
    if(!vert_exists) {
      log_error(src(), "vertex shader does not exists in path: '{}'", vertex_path);
    }
    if(!frag_exists) {
      log_error(src(), "fragment shader does not exists in path: '{}'", fragment_path);
    }
    return;
  }
  this->_shader = it->second.prog;
}

void ShaderObject::init_shader(const std::string& key) noexcept {
  this->init_shader(key, key);
}

[[nodiscard]] const fre2d::Shader& ShaderObject::get_shader() const noexcept {
  return this->_shader;
}

[[nodiscard]] fre2d::Shader& ShaderObject::get_shader_mutable() noexcept {
  return this->_shader;
}

[[nodiscard]] bool ShaderObject::is_shader_initialized() const noexcept {
  return this->_shader.get_program_id() != 0;
}
} // namespace fresh