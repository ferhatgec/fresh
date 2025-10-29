// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <log/log.hpp>
#include <fescript/modules/engine.hpp>

#include <objects/animation/animation_frame_object.hpp>
#include <objects/animation/animation_player_object.hpp>

#include <objects/physics/area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/world_object.hpp>
#include <objects/physics/body_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <objects/physics/polygon_body_object.hpp>

#include <objects/camera_object.hpp>
#include <objects/label_object.hpp>
#include <objects/sprite_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/polygon_object.hpp>
#include <objects/rectangle_object.hpp>

#include <render_objects.hpp>
#include <freshengine.hpp>

#include <resources/fes_loader_resource.hpp>

namespace fescript {
[[nodiscard]] Object FescriptEngineGetObject::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("Engine_get_object()", 1)
  return Interpreter::baseobject_to_fescript_object(
    interpreter.get_parent_object()->get_object_by_path(std::get<StringIndex>(arguments.front()))
    );
}

[[nodiscard]] Object FescriptEngineRenderObjectsPush::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.empty())
    return false;
  for(const auto& argument: arguments) {
    auto ptr = Interpreter::fescript_object_to_baseobject(argument);
    if(!ptr) {
      fresh::log_error(fresh::src(), "argument is invalid.\n");
      return nullptr;
    }
    // TODO: wrap init_signal to fescript BaseObject member function.
    if(!ptr->get_initialized()) {
      ptr->init_signal();
    }
    fresh::RenderObjects::push_object(std::move(ptr));
  }
  return nullptr;
}

[[nodiscard]] Object FescriptEngineLoadFes::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("Engine_load_fes()", 1)
  fresh::FesLoaderResource fes_loader;
  fes_loader.load_fes(std::get<StringIndex>(arguments.front()));
  return std::move(fes_loader.generate());
}

[[nodiscard]] Object FescriptEngineLinkCamera::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.empty()) {
    std::cout << "Engine [language] error: Engine_link_camera() cannot be empty.\n";
    std::exit(1);
  }
  if(arguments.front().index() != FescriptCameraObjectIndex) {
    std::cout << "Engine [language] error: Cannot link object which is not CameraObject.";
    std::exit(1);
  }
  FreshInstance->link_camera(std::get<FescriptCameraObjectIndex>(arguments.front()));
  return nullptr;
}

[[nodiscard]] Object FescriptEngineCalculateFPS::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return FreshInstance->calculate_fps();
}
} // namespace fescript