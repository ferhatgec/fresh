#include "../../include/editor/editor.hpp"
#include "../../libs/SDL_image/include/SDL_image.h"
#include "../libs/imgui/backends/imgui_impl_sdl2.h"
#include "../libs/imgui/backends/imgui_impl_sdlrenderer2.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_internal.h"
#include "../libs/imgui/misc/cpp/imgui_stdlib.h"
#include <fstream>

// FIXME: cannot save second fes file that preloaded from project file

namespace fresh {
bool Editor::control_key_pressed { false };
idk::isize Editor::_resource_id{0_isize};
idk::isize Editor::_group_index{0_isize};
idk::isize Editor::_selected_tree_node{0_isize};

SDL_Texture* Editor::_gizmo_y_axis;
SDL_Texture* Editor::_gizmo_x_axis;
SDL_Texture* Editor::_editor_texture;

idk::isize Editor::_editor_focus_group_id;

bool Editor::_first_loop{true};

idk::Vector<idk::StringViewChar> Editor::_code_editor_files{};

idk::StringViewChar Editor::_state = "";

idk::StringViewChar Editor::_fes_file_path = "";
idk::StringViewChar Editor::_fes_save_file_path = "";
idk::StringViewChar Editor::_project_file_path = "";

fes::Keywords Editor::create_object = fes::Keywords::Undefined;
idk::StringViewChar Editor::object_name = "";

idk::StringViewChar Editor::resource_str_1 = "";// used for to assign additional ImGui::InputText datas on it.
idk::StringViewChar Editor::resource_str_2 = "";
idk::i32 Editor::resource_int_1 = 0_i32;

bool Editor::resource_bool_1 = false;
bool Editor::is_open = true;
bool Editor::is_select_scene_open = false;
bool Editor::is_save_scene_open = false;
bool Editor::is_create_project_scene_open = false;
bool Editor::is_open_project_scene_open = false;
bool Editor::is_project_settings_open = false;
bool Editor::is_project_add_scene_open = false;
bool Editor::is_engine_about_scene_open = false;
bool Editor::reload_scene_hierarchy = false;

idk::i32 Editor::object_width = 0_i32;
idk::i32 Editor::object_height = 0_i32;
idk::i32 Editor::object_pos_x = 0_i32;
idk::i32 Editor::object_pos_y = 0_i32;

std::function<void()> Editor::_debug_fn = []() -> void {};// _debug_fn is used in debugging process.
                                                          // so you actually don't need that.
// ImFont* font;

Editor::Editor() {
  FreshInstanceInit();

  Engine::get_instance()->get_window() = std::make_shared<fresh::Window>(
    "freshEngine",
    960,// width & height hardcoded for now
    540, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  Engine::get_instance()->get_window()->init_window();

  if(!Engine::get_instance()->get_window()->set_icon("icon.png")) {
    std::cout << "Editor error: Failed to initialize window icon.\n";
  }

  Engine::get_instance()->get_window()->get_default_clear_color() = {
    .r = 0,
    .g = 192,
    .b = 255,
    .a = 255};

  this->_editor_camera = std::make_shared<CameraObject>();
  this->_editor_camera->get_position_info().x = 0;
  this->_editor_camera->get_position_info().y = 0;
  this->_editor_camera->get_position_info().w =
    Engine::get_instance()->get_window()->_width;
  this->_editor_camera->get_position_info().h =
    Engine::get_instance()->get_window()->_height;

  this->_project_fes_file = std::make_shared<FesLoaderResource>();

  Engine::get_instance()->link_camera(this->_editor_camera);


}

Editor::~Editor() {
  if(Editor::_gizmo_y_axis)
    SDL_DestroyTexture(Editor::_gizmo_y_axis);

  if(Editor::_gizmo_x_axis)
    SDL_DestroyTexture(Editor::_gizmo_x_axis);

  this->last();
}

void Editor::load_fes_to_editor(const idk::StringViewChar& fes_file_or_content,
                                bool file) noexcept {
  bool is_found{false};
  for(auto& resource : this->_preloaded_fes_files) {
    if(resource.second()->scene_fes_file_path == fes_file_or_content) {
      std::cout << "Editor info: The fes file that trying to be loaded into editor is already loaded.\n";
      is_found = true;
      break;
    }
  }

  if(is_found)
    return;

  std::shared_ptr<FesLoaderResource> res =
    std::make_shared<FesLoaderResource>();
  res->load_fes(fes_file_or_content, file);
  this->_preloaded_fes_files.push_back(
    idk::MakePair<idk::usize, std::shared_ptr<FesLoaderResource>>(
      Editor::_resource_id, idk::move(res)));
  ++Editor::_resource_id;
}

void Editor::load_fes_to_editor(idk::StringViewChar&& fes_file_or_content,
                                bool file) noexcept {
  bool is_found{false};
  for(auto& resource : this->_preloaded_fes_files) {
    if(resource.second()->scene_fes_file_path == fes_file_or_content) {
      std::cout << "Editor info: The fes file that trying to be loaded into editor is already loaded.\n";
      is_found = true;
      break;
    }
  }

  if(is_found)
    return;

  std::shared_ptr<FesLoaderResource> res = std::make_shared<FesLoaderResource>();
  res->load_fes(idk::move(fes_file_or_content), file);

  this->_preloaded_fes_files.push_back(
    idk::MakePair<idk::usize, std::shared_ptr<FesLoaderResource>>(
      Editor::_resource_id, idk::move(res)));
  ++Editor::_resource_id;
}

void Editor::overwrite_current_fes_with_preloaded_one(idk::usize resource_id) noexcept {
  if(resource_id >= this->_preloaded_fes_files.size()) {
    std::cout << "Engine error: resource_id is matches out of vector bounds.\n";
    return;
  }

  RenderObjects::objects_to_render.clear();
  id::object_id = 0;
  this->_current_resource_id = resource_id;
  this->_preloaded_fes_files.at_without_check_reference(resource_id)._second->generate_objects();
}

void Editor::init() {
  Editor::_gizmo_y_axis = IMG_LoadTexture(
    Engine::get_instance()->get_window()->get_renderer(), "gizmo_y_axis.png");
  Editor::_gizmo_x_axis = IMG_LoadTexture(
    Engine::get_instance()->get_window()->get_renderer(), "gizmo_x_axis.png");

  Engine::get_instance()->get_cursor_resource().init_cursor();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
  io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport;

  ImGui_ImplSDL2_InitForSDLRenderer(
    Engine::get_instance()->get_window()->_window,
    Engine::get_instance()->get_window()->get_renderer());
  ImGui_ImplSDLRenderer2_Init(
    Engine::get_instance()->get_window()->get_renderer());

  Editor::_editor_texture =
    SDL_CreateTexture(Engine::get_instance()->get_window()->get_renderer(),
                      SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                      Engine::get_instance()->get_window()->_width,
                      Engine::get_instance()->get_window()->_height);

  // font = io.Fonts->AddFontFromFileTTF("gech.ttf", 14);
}

void Editor::update() {
  while(Engine::get_instance()->_engine_running) {

    SDL_GetWindowSize(Engine::get_instance()->get_window()->_window,
                      &Engine::get_instance()->get_window()->_width,
                      &Engine::get_instance()->get_window()->_height);

    ImGui_ImplSDL2_ProcessEvent(&Engine::_event_instance);

    ImGui_ImplSDLRenderer2_NewFrame();

    ImGui_ImplSDL2_NewFrame(Engine::get_instance()->get_window()->_window);

    ImGui::NewFrame();

    SDL_SetRenderTarget(Engine::get_instance()->get_window()->get_renderer(),
                        Editor::_editor_texture);

    SDL_SetRenderDrawColor(
      Engine::get_instance()->get_window()->get_renderer(),
      Engine::get_instance()->get_window()->get_default_clear_color().r,
      Engine::get_instance()->get_window()->get_default_clear_color().g,
      Engine::get_instance()->get_window()->get_default_clear_color().b,
      Engine::get_instance()->get_window()->get_default_clear_color().a);

    SDL_RenderClear(Engine::get_instance()->get_window()->get_renderer());

    SDL_PollEvent(&Engine::_event_instance);

    Engine::get_instance()->get_cursor_resource().sync_position();

    if(Engine::_event_instance.type == SDL_QUIT) {
      Engine::get_instance()->_engine_running = false;
      break;
    }

    if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_RCTRL) ||
       Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_LCTRL)) {
      Editor::control_key_pressed = true;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_released(SDL_SCANCODE_RCTRL) ||
              Engine::get_instance()->get_keyboard_input().is_key_released(SDL_SCANCODE_LCTRL)) {
      Editor::control_key_pressed = false;
    }

    if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_Z) && Editor::control_key_pressed) {
      if(!this->_operation_handler._operations.is_empty()) {
        this->_operation_handler.undo_last_change();
      } else {
        std::cout << "Editor info: No undo possible right now.\n";
      }
    }

    Editor::_debug_fn();

    // editor camera. when playing the game, this camera will be replaced with user defined one.
    if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_A)) {
      this->_editor_camera->get_position_info().x -= 10;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_D)) {
      this->_editor_camera->get_position_info().x += 10;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_W)) {
      this->_editor_camera->get_position_info().y -= 10;
    } else if(Engine::get_instance()->get_keyboard_input().is_key_pressed(SDL_SCANCODE_S)) {
      this->_editor_camera->get_position_info().y += 10;
    }

    for(auto& object : fresh::RenderObjects::objects_to_render) {
      if(object.get()) {
        if(Engine::get_instance()->_camera_object.get()) {
          if(Engine::get_instance()->_camera_object->is_visible_on_camera(
               object)) {
            object->sync();
          }
        } else {
          object->sync();
        }
      } else {
        std::cout << "Engine error: No camera found and iterated object is invalid.\n";
      }
    }

    if(Engine::get_instance()->_camera_object.get())
      Engine::get_instance()->_camera_object->sync();

    Engine::get_instance()->get_cursor_resource().sync_sprite();

    SDL_SetRenderTarget(Engine::get_instance()->get_window()->get_renderer(),
                        NULL);

    //      ImGui::Begin("Test");
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(
      ImVec2(viewport->Pos.x, viewport->Pos.y + ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |=
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("freshEngine", &Editor::is_open,
                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::PopStyleVar(3);
    ImGui::BeginMainMenuBar();

    // ImGui::PushFont(font);
    if(ImGui::BeginMenu("freshEngine")) {
      if(ImGui::MenuItem("About")) {
        Editor::is_engine_about_scene_open = true;
      }

      ImGui::EndMenu();
    }
    // ImGui::PopFont();

    if(this->_project_fes_file.get() && !this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty()) {
      std::shared_ptr<fes::FesProjectObjectAST> ptr = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(this->_project_fes_file->get_fes_parser()
                                                                                                            ._objects->_sub_groups.at_without_check_reference(0));
      if(ImGui::BeginMenu((this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty())
                            ? "##project_settings"
                            : ptr->_project_name.data())) {
        if(ImGui::MenuItem("Project Settings")) {
          Editor::is_project_settings_open = true;
          std::shared_ptr<fes::FesProjectObjectAST> ptr = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
            this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0));

          Editor::object_name = ptr->_project_name;
          Editor::resource_str_1 = ptr->_default_fes_file;
          Editor::object_width = ptr->_default_window_size_w;
          Editor::object_height = ptr->_default_window_size_h;
        } else if(ImGui::MenuItem("Add Scene")) {
          Editor::is_project_add_scene_open = true;
        }

        ImGui::EndMenu();
      }
    }

    if(ImGui::BeginMenu("Project")) {
      if(ImGui::MenuItem("Create Project")) {
        Editor::is_create_project_scene_open = true;
      } else if(ImGui::MenuItem("Open Project")) {
        Editor::is_open_project_scene_open = true;
      } else if(ImGui::MenuItem("Save Project")) { // FIXME: there are some problems
        if(!this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty()
              &&
           !std::dynamic_pointer_cast<fes::FesProjectObjectAST>(this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
              ->_default_fes_file.is_empty()) {
          // TODO: Save project with scenes
          //for(auto& [id, ptr]: this->_preloaded_fes_files) {
          //          if(!ptr.get()) {
          //            std::cout << "Editor error: Invalid pointer passed to Scenes menu!\n";
          //            continue;
          //          }
          //
          //          if(ptr->scene_fes_file_path.is_empty()) {
          //            std::cout << "Editor error: Scene file path is empty.\n";
          //          }
          //
          //          if(ImGui::MenuItem(ptr->scene_fes_file_path.data())) {
          //
          //          }
          //        }
          for(auto& [id, ptr] : this->_preloaded_fes_files) {
            if(!ptr.get()) {
              std::cout << "Editor error: Invalid FesLoaderResource pointer found at project save.\n";
              continue;
            }

            if(id != this->_current_resource_id) {
              std::ofstream file_stream(
                this->_preloaded_fes_files.at_without_check_reference(this->_current_resource_id).second()->scene_fes_file_path.data(), std::ios::trunc);
              file_stream << ptr->_convert_render_objects();
              file_stream.close();
              this->overwrite_current_fes_with_preloaded_one(id);
            }
          }

          // save project file
          std::ofstream output_stream(
            this->_project_fes_file->scene_fes_file_path.data(), std::ios::trunc);
          output_stream << this->_project_fes_file->convert_into_fes() << '\n';
          output_stream.close();
          const auto project_file_path = this->_project_fes_file->scene_fes_file_path;
          this->_project_fes_file.reset();
          this->_project_fes_file = std::make_shared<FesLoaderResource>();
          this->_preloaded_fes_files.clear();
          this->open_project(project_file_path);
  /*
          this->_preloaded_fes_files.clear();
          Editor::_resource_id = 0;

          this->load_fes_to_editor(std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
                                     this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0)
                                       )->_default_fes_file);
          // FIXME: maybe there's a problem (latest)
          for(auto& scene: std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
                              this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0)
                                )->_preloaded_fes_files) {
            std::shared_ptr<FesLoaderResource> res = std::make_shared<FesLoaderResource>();
            res->load_fes(scene->_file_path);
            this->_preloaded_fes_files.push_back(
              idk::MakePair<idk::usize, std::shared_ptr<FesLoaderResource>>(
                Editor::_resource_id, idk::move(res))
            );
            ++Editor::_resource_id;
          }*/
          this->_operation_handler._operations.clear();
          const auto project_fes_file_path = this->_project_fes_file->scene_fes_file_path;
          this->_project_fes_file = std::make_shared<FesLoaderResource>();
          this->_preloaded_fes_files.clear();
          this->open_project(project_fes_file_path);
        }
      }

      ImGui::EndMenu();
    }

    if((this->_current_resource_id != -1) && !this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty()) {
      if(ImGui::BeginMenu("Scenes")) {
        // if(ImGui::MenuItem(this->_preloaded_fes_files.at_without_check_reference(this->_current_resource_id)._second->scene_fes_file_path.data())) {
        //  this->overwrite_current_fes_with_preloaded_one(this->_current_resource_id);
        //}
        // TODO: Do not load every scene from file. instead, access preloaded scenes from memory, otherwise we will overwrite current unsaved scene.
        for(auto& [id, ptr]: this->_preloaded_fes_files) {
          if(!ptr.get()) {
            std::cout << "Editor error: Invalid pointer passed to Scenes menu!\n";
            continue;
          }

          if(ptr->scene_fes_file_path.is_empty()) {
            std::cout << "Editor error: Scene file path is empty.\n";
          }

          if(ImGui::MenuItem(ptr->scene_fes_file_path.data())) {
            if(id != this->_current_resource_id) {
              std::ofstream file_stream(
                this->_preloaded_fes_files.at_without_check_reference(this->_current_resource_id).second()->scene_fes_file_path.data(), std::ios::trunc
                );
              file_stream << ptr->_convert_render_objects();
              file_stream.close();

              this->_operation_handler._operations.clear();
              const auto project_fes_file_path = this->_project_fes_file->scene_fes_file_path;
              this->_project_fes_file = std::make_shared<FesLoaderResource>();
              this->_preloaded_fes_files.clear();
              this->open_project(project_fes_file_path);

              this->overwrite_current_fes_with_preloaded_one(id);
            }
          }
        }
        ImGui::EndMenu();
      }
    }
    

    if(ImGui::BeginMenu("Menu")) {
      if(ImGui::MenuItem("Open Scene", "CTRL+O")) {
        Editor::is_select_scene_open = true;
      } else if(ImGui::MenuItem("Save Scene", "CTRL+S")) {
        Editor::is_save_scene_open = true;
      }

      ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Create")) {
      if(ImGui::MenuItem("GuiBaseObject")) {
        Editor::create_object = fes::Keywords::GuiBaseObject;
      } else if(ImGui::MenuItem("GuiButtonObject")) {
        Editor::create_object = fes::Keywords::GuiButtonObject;
      } else if(ImGui::MenuItem("AreaObject")) {
        Editor::create_object = fes::Keywords::AreaObject;
      } else if(ImGui::MenuItem("BaseObject")) {
        Editor::create_object = fes::Keywords::BaseObject;
      } else if(ImGui::MenuItem("CameraObject")) {
        Editor::create_object = fes::Keywords::CameraObject;
      } else if(ImGui::MenuItem("CollisionObject")) {
        Editor::create_object = fes::Keywords::CollisionObject;
      } else if(ImGui::MenuItem("LabelObject")) {
        Editor::create_object = fes::Keywords::LabelObject;
      } else if(ImGui::MenuItem("SpriteObject")) {
        Editor::create_object = fes::Keywords::SpriteObject;
      }

      ImGui::EndMenu();
    }

    if(!this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty() &&
       !std::dynamic_pointer_cast<fes::FesProjectObjectAST>(this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
          ->_default_fes_file.is_empty() && !this->_operation_handler._operations.is_empty()) {

      ImGui::SameLine(ImGui::GetWindowWidth() - 65);
      ImGui::Text("Unsaved");
    }
    ImGui::EndMainMenuBar();

    ImGuiID dockspace_id = ImGui::GetID("freshEngine");
    ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

    if(Editor::_first_loop) {
      ImVec2 workPos = ImGui::GetMainViewport()->WorkPos;
      ImVec2 workSize = ImGui::GetMainViewport()->WorkSize;
      ImVec2 workCenter {workPos.x + workSize.x * 0.8f,
                        workPos.y + workSize.y * 0.8f };

      ImGuiID id = ImGui::GetID("freshEngine");

      ImGui::DockBuilderRemoveNode(id);
      ImGui::DockBuilderAddNode(id);

      ImVec2 size {960, 540 };
      ImVec2 nodePos { workCenter.x - size.x * 0.5f,
                     workCenter.y - size.y * 0.5f };

      ImGui::DockBuilderSetNodeSize(id, size);
      ImGui::DockBuilderSetNodePos(id, nodePos);

      ImGuiID dock1 =
        ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.8f, nullptr, &id);

      ImGuiID dock2 =
        ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.3f, nullptr, &id);

      ImGuiID dock3 = ImGui::DockBuilderSplitNode(dock2, ImGuiDir_Down, 0.3f,
                                                  nullptr, &dock2);

      ImGui::DockBuilderDockWindow("Scene", dock1);
      ImGui::DockBuilderDockWindow("Objects", dock2);
      ImGui::DockBuilderDockWindow("Code Editor", dock3);

      ImGui::DockBuilderFinish(id);
    }

    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Image((void*)Editor::_editor_texture,
                 ImVec2(Engine::get_instance()->get_window()->_width,
                        Engine::get_instance()->get_window()->_height));
    ImGui::End();

    ImGui::Begin("Objects", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    for(idk::isize i = 0; i < RenderObjects::objects_to_render.size(); ++i) {
      if(Editor::reload_scene_hierarchy) {
        break;
      }
      Editor::_walk_over_render_objects(RenderObjects::objects_to_render[i], i);
    }
    if(Editor::reload_scene_hierarchy) {
      for(idk::isize i = 0; i < RenderObjects::objects_to_render.size(); ++i) {
        Editor::_walk_over_render_objects(RenderObjects::objects_to_render[i], i);
      }
      Editor::reload_scene_hierarchy = false;
    }
    ImGui::End();

    ImGui::Begin("Code Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    /*if(Editor::_code_editor_files.is_empty()) {
      Editor::_code_editor_files.push_back("");
    }

    Editor::_add_element([]() {
      ImGui::InputTextMultiline("##inputtext", &Editor::_code_editor_files.back());
    });*/
    ImGui::End();
    ImGui::End();

    if(Editor::is_engine_about_scene_open) {
      ImGui::Begin("About");
        ImGui::Text("freshEngine is open source 2D game engine, core written in C++");
        ImGui::Text("Made by @ferhatgec for specific game development requirements.");
        ImGui::Text("freshEngine designed to ease use but it does not mean that it's generally purpose game engine.");
        ImGui::Text("freshEngine licensed under the terms of MIT License.");
      ImGui::End();
    }

    if(Editor::is_project_add_scene_open) {
      ImGui::Begin("Add Scene to Preloaded List");
      std::shared_ptr<fes::FesFileObjectAST> file_object = std::make_shared<fes::FesFileObjectAST>();
      this->_show_add_project_fes_file(idk::move(file_object));
      ImGui::End();
    }

    if(Editor::is_open_project_scene_open) {
      ImGui::Begin("Open Existing Project");
      Editor::_add_element([this]() {
        if(ImGui::InputText("<- .feproj file path", &Editor::_fes_file_path,
                            ImGuiInputTextFlags_EnterReturnsTrue)) {
          this->open_project(Editor::_fes_file_path);
          Editor::is_open_project_scene_open = false;
        }
      });
      ImGui::End();
    }

    if(Editor::is_project_settings_open) {
      if(!this->_project_fes_file.get()) {
        std::cout << "Editor error: Invalid project Fes file.\n";
        Editor::is_project_settings_open = false;
        Editor::_group_index = 0;
        return;
      }

      if(!this->_project_fes_file->get_fes_parser()._objects.get()) {
        std::cout << "Editor error: Fes parser contains invalid object pointer.\n";
        Editor::is_project_settings_open = false;
        Editor::_group_index = 0;
        return;
      }

      if(this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty()) {
        std::cout << "Editor error: Project parser is empty.\n";
        Editor::is_project_settings_open = false;
        Editor::_group_index = 0;
        return;
      }

      ImGui::Begin((std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
                      this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
                      ->_project_name
                    + " Project Settings")
                     .data());
      Editor::_add_element([]() {
        ImGui::InputText("<- project name", &Editor::object_name);
      });

      Editor::_add_element([]() {
        ImGui::InputText("<- default scene file (ends with .fes)", &Editor::resource_str_1);
      });

      Editor::_add_element([]() {
        ImGui::InputInt("<- default window width", &Editor::object_width);
      });

      Editor::_add_element([]() {
        ImGui::InputInt("<- default window height", &Editor::object_height);
      });

      Editor::_add_element([&]() {
        if(ImGui::SmallButton("Save")) {
          std::shared_ptr<fes::FesProjectObjectAST> ptr = std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
            this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0));

          if(!ptr.get()) {
            std::cout << "Editor error: Invalid pointer passed into editor settings handler.\n";
            Editor::is_project_settings_open = false;
            Editor::_group_index = 0;
            return;
          }

          ptr->_project_name = Editor::object_name;
          ptr->_default_fes_file = Editor::resource_str_1;

          if(Editor::object_width < 0)
            Editor::object_width = abs(Editor::object_width);

          if(Editor::object_height < 0)
            Editor::object_height = abs(Editor::object_height);

          ptr->_default_window_size_w = Editor::object_width;
          ptr->_default_window_size_h = Editor::object_height;

          const auto copy_scene_feproj_file_path = this->_project_fes_file->scene_fes_file_path;

          std::ofstream output_stream(this->_project_fes_file->scene_fes_file_path.data(), std::ios::trunc);

          if(!output_stream) {
            std::cout << "Editor error: Output stream is invalid.\n";
            Editor::is_project_settings_open = false;
            Editor::_group_index = 0;
            return;
          }

          output_stream << this->_project_fes_file->convert_into_fes();
          output_stream.close();
          this->_project_fes_file = std::make_shared<FesLoaderResource>();
          this->_preloaded_fes_files.clear();
          this->open_project(copy_scene_feproj_file_path);
          Editor::is_project_settings_open = false;
        }
      });

      for(auto& elem : std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
                         this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
                         ->_preloaded_fes_files) {
        if(elem->_name.is_empty()) {
          if(elem->_file_path.is_empty()) {
            std::cout << "Editor error: File path / name is empty in preloaded files.\n";
          }

          elem->_name = elem->_file_path;
        }

        if(ImGui::TreeNode(elem->_name.data())) {
          this->_show_add_project_fes_file(elem);
          ImGui::TreePop();
        }
      }

      ImGui::End();
    }

    if(Editor::is_create_project_scene_open) {
      ImGui::Begin("Create New Project");
      Editor::_add_element(
        []() { ImGui::InputText("<- project name", &Editor::object_name); });
      Editor::_add_element([]() {
        ImGui::InputText("<- project file name (ends with .feproj)",
                         &Editor::resource_str_1);
      });
      Editor::_add_element([]() {
        ImGui::InputInt("<- default window width", &Editor::object_width);
      });
      Editor::_add_element([]() {
        ImGui::InputInt("<- default window height", &Editor::object_height);
      });

      Editor::_add_element([&]() {
        if(ImGui::SmallButton("Create New Project")) {
          // TODO: Create new project and save as file. Then add option for add new scene files into it. and give option to set default scene file.
          std::shared_ptr<fes::FesProjectObjectAST> project = std::make_shared<fes::FesProjectObjectAST>();
          project->_project_name = Editor::object_name;
          project->_default_window_size_w = Editor::object_width;
          project->_default_window_size_h = Editor::object_height;
          project->_object_type = fes::Keywords::Project;
          project->_default_clear_color =
            std::make_shared<fes::FesColorObjectAST>();
          project->_default_clear_color->_object_type = fes::Keywords::Color;
          this->_project_fes_file->get_fes_parser()
            ._objects->_sub_groups.push_back(
              std::dynamic_pointer_cast<fes::FesObjectAST>(idk::move(project)));
          std::ofstream output_stream(Editor::resource_str_1.data(), std::ios::trunc);
          output_stream << this->_project_fes_file->convert_into_fes() << '\n';
          output_stream.close();
          Editor::is_create_project_scene_open = false;
        }
      });
      ImGui::End();
    }

    if(Editor::is_select_scene_open) {
      ImGui::Begin("Open .fes File");
      Editor::_add_element([this]() {
        if(ImGui::InputText("<- .fes file path", &Editor::_fes_file_path,
                            ImGuiInputTextFlags_EnterReturnsTrue)) {
          this->load_fes_to_editor(Editor::_fes_file_path);
          this->overwrite_current_fes_with_preloaded_one(
            this->_preloaded_fes_files.size() - 1
            );
          Editor::is_select_scene_open = false;
        }
      });
      ImGui::End();
    }

    if(Editor::is_save_scene_open) {
      ImGui::Begin("Save .fes File");
      Editor::_add_element([this]() {
        if(ImGui::InputText("<- .fes file path", &Editor::_fes_save_file_path,
                            ImGuiInputTextFlags_EnterReturnsTrue)) {
          if(!this->_preloaded_fes_files.is_empty()) {
            std::ofstream file_stream(Editor::_fes_save_file_path.data(),
                                      std::ios::trunc);

            file_stream << this->_preloaded_fes_files.back()
                             ._second->convert_into_fes()
                             .data();
            file_stream.close();
            Editor::is_save_scene_open = false;
          } else {
            std::cout << "Engine info: You actually have not opened any scenes, saving it will not do anything.\n";
          }
        }
      });
      ImGui::End();
    }

    if(Editor::create_object != fes::Keywords::Undefined) {
      ImGui::Begin("Create New Object");
      Editor::_add_element(
        []() { ImGui::InputText("<- object name", &Editor::object_name); });
      Editor::_add_element(
        []() { ImGui::InputInt("<- width", &Editor::object_width); });
      Editor::_add_element(
        []() { ImGui::InputInt("<- height", &Editor::object_height); });
      Editor::_add_element(
        []() { ImGui::InputInt("<- x", &Editor::object_pos_x); });
      Editor::_add_element(
        []() { ImGui::InputInt("<- y", &Editor::object_pos_y); });

      if(create_object == fes::Keywords::SpriteObject) {
        Editor::_add_element([]() {
          ImGui::InputText("<- sprite path", &Editor::resource_str_1);
        });
      } else if(create_object == fes::Keywords::LabelObject) {
        Editor::_add_element([]() {
          ImGui::InputText("<- font path", &Editor::resource_str_1);
        });

        Editor::_add_element([]() {
          ImGui::InputText("<- label text", &Editor::resource_str_2);
        });

        Editor::_add_element(
          []() { ImGui::InputInt("<- font size", &Editor::resource_int_1); });
      }

      switch(create_object) {
      case fes::Keywords::GuiBaseObject: {
        if(ImGui::SmallButton("Create GuiBaseObject")) {
          std::shared_ptr<fresh::GuiBaseObject> object =
            std::make_shared<fresh::GuiBaseObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::GuiButtonObject: {
        if(ImGui::SmallButton("Create GuiButtonObject")) {
          std::shared_ptr<fresh::GuiButtonObject> object =
            std::make_shared<fresh::GuiButtonObject>();
          Editor::_create_render_object(idk::move(object));
          // TODO: textures? hover, click?
        }
        break;
      }

      case fes::Keywords::AreaObject: {
        if(ImGui::SmallButton("Create AreaObject")) {
          std::shared_ptr<fresh::AreaObject> object =
            std::make_shared<fresh::AreaObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::BaseObject: {
        if(ImGui::SmallButton("Create BaseObject")) {
          std::shared_ptr<fresh::BaseObject> object =
            std::make_shared<fresh::BaseObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::CameraObject: {
        if(ImGui::SmallButton("Create CameraObject")) {
          std::shared_ptr<fresh::CameraObject> object =
            std::make_shared<fresh::CameraObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::CollisionObject: {
        if(ImGui::SmallButton("Create CollisionObject")) {
          std::shared_ptr<fresh::CollisionObject> object =
            std::make_shared<fresh::CollisionObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::LabelObject: {
        if(ImGui::SmallButton("Create LabelObject")) {
          std::shared_ptr<fresh::LabelObject> object =
            std::make_shared<fresh::LabelObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::SpriteObject: {
        if(ImGui::SmallButton("Create SpriteObject")) {
          std::shared_ptr<fresh::SpriteObject> object =
            std::make_shared<fresh::SpriteObject>();
          Editor::_create_render_object(idk::move(object));
        }
        break;
      }

      case fes::Keywords::Undefined: {
        break;
      }

      default: {
        std::cout << "Editor error: Unknown object type found.\n";
        break;
      }
      }
      ImGui::End();
    }

    ImGui::Render();

    Engine::get_instance()
      ->get_cursor_resource()
      .sync_sprite();// it's synced before everything passed to framebuffer.
                     // to bypass render priority.

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(Engine::get_instance()->get_window()->get_renderer());

    SDL_DestroyTexture(Editor::_editor_texture);

    Editor::_editor_texture =
      SDL_CreateTexture(Engine::get_instance()->get_window()->get_renderer(),
                        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                        Engine::get_instance()->get_window()->_width,
                        Engine::get_instance()->get_window()->_height);

    if(Engine::get_instance()->_camera_object.get()) {
      Engine::get_instance()->_camera_object->get_position_info().w =
        Engine::get_instance()->get_window()->_width;
      Engine::get_instance()->_camera_object->get_position_info().h =
        Engine::get_instance()->get_window()->_height;
    }

    if(Editor::_first_loop)
      Editor::_first_loop = false;

    Editor::_group_index = 0;
    Editor::_selected_tree_node = 0;
  }
}

void Editor::last() {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void Editor::open_project(const idk::StringViewChar& project_file_path) noexcept {
  Editor::_resource_id = 0;
  this->_project_fes_file->load_fes(project_file_path);
  
  if(!this->_project_fes_file->get_fes_parser()._objects->_sub_groups.is_empty()) {

    std::shared_ptr<fes::FesProjectObjectAST> ptr =
      std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
        this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0));
    
    this->_editor_camera->get_position_info().w = ptr->_default_window_size_w;
    this->_editor_camera->get_position_info().h = ptr->_default_window_size_h;

    Engine::get_instance()->get_window()->get_default_clear_color().r = ptr->_default_clear_color->_red;
    Engine::get_instance()->get_window()->get_default_clear_color().g = ptr->_default_clear_color->_green;
    Engine::get_instance()->get_window()->get_default_clear_color().b = ptr->_default_clear_color->_blue;
    Engine::get_instance()->get_window()->get_default_clear_color().a = ptr->_default_clear_color->_alpha;
    

    if(!ptr->_default_fes_file.is_empty()) {
      this->load_fes_to_editor(ptr->_default_fes_file);
      this->overwrite_current_fes_with_preloaded_one(this->_preloaded_fes_files.size() - 1);

      for(auto& scene: ptr->_preloaded_fes_files) {
        std::shared_ptr<FesLoaderResource> res = std::make_shared<FesLoaderResource>();
          res->load_fes(scene->_file_path);
          this->_preloaded_fes_files.push_back(
            idk::MakePair<idk::usize, std::shared_ptr<FesLoaderResource>>(
                  Editor::_resource_id, idk::move(res))
            );
          ++Editor::_resource_id;
      }

      // preload others?
    } else {
      std::cout << "Editor info: No scene is opened by default.\n";
    }
  }
}

void Editor::_walk_over_render_objects(std::shared_ptr<BaseObject>& obj, idk::isize obj_index) noexcept {
  if(obj->get_name().is_empty()) {
    std::cout << "Editor error: Name cannot be empty.\n";
    obj->get_name() =
      obj->_object_def + idk::StringViewChar(std::to_string(Editor::_group_index).data());
  }

  if(bool x = ImGui::TreeNode(obj->get_name().data())
       ; [obj, obj_index, x]() {
          ImGui::SameLine();
          Editor::_add_element([obj_index]() {
            if(ImGui::SmallButton("Up")) {
              if(obj_index != 0) {
                idk::swap(RenderObjects::objects_to_render[obj_index], RenderObjects::objects_to_render[obj_index - 1]);
                Editor::reload_scene_hierarchy = true;
              } else {
                std::cout << "Editor info: Object is already at the top.\n";
              }
            }
          });

          ImGui::SameLine();
          Editor::_add_element([obj_index]() {
            if(ImGui::SmallButton("Down")) {
              if(obj_index != (RenderObjects::objects_to_render.size() - 1)) {
                idk::swap(RenderObjects::objects_to_render[obj_index], RenderObjects::objects_to_render[obj_index + 1]);
                Editor::reload_scene_hierarchy = true;
              } else {
                std::cout << "Editor info: Object is already at the bottom.\n";
              }
            }
          });

          return x;
     }()) {
    Editor::_selected_tree_node =
      obj->get_object_id();// last opened treenode will be selected as _selected_tree_node. so creating new object will be passed inside that object's sub_groups.
    ImGui::SetNextItemAllowOverlap();

    // FIXME: there can be a problem
    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::Name, obj->get_name());

      if(ImGui::InputText("<- name", &obj->get_name(),
                          ImGuiInputTextFlags_EnterReturnsTrue)) {
        if(obj->get_name().is_empty()) {
          std::cout << "Editor error: Name cannot be empty.\n";
          obj->get_name() =
            obj->_object_def + idk::StringViewChar(std::to_string(Editor::_group_index).data());
          this->_operation_handler.before_push_to_init(obj->get_name());
          // operation handler here.
        }
      }
    });

    ImGui::Text("disabled: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::Disabled, obj->get_is_disabled());
      if(ImGui::Selectable(obj->get_is_disabled() ? "true" : "false",&obj->get_is_disabled())) {
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_is_disabled());
      }
    });

    ImGui::Text("visible: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::Visible, obj->get_is_visible());
      if(ImGui::Selectable(obj->get_is_visible() ? "true" : "false",&obj->get_is_visible())) {
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_is_visible());
      }
    });

    ImGui::Text("width: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::Width, obj->get_position_info().w);
      if(ImGui::SliderInt(std::to_string(obj->get_position_info().w).data(),&obj->get_position_info().w, 0, 4096)) {
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_position_info().w);
      }
    });

    ImGui::Text("height: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::Height, obj->get_position_info().h);
      if(ImGui::SliderInt(std::to_string(obj->get_position_info().h).data(),&obj->get_position_info().h, 0, 4096)) {
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_position_info().h);
      }
    });

    ImGui::Text("x: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::PositionX, obj->get_position_info().x);
      if(ImGui::SliderInt(std::to_string(obj->get_position_info().x).data(),&obj->get_position_info().x, -8192, 8192)) {
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_position_info().x);
      }
    });

    ImGui::Text("y: ");
    ImGui::SameLine();

    Editor::_add_element([this, obj]() {
      this->_operation_handler.before_push_from_init(fes::Keywords::PositionY, obj->get_position_info().y);
      if(ImGui::SliderInt(std::to_string(obj->get_position_info().y).data(),&obj->get_position_info().y,
                          -8192,8192)) { // FIXME: those limits are enough for us. otherwise slider being nonsensitive on small intervals.
        // operation handler here.
        this->_operation_handler.before_push_to_init(obj->get_position_info().y);
      }
    });

    if(obj->_object_def == "labelobject") {
      Editor::_show_label_object_on_tree(
        obj);// TODO: create preview area that shows the label text with given font. Like SpriteObject, which has image preview.

      //
      //
      //    this->_label_font_resource.load_font(this->_label_font_resource.get_font_path());
      //  this->initialize_text(this->_label_text, this->_fg, this->_bg, this->_label_render_type);

      //
    } else if(obj->_object_def == "spriteobject") {
      Editor::_show_sprite_object_on_tree(obj);
    } else if(obj->_object_def == "guibuttonobject") {
      ImGui::Text("On click: ");
      Editor::_add_element([&]() {
        if(!std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_clicked_sprite_object()
              ->get_sprite_resource()
              .get_texture()) {
          Editor::_add_element([]() {
            ImGui::SameLine();
            if(ImGui::SmallButton("Create SpriteObject")) {
              Editor::create_object = fes::Keywords::SpriteObject;
              Editor::_state = "guibuttonobject:_on_clicked_sprite_object";
            }
          });
        } else {
          Editor::_show_sprite_object_on_tree(
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_clicked_sprite_object());
        }
      });

      ImGui::Text("On click: ");
      Editor::_add_element([&]() {
        if(!std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_clicked_label_object()
              ->get_label_font_resource()
              .get_font()) {
          Editor::_add_element([]() {
            ImGui::SameLine();
            if(ImGui::SmallButton("Create LabelObject")) {
              Editor::create_object = fes::Keywords::LabelObject;
              Editor::_state = "guibuttonobject:_on_clicked_label_object";
            }
          });
        } else {
          Editor::_show_label_object_on_tree(
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_clicked_label_object());
        }
      });

      ImGui::Text("On hover: ");
      Editor::_add_element([&]() {
        if(!std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_hover_sprite_object()
              ->get_sprite_resource()
              .get_texture()) {
          Editor::_add_element([]() {
            ImGui::SameLine();
            if(ImGui::SmallButton("Create SpriteObject")) {
              Editor::create_object = fes::Keywords::SpriteObject;
              Editor::_state = "guibuttonobject:_on_hover_sprite_object";
            }
          });
        } else {
          Editor::_show_sprite_object_on_tree(
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_hover_sprite_object());
        }
      });

      ImGui::Text("On hover: ");
      Editor::_add_element([&]() {
        if(!std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_hover_label_object()
              ->get_label_font_resource()
              .get_font()) {
          Editor::_add_element([]() {
            ImGui::SameLine();
            if(ImGui::SmallButton("Create LabelObject")) {
              Editor::create_object = fes::Keywords::LabelObject;
              Editor::_state = "guibuttonobject:_on_hover_label_object";
            }
          });
        } else {
          Editor::_show_label_object_on_tree(
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(obj)
              ->get_on_hover_label_object());
        }
      });
    }

    for(idk::isize i = 0; i < obj->get_sub_objects().size(); ++i) {
      Editor::_walk_over_render_objects(obj->get_sub_objects()[i], i);
    }

    ImGui::TreePop();
  }
}

void Editor::_create_render_object(std::shared_ptr<BaseObject> obj) noexcept {
  if(!obj.get())
    std::cout
      << "Editor error: Invalid pointer passed to _create_render_object!\n";

  if(Editor::object_name.is_empty())
    Editor::object_name =
      obj->_object_def + std::to_string(obj->get_object_id()).data();

  obj->get_name() = Editor::object_name;
  obj->get_position_info().x = Editor::object_pos_x;
  obj->get_position_info().y = Editor::object_pos_y;

  if(Editor::object_width < 0)
    Editor::object_width = abs(Editor::object_width);

  if(Editor::object_height < 0)
    Editor::object_height = abs(Editor::object_height);

  obj->get_position_info().w = Editor::object_width;
  obj->get_position_info().h = Editor::object_height;

  if(obj->_object_def == "spriteobject") {
    if(!Editor::resource_str_1.is_empty()) {
      std::dynamic_pointer_cast<fresh::SpriteObject>(obj)
        ->get_sprite_resource()
        .load_resource(Editor::resource_str_1);

      if(!std::dynamic_pointer_cast<fresh::SpriteObject>(obj)
            ->get_sprite_resource()
            .get_texture()) {
        std::cout << "Editor error: SpriteObject texture cannot be loaded.\n";
      }

      Editor::resource_str_1.clear();
    } else {
      std::cout << "Editor warning: New SpriteObject has no texture being assigned.\n";
    }
  } else if(obj->_object_def == "labelobject") {
    if(!Editor::resource_str_1.is_empty()) {
      std::dynamic_pointer_cast<fresh::LabelObject>(obj)
        ->get_label_font_resource()
        .get_font_path() = Editor::resource_str_1;
      std::dynamic_pointer_cast<fresh::LabelObject>(obj)->get_label_text() =
        Editor::resource_str_2;
      std::dynamic_pointer_cast<fresh::LabelObject>(obj)
        ->get_label_font_resource()
        .load_font(Editor::resource_str_1);
      std::dynamic_pointer_cast<fresh::LabelObject>(obj)
        ->get_label_font_resource()
        .get_font_size() = abs(Editor::resource_int_1);
      std::dynamic_pointer_cast<fresh::LabelObject>(obj)->initialize_text(
        std::dynamic_pointer_cast<fresh::LabelObject>(obj)->get_label_text(),
        SDL_Color{.r = 255, .g = 255, .b = 255, .a = 255},
        SDL_Color{.r = 255, .g = 255, .b = 255, .a = 255},
        fresh::LabelRenderType::Solid);
      Editor::resource_str_1.clear();
      Editor::resource_str_2.clear();
      Editor::resource_int_1 = 0;
    }
  }

  if(Editor::_selected_tree_node != 0) {
    for(auto& render_obj : RenderObjects::objects_to_render) {
      if(!render_obj.get())
        continue;

      if(render_obj->get_object_id() == Editor::_selected_tree_node) {
        if(Editor::_state == "guibuttonobject:_on_clicked_sprite_object") {
          if(render_obj->_object_def == "guibuttonobject") {
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(render_obj)
              ->get_on_clicked_sprite_object() =
              idk::move(std::dynamic_pointer_cast<fresh::SpriteObject>(obj));
          } else {
            std::cout << "Editor error: Editor::_state is assigned with data that related with guibuttonobject."
                         "Current selected node either is not guibuttonobject or there's no any node being selected.\n";
          }
        } else if(Editor::_state == "guibuttonobject:_on_clicked_label_object") {
          if(render_obj->_object_def == "guibuttonobject") {
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(render_obj)
              ->get_on_clicked_label_object() =
              idk::move(std::dynamic_pointer_cast<fresh::LabelObject>(obj));
          } else {
            std::cout << "Editor error: Editor::_state is assigned with data that related with guibuttonobject."
                         "Current selected node either is not guibuttonobject or there's no any node being selected.\n";
          }
        } else if(Editor::_state == "guibuttonobject:_on_hover_sprite_object") {
          if(render_obj->_object_def == "guibuttonobject") {
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(render_obj)
              ->get_on_hover_sprite_object() =
              idk::move(std::dynamic_pointer_cast<fresh::SpriteObject>(obj));
          } else {
            std::cout << "Editor error: Editor::_state is assigned with data that related with guibuttonobject."
                         "Current selected node either is not guibuttonobject or there's no any node being selected.\n";
          }
        } else if(Editor::_state == "guibuttonobject:_on_hover_label_object") {
          if(render_obj->_object_def == "guibuttonobject") {
            std::dynamic_pointer_cast<fresh::GuiButtonObject>(render_obj)
              ->get_on_hover_label_object() =
              idk::move(std::dynamic_pointer_cast<fresh::LabelObject>(obj));
          } else {
            std::cout << "Editor error: Editor::_state is assigned with data that related with guibuttonobject."
                         "Current selected node either is not guibuttonobject or there's no any node being selected.\n";
          }
        } else {
          render_obj->push_to_sub_objects(obj);
          // render_obj->_sub_objects.push_back(idk::move(obj));
        }

        if(!Editor::_state.is_empty())
          Editor::_state.clear();

        Editor::object_width = 0;
        Editor::object_height = 0;
        Editor::object_pos_x = 0;
        Editor::object_pos_y = 0;
        Editor::object_name.clear();
        Editor::create_object = fes::Keywords::Undefined;
        return;
      }
    }
  }

  if(!Editor::_state.is_empty()) {
    std::cout << "Editor error: Editor::_state is not empty. Editor::_state -> "
              << Editor::_state << '\n';
    Editor::_state.clear();
  }

  RenderObjects::objects_to_render.push_back(idk::move(obj));
  Editor::object_width = 0;
  Editor::object_height = 0;
  Editor::object_pos_x = 0;
  Editor::object_pos_y = 0;
  Editor::object_name.clear();
  Editor::create_object = fes::Keywords::Undefined;
}

void Editor::_add_element(std::function<void()> fn) noexcept {
  ImGui::PushID(Editor::_group_index);
  ++Editor::_group_index;
  fn();
  ImGui::PopID();
}

void Editor::_show_sprite_object_on_tree(
  std::shared_ptr<BaseObject> obj) noexcept {
  std::shared_ptr<SpriteObject> casted_obj =
    std::dynamic_pointer_cast<SpriteObject>(obj);

  Editor::_add_element([this, casted_obj]() {
    this->_operation_handler.before_push_from_init(fes::Keywords::SpriteResource, casted_obj->get_sprite_resource()._texture_path);
    if(ImGui::InputText("<- image",
                        &casted_obj->get_sprite_resource()._texture_path,
                        ImGuiInputTextFlags_EnterReturnsTrue)) {
      casted_obj->get_sprite_resource().load_resource(
        casted_obj->get_sprite_resource()._texture_path);
      this->_operation_handler.before_push_to_init(casted_obj->get_sprite_resource()._texture_path);
    }
  });

  ImGui::Image(casted_obj->get_sprite_resource().get_texture(), ImVec2(40, 40));
}

// FIXME: labelobject does not render correctly when created using editor.
void Editor::_show_label_object_on_tree(std::shared_ptr<BaseObject> obj) noexcept {
  std::shared_ptr<LabelObject> casted_obj =
    std::dynamic_pointer_cast<LabelObject>(obj);

  Editor::_add_element([this, casted_obj]() {
    this->_operation_handler.before_push_from_init(fes::Keywords::LabelText, casted_obj->get_label_text());
    if(ImGui::InputText("<- text", &casted_obj->get_label_text(),
                        ImGuiInputTextFlags_EnterReturnsTrue)) {
      casted_obj->initialize_label_font_surface();
      this->_operation_handler.before_push_to_init(casted_obj->get_label_text());
    }
  });

  Editor::_add_element([this, casted_obj]() {
    this->_operation_handler.before_push_from_init(fes::Keywords::FontResource, casted_obj->get_label_font_resource().get_font_path());
    if(ImGui::InputText("<- font path",
                        &casted_obj->get_label_font_resource().get_font_path(),
                        ImGuiInputTextFlags_EnterReturnsTrue)) {
      casted_obj->get_label_font_resource().load_font(
        casted_obj->get_label_font_resource().get_font_path());
      casted_obj->get_label_font_resource().sync_font_size();
      casted_obj->initialize_label_font_surface();
      this->_operation_handler.before_push_to_init(casted_obj->get_label_font_resource().get_font_path());
    }
  });

  Editor::_add_element([this, casted_obj]() {
    this->_operation_handler.before_push_from_init(fes::Keywords::FontSize, casted_obj->get_label_font_resource().get_font_size());
    if(ImGui::InputInt("<- font size",
                       &casted_obj->get_label_font_resource().get_font_size(),
                       ImGuiInputTextFlags_EnterReturnsTrue)) {
      casted_obj->get_label_font_resource().sync_font_size();
      casted_obj->initialize_label_font_surface();
      this->_operation_handler.before_push_to_init(casted_obj->get_label_font_resource().get_font_size());
    }
  });
  // TODO: font preview?
}

void Editor::_show_add_project_fes_file(std::shared_ptr<fes::FesFileObjectAST> file_object) noexcept {
  Editor::_add_element([file_object]() {
    ImGui::InputText("<- scene name", &file_object->_name);
  });

  Editor::_add_element([file_object]() {
    ImGui::InputText("<- scene .fes file path", &file_object->_file_path);
  });

  Editor::_add_element([]() {
    ImGui::Checkbox("<- use as default scene", &Editor::resource_bool_1);
  });

  Editor::_add_element([this, file_object]() {
    if(ImGui::SmallButton((Editor::is_project_settings_open ? "Save" : "Add"))) {
      if(!file_object.get()) {
        std::cout << "Editor error: Invalid FesFileObjectAST pointer.\n";
        Editor::is_project_add_scene_open = false;
        return;
      }

      if(file_object->_name.is_empty()) {
        file_object->_name = file_object->_file_path;
      }

      idk::isize found_index { -1_isize };

      for(idk::isize i = 0; i < this->_preloaded_fes_files.size(); ++i) {
        if(this->_preloaded_fes_files.at_without_check_reference(i).second()->scene_fes_file_path == file_object->_file_path) {
          found_index = i;
          break;
        }
      }

      if(Editor::resource_bool_1) { // set as default scene file
        if(found_index < 0) {
          this->load_fes_to_editor(file_object->_file_path);// push into fes project file
          std::dynamic_pointer_cast<fes::FesProjectObjectAST>(
            this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
            ->_preloaded_fes_files.push_back(idk::move(file_object));

          // TODO: load preloaded scenes from memory not from file they may be changed later but can be unsaved.
          this->overwrite_current_fes_with_preloaded_one(this->_preloaded_fes_files.size() - 1);
        } else {
          this->overwrite_current_fes_with_preloaded_one(found_index);
        }

        this->_project_fes_file->scene_fes_file_path = file_object->_file_path; // this applies changes.
        std::dynamic_pointer_cast<fes::FesProjectObjectAST>(this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
          ->_default_fes_file = file_object->_file_path; // this applies changes to project file configuration.
      } else {
        if(found_index < 0) {
          this->load_fes_to_editor(file_object->_file_path);// push into fes project file
          std::dynamic_pointer_cast<fes::FesProjectObjectAST>(this->_project_fes_file->get_fes_parser()._objects->_sub_groups.at_without_check_reference(0))
            ->_preloaded_fes_files.push_back(idk::move(file_object));
        } else {
          if(Editor::is_project_settings_open) { // change already preloaded scene.
            this->overwrite_current_fes_with_preloaded_one(found_index);
          } else {
            std::cout << "Engine info: Scene that being loaded is actually preloaded before.\n";
          }
        }
      }

      Editor::resource_bool_1 = false;
      Editor::is_project_add_scene_open = false;
    }
  });
}
}// namespace fresh