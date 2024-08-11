#include <fescript/modules/engine.hpp>

#include <objects/animation/animation_frame_object.hpp>
#include <objects/animation/animation_player_object.hpp>

#include <objects/physics/area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>

#include <objects/camera_object.hpp>
#include <objects/collision_object.hpp>
#include <objects/label_object.hpp>
#include <objects/sprite_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/polygon_object.hpp>

#include <render_objects.hpp>
#include <freshengine.hpp>

#include <resources/fes_loader_resource.hpp>

namespace fescript {
[[nodiscard]] Object FescriptEngineGetObject::call(Interpreter &interpreter, std::vector<Object> arguments) {
  ERR_CHECK_STRING("Engine_get_object()", 1)
  // TODO:
  return Interpreter::baseobject_to_fescript_object(
    interpreter.get_parent_object()->get_object_by_path(std::get<StringIndex>(arguments.front()))
    );
}

__idk_nodiscard Object FescriptEngineRenderObjectsPush::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(arguments.empty())
    return false;
  for(const auto& argument: arguments) {
    switch(argument.index()) {
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptBaseObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptSpriteObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptLabelObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptAreaObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptCollisionObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptCameraObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptAnimationPlayerObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptAnimationFrameObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptCircleObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptPolygonObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptRectangleAreaObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptCircleAreaObjectIndex)
      PUSH_RENDER_OBJECTS_IMPL_OBJECT(FescriptPolygonAreaObjectIndex)
      default: {
        std::cout << "Engine [language] error: Some arguments of Engine_render_objects_push() is not inherited from BaseObject.\n";
        std::exit(1);
      }
    }
  }
}

__idk_nodiscard Object FescriptEngineLoadFes::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Engine_load_fes()", 1)
  fresh::FesLoaderResource fes_loader;
  fes_loader.load_fes(std::get<StringIndex>(arguments.front()).data());
  return std::move(fes_loader.return_generated_objects());
}

__idk_nodiscard Object FescriptEngineLinkCamera::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(arguments.empty()) {
    std::cout << "Engine [language] error: Engine_link_camera() cannot be empty.\n";
    std::exit(1);
  }
  if(arguments.front().index() != FescriptCameraObjectIndex) {
    std::cout << "Engine [language] error: Cannot link object which is not CameraObject.";
    std::exit(1);
  }
  fresh::Engine::get_instance()->link_camera(std::get<FescriptCameraObjectIndex>(arguments.front()));
  return nullptr;
}
} // namespace fescript