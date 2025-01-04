// MIT License
//
// Copyright (c) 2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <resources/shader_resource.hpp>
#include <freshengine.hpp>

namespace fresh {
void init_cache_shader_map() noexcept {
  if(!FreshInstance->get_cache_shader_resource().get_map().empty()) {
    log_warning(src(), "do not call init_cache_shader_map more than once; it's done automatically.");
    return;
  }
  // add predefined shaders into cache before rendering loop.
  for(const auto& [path, shader_data]: default_shaders) {
    ShaderMetadata shd;
    shd.prog.initialize(shader_data.first, shader_data.second);
    FreshInstance->get_cache_shader_resource().push_overwrite(
      std::make_pair(path, path),
      shd
    );
  }
}
} // namespace fresh