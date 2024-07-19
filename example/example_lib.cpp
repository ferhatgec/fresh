#define SDL_MAIN_HANDLED
#define __FRESH_ENABLE_EDITOR
#include <fstream>
#include "../include/editor/editor.hpp"
#include "../include/fescript/fescript_interpreter.hpp"
#include "../include/fescript/fescript_scanner.hpp"
#include "../include/fescript/fescript_parser.hpp"
#include "../include/fescript/fescript_resolver.hpp"

#include <objects/circle_object.hpp>
#include <objects/polygon_object.hpp>
#include <resources/circle_resource.hpp>
#include <resources/color_resource.hpp>

class Application : public fresh::Engine {
private:
  fresh::FesLoaderResource _resource;
  // std::shared_ptr<fresh::AnimationPlayerResource> anim_player;
  std::shared_ptr<fresh::CircleObject> _circle;
  std::shared_ptr<fresh::PolygonObject> _polygon;
public:
  Application() {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.
    Engine::get_instance()->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        800,
                                                        600,
                                                        SDL_WINDOWPOS_CENTERED,
                                                        SDL_WINDOWPOS_CENTERED);
    Engine::get_instance()->get_window()->init_window();
    Engine::get_instance()->set_scaling_mode(fresh::Engine::Scaling::KeepAspectRatio, 1024, 1024);
    // anim_player = std::make_shared<fresh::AnimationPlayerResource>(true);
    this->_resource.load_fes("example/test/scene.fes");
    this->_resource.generate_objects();
    _circle = std::make_shared<fresh::CircleObject>(fresh::CircleResource(150.0f, 30, true),
                                                    fresh::ColorResource(255, 0, 0, 125));
    _circle->get_position_info().x = 100.0f;
    _circle->get_position_info().y = 100.0f;

    fresh::PolygonResource pol_res;
    pol_res.push_polygons({{100.0f, 100.0f}, {200.0f, 100.0f},  {200.0f, 200.0f}, {100.0f, 200.0f}});
    pol_res.get_is_filled() = false;

    _polygon = std::make_shared<fresh::PolygonObject>(pol_res, fresh::ColorResource(255, 126, 126, 120));
    _polygon->get_position_info().x = 120.0f;
    _polygon->get_position_info().y = 120.0f;

    /*fresh::AnimationKeyResourceV2 res(0, 2500,
                                      fresh::RenderObjects::objects_to_render.at(0)->get_sub_objects().at(0),
                                      false,
                                      "visible");
    fresh::AnimationKeyResourceV2 re2(5000, 4500,
                                      fresh::RenderObjects::objects_to_render.at(0)->get_sub_objects().at(0),
                                      true,
                                      "visible");
    anim_player->push_frame(res);
    anim_player->push_frame(re2);
    anim_player->synchronize_frames();*/
  }

  ~Application() {}

  void
  update() override {
    // anim_player->run_animation();
    _circle->sync();
    _polygon->sync();
  }

  void
  init() override {
    std::cout << "First call from Engine::run()\n";
  }

  void
  last() override {
    std::cout << "Last call from Engine::run()\n";
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
    Application* app = new Application();
    app->run();
    if(app)
      delete app;
    return 1;
  }
  run(read_file(argv[1]));
  return 0;
}