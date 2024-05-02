#include "../../../include/fescript/modules/engine.hpp"
#include "../../../include/render_objects.hpp"
#include "../../../include/objects/sprite_object.hpp"
#include "../../../include/objects/label_object.hpp"
#include "../../../include/objects/area_object.hpp"
#include "../../../include/objects/collision_object.hpp"
#include "../../../include/objects/camera_object.hpp"
#include "../../../include/resources/fes_loader_resource.hpp"
#include "../../../include/freshengine.hpp"

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
      case FescriptBaseObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptBaseObjectIndex>(argument));
        break;
      }
      case FescriptSpriteObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptSpriteObjectIndex>(argument));
        break;
      }
      case FescriptLabelObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptLabelObjectIndex>(argument));
        break;
      }
      case FescriptAreaObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptAreaObjectIndex>(argument));
        break;
      }
      case FescriptCollisionObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptCollisionObjectIndex>(argument));
        break;
      }
      case FescriptCameraObjectIndex: {
        fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptCameraObjectIndex>(argument));
        break;
      }
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

//Engine::get_instance()->link_camera
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