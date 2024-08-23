#define SDL_MAIN_HANDLED
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

#include <fstream>
#include <numbers>

class Application : public fresh::Engine {
private:
  fresh::FesLoaderResource _resource;
  std::shared_ptr<fresh::RectangleBodyObject> _rect_body;
  std::shared_ptr<fresh::WorldObject> _world;
public:
  Application() {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.
    Engine::get_instance()->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        600,
                                                        600,
                                                        SDL_WINDOWPOS_CENTERED,
                                                        SDL_WINDOWPOS_CENTERED);
    Engine::get_instance()->get_window()->init_window();
    Engine::get_instance()->set_scaling_mode(fresh::Engine::Scaling::KeepAspectRatio, 600, 600);
    this->_resource.load_fes("example/box2d_example/physics_scene.fes");
    this->_resource.generate_objects();

    SDL_FRect rect_pos = {
      400.f, 300.f, 200.f, 60.f
    }, rect_pos_2 = {
      400.f, 300.f, 30.f, 30.f
    };

    this->_world = std::make_shared<fresh::WorldObject>();
    this->_rect_body = std::make_shared<fresh::RectangleBodyObject>(this->_world->get_world_id(), rect_pos, true);
    // we attach a circle sprite, so we can actually see what box2d does.
    this->_rect_body->get_sub_objects().push_back(std::make_shared<fresh::RectangleObject>(rect_pos, fresh::ColorResource(0, 0, 0, 125), false));

   //  this->_rect_body->set_rotation_by_radian_degrees(std::numbers::pi_v<idk::f32> / 4.f);

    Engine::get_instance()->get_objects_to_render().push_back(this->_world);
    Engine::get_instance()->get_objects_to_render().push_back(this->_rect_body);
  }

  ~Application() = default;

  SDL_FRect conv_from_rect(const SDL_Rect& rect) {
    return SDL_FRect {
      static_cast<idk::f32>(rect.x),
      static_cast<idk::f32>(rect.y),
      static_cast<idk::f32>(rect.w),
      static_cast<idk::f32>(rect.h)
    };
  }
  void
  update() override {
    if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_U)) {
      this->_rect_body->set_rotation_by_radian_degrees(this->_rect_body->get_rotation_by_radian_degrees() + std::numbers::pi_v<idk::f32> / 36.f);
    }

    if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_J)) {
      this->_rect_body->set_rotation_by_radian_degrees(this->_rect_body->get_rotation_by_radian_degrees() - std::numbers::pi_v<idk::f32> / 36.f);
    }

    if(Engine::get_instance()->get_mouse_input().is_button_just_pressed(SDL_BUTTON_RIGHT)) {
      auto cursor_pos = Engine::get_instance()->get_mouse_input().get_current_coordinates();
      SDL_FRect rect = {
        static_cast<idk::f32>(cursor_pos.first()),
        static_cast<idk::f32>(cursor_pos.second()),
          30,
        30
      }; // TODO: if any camera linked to engine instance, convert to camera render_pos.
      auto box = std::make_shared<fresh::RectangleBodyObject>(this->_world->get_world_id(), rect, false);
      box->get_sub_objects().push_back(std::make_shared<fresh::RectangleObject>(rect, fresh::ColorResource(0, 0, 255, 125), false));
      Engine::get_instance()->get_objects_to_render().push_back(std::move(box));
    }

    if(Engine::get_instance()->get_mouse_input().is_button_just_pressed(SDL_BUTTON_LEFT)) {
      auto cursor_pos = Engine::get_instance()->get_mouse_input().get_current_coordinates();

      SDL_FRect rect = {
        static_cast<idk::f32>(cursor_pos.first()),
        static_cast<idk::f32>(cursor_pos.second()),
          50,
        50
      };
      auto box = std::make_shared<fresh::CircleBodyObject>(this->_world->get_world_id(), rect, 30.f, false);
      box->get_sub_objects().push_back(std::make_shared<fresh::CircleObject>(rect, fresh::CircleResource(30.f, 0, false), fresh::ColorResource(0, 0, 255, 125)));
      Engine::get_instance()->get_objects_to_render().push_back(std::move(box));
    }
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