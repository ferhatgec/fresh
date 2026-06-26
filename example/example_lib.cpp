#include "../include/fescript/fescript_interpreter.hpp"
#include "../include/fescript/fescript_parser.hpp"
#include "../include/fescript/fescript_resolver.hpp"
#include "../include/fescript/fescript_scanner.hpp"
#include "../include/freshengine.hpp"
#include "../include/objects/circle_object.hpp"
#include "objects/point_light_object.hpp"
#include "objects/audio_player_object.hpp"
#include <fstream>


class Application : public fresh::Engine {
  fresh::FesLoaderResource _resource;
public:
  Application() noexcept {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.
    FreshInstance->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        800,
                                                        600,
                                                        0,
                                                        0);
    FreshInstance->get_window()->init_window();
    this->_resource.load_fes("physics_scene.fes");
    FreshInstance->get_light_manager()->get_ambient_light_mutable().set_color(
        glm::vec4 { 0.f, 0.f, 0.f, 1.f }
    );
    fresh::RenderObjects::push_object(std::move(this->_resource.generate()));
  }

  ~Application() noexcept override = default;

  void
  update() override {

  }

  void
  init() override {
    fresh::log_info(fresh::src(), "First call from Application::run()\n");
  }

  void
  last() override {
    fresh::log_info(fresh::src(), "Last call from Application::run()\n");
  }
};

[[nodiscard]] std::string read_file(std::string_view path) noexcept {
  std::ifstream file(path.data());
  if(!file)
    return "IO_println(\"failed to open file\");";
  std::string contents;
  for(std::string temp; std::getline(file, temp); contents.append(temp + "\n"))
    ;
  file.close();
  return contents;
}

void run(std::string_view source, fescript::Interpreter& interpreter) noexcept {
  using namespace fescript;

  Scanner scanner(source);
  const auto& tokens = scanner.scan_tokens();
  Parser parser(tokens);
  auto statements = parser.parse();
  if (had_error || had_runtime_error)
    return;
  Resolver resolver{interpreter};
  resolver.resolve(statements);
  if (had_error || had_runtime_error)
    return;
  interpreter.interpret(statements);
}

// you can use this example as fescript interpreter, just pass the script path.
int main(int argc, char** argv) {
  if(argc < 2) {
    std::make_unique<Application>()->run();
  } else {
    fescript::Interpreter interpreter;
    run(read_file(argv[1]), interpreter);
  }

  return 0;
}