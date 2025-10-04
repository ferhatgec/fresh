#include "../include/fescript/fescript_interpreter.hpp"
#include "../include/fescript/fescript_parser.hpp"
#include "../include/fescript/fescript_resolver.hpp"
#include "../include/fescript/fescript_scanner.hpp"
#include "../include/freshengine.hpp"
#include "../include/objects/circle_object.hpp"
#include "../include/objects/physics/circle_area_object.hpp"
#include "../include/objects/physics/polygon_area_object.hpp"
#include "../include/objects/physics/polygon_body_object.hpp"
#include "../include/objects/physics/rectangle_body_object.hpp"
#include "../include/objects/physics/world_object.hpp"
#include "../include/objects/polygon_object.hpp"
#include "../include/resources/circle_resource.hpp"
#include "../include/resources/color_resource.hpp"
#include "objects/physics/circle_body_object.hpp"
#include "objects/rectangle_object.hpp"
#include "objects/point_light_object.hpp"

#include <fstream>
#include <numbers>

#include "objects/audio_player_object.hpp"

class Application : public fresh::Engine {
  fresh::FesLoaderResource _resource;
public:
  Application() noexcept {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.
    Engine::get_instance()->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        800,
                                                        600,
                                                        0,
                                                        0);
    Engine::get_instance()->get_window()->init_window();
    /*
     fresh::RenderObjects::push_object(
      std::make_shared<fresh::RectangleObject>(
        fresh::BBoxResource {-150.f, -150.f, 200.f, 100.f},
        fresh::ColorResource {1.f, 0.f, 0.f, 1.f}
      )
    );

    auto ptr = std::make_shared<fresh::SpriteObject>();
    fresh::SpriteResource resource("gechland.icon.png");

    ptr->get_sprite_resource() = resource;
    ptr->set_position({
      100.f, 100.f, 50.f, 50.f
    });

    fresh::RenderObjects::objects_to_render.back()->push_object(
      ptr
    );

    fresh::PolygonResource res;
    res.push_polygons({{-100.f, -100.f}, {150.f, -100.f}, {75.f, 100.f}, {-100.f, 100.f}});

    fresh::RenderObjects::push_object(
      std::make_shared<fresh::PolygonObject>(res, fresh::ColorResource {1.f, 0.f, 0.f, 1.f})
      );

    fresh::FontResource font_res;
    font_res.set_font_size(64);
    font_res.load_font("Roboto-Regular.ttf");

    fresh::RenderObjects::push_object(
      std::make_shared<fresh::LabelObject>()
    );

    const auto& lbl = std::static_pointer_cast<fresh::LabelObject>(
      fresh::RenderObjects::objects_to_render.back()
      );
    lbl->get_label_font_resource() = font_res;
    lbl->set_position({
      0.f, 0.f,
      1.f, 1.f
    });
    lbl->initialize_text(
      "Hello world",
      fresh::ColorResource {0.f, 0.f, 0.f, 1.f},
      fresh::ColorResource {0.f, 0.f, 0.f, 1.f}
    );

    fresh::RenderObjects::push_object(std::make_shared<fresh::AudioPlayerObject>());
    std::dynamic_pointer_cast<fresh::AudioPlayerObject>(
      fresh::RenderObjects::objects_to_render.back()
    )->get_audio_resource().load_audio_source("digits.wav");
    */

    this->_resource.load_fes("physics_scene.fes");
    FreshInstance->get_light_manager()->get_ambient_light_mutable().set_color(
        glm::vec4 { 0.f, 0.f, 0.f, 1.f }
    );
    // FreshInstance->get_window()->set_clear_color(fresh::ColorResource(0.f, 0.f, 0.f, 1.f));

    fresh::RenderObjects::push_object(std::move(this->_resource.generate()));

  }

  ~Application() noexcept override = default;

  void
  update() override {
    /*if(FreshInstance->get_keyboard_input().is_key_pressed(GLFW_KEY_W)) {
      std::cout << "[W] press\n";
      Engine::get_instance()->get_camera()->get_camera()->set_position(
        Engine::get_instance()->get_camera()->get_camera()->get_camera_position()
        +
        glm::vec3 { 0.f, -0.05f, 0.f }
      );
    }
    if(FreshInstance->get_keyboard_input().is_key_released(GLFW_KEY_W)) {
      std::cout << "[W] release\n";
    }*/
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
  Scanner scanner(source);
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
  if(argc < 2) {
    std::make_unique<Application>()->run();
  } else {
    run(read_file(argv[1]));
  }

  return 0;
}