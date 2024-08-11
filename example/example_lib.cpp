#define SDL_MAIN_HANDLED
#include "../include/fescript/fescript_interpreter.hpp"
#include "../include/fescript/fescript_parser.hpp"
#include "../include/fescript/fescript_resolver.hpp"
#include "../include/fescript/fescript_scanner.hpp"
#include "../include/freshengine.hpp"
#include "../include/objects/circle_object.hpp"
#include "../include/objects/physics/circle_area_object.hpp"
#include "../include/objects/physics/polygon_area_object.hpp"
#include "../include/objects/polygon_object.hpp"
#include "../include/resources/circle_resource.hpp"
#include "../include/resources/color_resource.hpp"
#include <fstream>

class Application : public fresh::Engine {
private:
  fresh::FesLoaderResource _resource;
public:
  Application() {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.
    Engine::get_instance()->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        800,
                                                        600,
                                                        SDL_WINDOWPOS_CENTERED,
                                                        SDL_WINDOWPOS_CENTERED);
    Engine::get_instance()->get_window()->init_window();
    Engine::get_instance()->set_scaling_mode(fresh::Engine::Scaling::KeepAspectRatio, 800, 600);
    this->_resource.load_fes("example/test/scene.fes");
    this->_resource.generate_objects();
  }

  ~Application() {}

  void
  update() override {
  }

  void
  init() override {
    std::cout << "First call from Application::run()\n";
  }

  void
  last() override {
    std::cout << "Last call from Application::run()\n";
  }
};

using namespace fescript;

[[nodiscard]] std::string read_file(std::string_view path) noexcept {
  std::ifstream file(path.data());
  if(!file)
    return "IO_println(\"failed to open file\");";
  std::string contents;
  for(std::string temp; std::getline(file, temp); contents.append(temp + "\n"))
    ;
  file.close();
  return std::move(contents);
}

Interpreter interpreter;

void run(std::string_view source) noexcept {
  Scanner scanner(std::move(source));
  std::vector<Token> tokens = scanner.scan_tokens();
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

int main(int argc, char** argv) {
  SDL_SetMainReady();

  if(argc < 2) {
    std::make_unique<Application>()->run();
  } else {
    run(read_file(argv[1]));
  }

  return 0;
}