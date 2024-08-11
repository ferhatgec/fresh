#pragma once

#include "module_helpers.hpp"
#include <fescript/fescript_class.hpp>
#include <fescript/fescript_callable.hpp>
#include <types/predefined.hpp>

#define ENGINE_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Engine, arg_count)

#define PUSH_RENDER_OBJECTS_IMPL_OBJECT(object_index) \
case object_index: { \
  fresh::RenderObjects::objects_to_render.push_back(std::get<object_index>(argument)); \
  break; \
}

namespace fescript {
class FescriptEngineGetObject : public FescriptCallable {
public:
  [[nodiscard]] int arity() override { return 1; }
  [[nodiscard]] std::string to_string() override { return "GetObject"; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};

ENGINE_MODULE(RenderObjectsPush, 1)
ENGINE_MODULE(LoadFes, 1)
ENGINE_MODULE(LinkCamera, 1)
} // namespace fescript