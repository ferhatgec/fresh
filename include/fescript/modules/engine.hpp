#pragma once

#include "module_helpers.hpp"
#include "../fescript_class.hpp"
#include "../fescript_callable.hpp"
#include "../../../libs/idk/idk/types/predefined.hpp"

#define ENGINE_MODULE(name, arg_count) DEFINE_MODULE_CLASS(name, Engine, arg_count)

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