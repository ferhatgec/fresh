#define SDL_MAIN_HANDLED
#define __FRESH_ENABLE_EDITOR
#include "../include/editor/editor.hpp"
constexpr auto _speed = 5;
constexpr auto _maximum_speed = 10;

/*class Application : public fresh::Engine {
private:
  fresh::FesLoaderResource _resource;
  std::shared_ptr<fresh::CameraObject> obj;
 /* fresh::SpriteObject* _icon;
  fresh::LabelObject* _font;
  fresh::SpriteObject* _test;
  fresh::SpriteObject* _test2;
  fresh::SpriteObject* _test3;


  fresh::CameraObject* _camera_object;

  fresh::AreaObject* _collision_detection_1,
                   * _collision_detection_2;

  fresh::CollisionObject* _collision_obj;

  fresh::AnimatedSpriteResource _animation_of_gech;
  fresh::AnimationPropertyResource<bool, fresh::SpriteObject> _gech_visible;

  //  fresh::AnimationResource<fresh::SpriteObject*> _animation_of_gech;

  fresh::SpriteResource _cursor_resource;
  fresh::FontResource _font_resource;
  fresh::AudioResource _audio_resource;
  fresh::AudioResource _audio_resource_2;
  fresh::AnimationKeyResource<bool, fresh::SpriteObject> key_resource_1_visible;
  fresh::AnimationKeyResource<bool, fresh::SpriteObject> key_resource_2_visible;

  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> key_resource_1;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> key_resource_2;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> key_resource_3;


  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> character_anim_1;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> character_anim_2;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> character_anim_3;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> character_anim_4;
  fresh::AnimationKeyResource<fresh::SpriteResource, fresh::SpriteObject> character_anim_5;


  fresh::SpriteObject* character_sprite_1;
  fresh::SpriteObject* character_sprite_2;
  fresh::SpriteObject* character_sprite_3;
  fresh::SpriteObject* character_sprite_4;
  fresh::SpriteObject* character_sprite_5;


  bool is_pressed_a { false };

  SDL_Rect dest {
      .x = 100,
      .y = 100,
      .w = 100,
      .h = 50
  };
public:
  Application() {
    FreshInstanceInit(); // this is a *must* to initialize every part of engine correct.

    Engine::get_instance()->get_window() = std::make_shared<fresh::Window>("Hello world",
                                                        800,
                                                        600,
                                                        SDL_WINDOWPOS_CENTERED,
                                                        SDL_WINDOWPOS_CENTERED);

    Engine::get_instance()->get_window()->init_window(); // initialize window first.
    if(!Engine::get_instance()->get_window()->set_icon("example/icon.png")) {
      std::cout << "Failed to initialize icon.\n";
    }

        Engine::get_instance()->get_window()->get_default_clear_color() = {
            .r = 0, .g = 0, .b = 0, .a = 255
        };

    this->_resource.load_fes("example/scene.fes");
    this->_resource.generate_objects();

    //Engine::get_instance()->link_camera(std::dynamic_pointer_cast<fresh::CameraObject>(fresh::RenderObjects::objects_to_render[0]));

   /* std::dynamic_pointer_cast<fresh::GuiButtonObject>(fresh::RenderObjects::objects_to_render[2])
        ->get_button_hover_callback() = []() {
      std::cout << "get_button_hover_callback\n";
    };

    this->obj = std::dynamic_pointer_cast<fresh::CameraObject>(fresh::RenderObjects::objects_to_render.back());
   Engine::get_instance()->link_camera(this->obj);

    /*_cursor_resource.load_resource("example/cursor.png");
    _audio_resource.load_audio_source("example/digits.wav");
    _audio_resource_2.load_audio_source("example/fallfatfroeites.wav");

    _audio_resource.get_audio_volume() = 50;
    _audio_resource_2.get_audio_volume() = 50;

    _audio_resource.play_fade_in_audio(false, 10000);
    _audio_resource_2.play_fade_in_audio(false, 1000);

    _collision_detection_1 = new fresh::AreaObject();
    _collision_detection_2 = new fresh::AreaObject();

    _collision_detection_1->get_position_info().w = 50;
    _collision_detection_1->get_position_info().h = 50;
    _collision_detection_1->get_position_info().x = 100;
    _collision_detection_1->get_position_info().y = 100;

    _collision_detection_2->get_position_info().w = 50;
    _collision_detection_2->get_position_info().h = 50;
    _collision_detection_2->get_position_info().x = 149; // colliding with _collision_detection_1.
    _collision_detection_2->get_position_info().y = 100;
    _collision_obj = new fresh::CollisionObject();

    _collision_obj->get_position_info().w = 50;
    _collision_obj->get_position_info().h = 200;
    _collision_obj->get_position_info().x = 200;
    _collision_obj->get_position_info().y = 10;

    _font = new fresh::LabelObject();

    _font->get_label_font_resource().load_font("example/gch.ttf");
    _font->get_label_font_resource().get_font_size() = 64;

    _font->get_position_info().w = 120;
    _font->get_position_info().h = 30;
    _font->get_position_info().x = 150;
    _font->get_position_info().y = 150;

    _font->initialize_text("Hello guys", SDL_Color {
                                             .r = 255,
                                             .g = 0,
                                             .b = 0,
                                             .a = 255 // ~0.5
                                         }, SDL_Color {
                                            .a = 0
                                         }, fresh::LabelRenderType::Solid);

    Engine::get_instance()->get_cursor_resource().get_cursor_sprite()   = _cursor_resource;
    Engine::get_instance()->get_cursor_resource().get_position_info().w = 68; // cursor image width
    Engine::get_instance()->get_cursor_resource().get_position_info().h = 68; // cursor image height

    _icon = new fresh::SpriteObject();
    _icon->get_sprite_resource().load_resource("example/character.png");
    _icon->get_position_info().w = 1024 / 8;
    _icon->get_position_info().h = 1280 / 8;
    _icon->get_position_info().x = 0;
    _icon->get_position_info().y = 0;

    character_sprite_1 = new fresh::SpriteObject();
    character_sprite_1->get_sprite_resource().load_resource("example/character.png");
    character_sprite_1->get_position_info().w = 1024 / 8; // 1 / 8 ratio scaling
    character_sprite_1->get_position_info().h = 1280 / 8;
    character_sprite_1->get_position_info().x = 0;
    character_sprite_1->get_position_info().y = 0;

    character_sprite_2 = new fresh::SpriteObject();
    character_sprite_2->get_sprite_resource().load_resource("example/character_walk_frame_1.png");
    character_sprite_2->get_position_info().w = 1024 / 8; // 1 / 8 ratio scaling
    character_sprite_2->get_position_info().h = 1280 / 8;
    character_sprite_2->get_position_info().x = 0;
    character_sprite_2->get_position_info().y = 0;

    character_sprite_3 = new fresh::SpriteObject();
    character_sprite_3->get_sprite_resource().load_resource("example/character_walk_frame_2.png");
    character_sprite_3->get_position_info().w = 1024 / 8; // 1 / 8 ratio scaling
    character_sprite_3->get_position_info().h = 1280 / 8;
    character_sprite_3->get_position_info().x = 0;
    character_sprite_3->get_position_info().y = 0;

    character_sprite_4 = new fresh::SpriteObject();
    character_sprite_4->get_sprite_resource().load_resource("example/character_walk_frame_3.png");
    character_sprite_4->get_position_info().w = 1024 / 8; // 1 / 8 ratio scaling
    character_sprite_4->get_position_info().h = 1280 / 8;
    character_sprite_4->get_position_info().x = 0;
    character_sprite_4->get_position_info().y = 0;

    character_sprite_5 = new fresh::SpriteObject();
    character_sprite_5->get_sprite_resource().load_resource("example/character_walk_frame_4.png");
    character_sprite_5->get_position_info().w = 1024 / 8; // 1 / 8 ratio scaling
    character_sprite_5->get_position_info().h = 1280 / 8;
    character_sprite_5->get_position_info().x = 0;
    character_sprite_5->get_position_info().y = 0;

    _test = new fresh::SpriteObject();
    _test->get_sprite_resource().load_resource("example/cursor.png");
    _test->get_position_info().w = 68;
    _test->get_position_info().h = 68;
    _test->get_position_info().x = 0;
    _test->get_position_info().y = 0;

    _test2 = new fresh::SpriteObject();
    _test2->get_sprite_resource().load_resource("example/icon.png");
    _test2->get_position_info().w = 143;
    _test2->get_position_info().h = 143;
    _test2->get_position_info().x = 0;
    _test2->get_position_info().y = 0;

    _test3 = new fresh::SpriteObject();
    _test3->get_sprite_resource().load_resource("example/block.png");
    _test3->get_position_info().w = 300;
    _test3->get_position_info().h = 150;
    _test3->get_position_info().x = 0;
    _test3->get_position_info().y = 0;

    _camera_object = new fresh::CameraObject();
    _camera_object->get_position_info().x = 0;
    _camera_object->get_position_info().y = 0;
    _camera_object->get_position_info().w = 800;
    _camera_object->get_position_info().h = 600;

    //_test->get_position_info().x = 500;
    //_test->get_position_info().y = 400;
    //std::cout << Engine::get_instance()->get_camera()->get_object_id() << '\n';

    // we need to push objects to render_objects first, then call init_animation()
    // because we need to sync _casted_render_objects with render_objects.
    std::cout << fresh::RenderObjects::objects_to_render.size() << '\n';


    Engine::get_instance()->link_camera(this->_camera_object);
    _icon->push_object(dynamic_cast<fresh::BaseObject*>(_camera_object));

    Engine::get_instance()->push_object(dynamic_cast<fresh::BaseObject*>(_icon)); // index 0 -> sync with get_index_in_render_objects() for fast access.
    Engine::get_instance()->push_object(dynamic_cast<fresh::BaseObject*>(_font));
    // Engine::get_instance()->push_object(_test);
    //Engine::get_instance()->push_object(dynamic_cast<fresh::BaseObject*>(_camera_object));
    //Engine::get_instance()->push_object(_collision_detection_1);
    //Engine::get_instance()->push_object(_collision_detection_2);
    //Engine::get_instance()->push_object(_collision_obj);

    std::cout << fresh::RenderObjects::objects_to_render.size() << '\n';

    if(!_icon->get_sprite_resource().get_texture()) {
      std::cout << "What?\n";
      _icon->get_sprite_resource().load_resource("example/icon.png");
    }

    if(!_test->get_sprite_resource().get_texture()) {
      std::cout << "What?\n";
      _test->get_sprite_resource().load_resource("example/icon.png");
    }

    if(!_test2->get_sprite_resource().get_texture()) {
      std::cout << "What?\n";
      _test2->get_sprite_resource().load_resource("example/icon.png");
    }

    _animation_of_gech.init_animation(true);
    _animation_of_gech.sync_render_objects();
    _animation_of_gech.get_index_in_render_objects() = 0; // this is important! index of _icon

    _gech_visible.init_animation(false);
    _gech_visible.sync_render_objects();
    _gech_visible.get_index_in_render_objects() = 0;


    bool _true { true },
         _false { false };

    character_anim_1.get_start_ms() = 0;
    character_anim_1.get_end_ms()   = 40;
    character_anim_1.link_to_key(&character_sprite_1->get_sprite_resource());

    character_anim_2.get_start_ms() = 40;
    character_anim_2.get_end_ms()   = 80;
    character_anim_2.link_to_key(&character_sprite_2->get_sprite_resource());

    character_anim_3.get_start_ms() = 80;
    character_anim_3.get_end_ms()   = 120;
    character_anim_3.link_to_key(&character_sprite_3->get_sprite_resource());

    character_anim_4.get_start_ms() = 120;
    character_anim_4.get_end_ms()   = 160;
    character_anim_4.link_to_key(&character_sprite_4->get_sprite_resource());

    character_anim_5.get_start_ms() = 160;
    character_anim_5.get_end_ms()   = 200;
    character_anim_5.link_to_key(&character_sprite_5->get_sprite_resource());

    key_resource_1_visible.get_start_ms() = 0;
    key_resource_1_visible.get_end_ms()   = 600;
    key_resource_1_visible.link_to_key(&_true);

    key_resource_2_visible.get_start_ms() = 600;
    key_resource_2_visible.get_end_ms()   = 1200;
    key_resource_2_visible.link_to_key(&_false);

    key_resource_1.get_start_ms() = 0;
    key_resource_1.get_end_ms()   = 600;
    key_resource_1.get_object_id()= _icon->get_object_id();   // select which object to change at this range.
    key_resource_1.link_to_key(&_test2->get_sprite_resource()); // you selected id, when timer ticks is between [start, end) range,

    // the object found from object id will change with _test object.

    key_resource_2.get_start_ms() = 600;
    key_resource_2.get_end_ms()   = 1200;
    key_resource_2.get_object_id()= _icon->get_object_id();
    key_resource_2.link_to_key(&_test->get_sprite_resource());

    key_resource_3.get_start_ms() = 1200;
    key_resource_3.get_end_ms()   = 2000;
    key_resource_3.get_object_id()= _icon->get_object_id();
    key_resource_3.link_to_key(&_test3->get_sprite_resource());

    _animation_of_gech.push_sprite_key(character_anim_1);
    _animation_of_gech.push_sprite_key(character_anim_2);
    _animation_of_gech.push_sprite_key(character_anim_3);
    _animation_of_gech.push_sprite_key(character_anim_4);
    _animation_of_gech.push_sprite_key(character_anim_5);

    _gech_visible.push_sprite_key(key_resource_1_visible);
    _gech_visible.push_sprite_key(key_resource_2_visible);
  }

  ~Application() {
    // we no more need this delete things. all of them will be done under Engine dtor!
/*    delete this->_font;
    delete this->_icon;
    delete this->_collision_detection_1;
    delete this->_collision_detection_2;
  }

  bool _press { false };
  void
  update() override {\
    /*if(Engine::get_mouse_input().is_button_just_pressed(SDL_BUTTON_LEFT)) {
      std::cout << "Mouse left click just pressed and released.\n";
    }

    if(Engine::get_mouse_input().is_button_pressed(SDL_BUTTON_LEFT)) {
      std::cout << "Mouse left click still stays as pressed.\n";
    }

    if(Engine::get_keyboard_input().is_key_pressed(SDL_SCANCODE_A)) {
      std::cout << "A\n";
      this->obj->get_position_info().x -= _speed;
    } else if(Engine::get_keyboard_input().is_key_pressed(SDL_SCANCODE_D)) {
      std::cout << "D\n";
      this->obj->get_position_info().x += _speed;
    } else if(Engine::get_keyboard_input().is_key_pressed(SDL_SCANCODE_W)) {
      std::cout << "W\n";
      this->obj->get_position_info().y -= _speed;
    } else if(Engine::get_keyboard_input().is_key_pressed(SDL_SCANCODE_S)) {
      std::cout << "S\n";
      this->obj->get_position_info().y += _speed;
    }

/*    _icon->sync(); // we will do it from engine later, but we have not any scene currently. -> we did it lmao
    _font->sync();
    _collision_detection_1->sync(); // no need for sync for this time actually but it's better than forgetting it.
    _collision_detection_2->sync();


    //_gech_visible.run_animation();
/*
    if(!_animation_of_gech.get_timer_resource().is_started()) {

    }

    //std::cout << std::boolalpha << "CollisionDetection1: " <<
     //   _collision_detection_1->is_colliding_with(this->_collision_detection_2) << '\n';

    std::cout << std::boolalpha << "IsVisibleOnCamera: " <<
        _camera_object->is_visible_on_camera(this->_icon) << '\n';
    _animation_of_gech.run_animation();
    if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_D)) {
      this->_icon->get_position_info().x += _speed;
      this->_camera_object->get_position_info().x -= _speed;

      std::cout << "Pressed and released D.\n";

      if(_press) {
        _audio_resource_2.resume_audio();
        _audio_resource.resume_audio();
      } else {
        _audio_resource_2.pause_audio();
        _audio_resource.pause_audio();
      }
      _press = not _press;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_D)) {
      _animation_of_gech.run_animation();
      this->_icon->get_position_info().x += _speed;
      this->_camera_object->get_position_info().x -= _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_A)) {
      _animation_of_gech.run_animation();
      this->_icon->get_position_info().x -= _speed;
      this->_camera_object->get_position_info().x += _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_A)) {
      _animation_of_gech.run_animation();
      this->_icon->get_position_info().x -= _speed;
      this->_camera_object->get_position_info().x += _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_W)) {
      this->_icon->get_position_info().y += _speed;
      this->_camera_object->get_position_info().y -= _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_W)) {
      this->_icon->get_position_info().y += _speed;
      this->_camera_object->get_position_info().y -= _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_S)) {
      this->_icon->get_position_info().y -= _speed;
      this->_camera_object->get_position_info().y += _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_S)) {
      this->_icon->get_position_info().y -= _speed;
      this->_camera_object->get_position_info().y += _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_H)) {
      this->_camera_object->get_position_info().x += _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_K)) {
      this->_camera_object->get_position_info().x -= _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_U)) {
      this->_camera_object->get_position_info().y -= _speed;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_J)) {
      this->_camera_object->get_position_info().y += _speed;
    }

    if(Engine::get_instance()->get_keyboard_input().is_key_just_pressed(SDL_SCANCODE_T)) {
      this->_icon->get_property<bool>() = !this->_icon->get_property<bool>(); // visible
    }
  }

  void
  init() override {
    std::cout << "First call from Engine::run()\n";
  }

  void
  last() override {
    std::cout << "Last call from Engine::run()\n";
  }
};*/

int main() {
  SDL_SetMainReady();

  fresh::Editor* editor = new fresh::Editor();
  (void)fresh::Engine::get_instance();

  fresh::Editor::_debug_fn = [&]() -> void {

  };

  editor->init();
  editor->update();
  delete editor;

  return 0;
}