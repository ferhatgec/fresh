#include "../../../include/fescript/modules/engine.hpp"
#include "../../../include/render_objects.hpp"
#include "../../../include/objects/sprite_object.hpp"

namespace fescript {
__idk_nodiscard Object FescriptEngineRenderObjectsPush::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(arguments.empty())
    return false;
  for(const auto& argument: arguments) {
    if(argument.index() == FescriptBaseObjectIndex)
      fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptBaseObjectIndex>(argument));
    else if(argument.index() == FescriptSpriteObjectIndex) {
      fresh::RenderObjects::objects_to_render.push_back(std::get<FescriptSpriteObjectIndex>(argument));
    } else {
      std::cout << "Engine [language] error: Some arguments of Engine_render_objects_push() is not inherited from BaseObject.\n";
      std::exit(1);
    }
  }
}
} // namespace fescript