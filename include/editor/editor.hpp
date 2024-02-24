//
// Created by gech on 2/10/2024.
//

#ifndef FRESHENGINE_EDITOR_HPP
#define FRESHENGINE_EDITOR_HPP

#ifndef __FRESH_ENABLE_EDITOR
# define __FRESH_ENABLE_EDITOR
#endif // __FRESH_ENABLE_EDITOR

#include "operation.hpp"
#include "../freshengine.hpp"
#include "../../libs/idk/idk/containers/vector.hpp"
#include "../../libs/idk/idk/containers/stack.hpp"
#include "../../libs/idk/idk/utilities/pair.hpp"

namespace fresh {
class Editor {
public:
  Editor();
  virtual ~Editor();

  void
  load_fes_to_editor(const idk::StringViewChar& fes_file_or_content, bool file = true) noexcept;

  void
  load_fes_to_editor(idk::StringViewChar&& fes_file_or_content, bool file = true) noexcept;

  void
  overwrite_current_fes_with_preloaded_one(idk::usize resource_id) noexcept;

  void
  init();

  void
  update();

  void
  last();

  void
  open_project(const idk::StringViewChar& project_file_path) noexcept;

  static std::function<void()> _debug_fn;

  static fes::Keywords create_object;
  static idk::StringViewChar object_name;

  static idk::StringViewChar resource_str_1,
                             resource_str_2;
  static idk::i32 resource_int_1;

  static bool resource_bool_1;

  static bool is_open,
              is_select_scene_open,
              is_save_scene_open,
              is_create_project_scene_open,
              is_open_project_scene_open,
              is_project_settings_open,
              is_project_add_scene_open,
              is_engine_about_scene_open,
              reload_scene_hierarchy;

  static idk::i32 object_width,
                  object_height,
                  object_pos_x,
                  object_pos_y;
private:
  void
  _walk_over_render_objects(std::shared_ptr<BaseObject>& obj, idk::isize obj_index = 0) noexcept;

  void
  _create_render_object(std::shared_ptr<BaseObject> obj) noexcept;

  static void
  _add_element(std::function<void()> fn) noexcept;

  void
  _show_sprite_object_on_tree(std::shared_ptr<BaseObject> obj) noexcept;

  void
  _show_label_object_on_tree(std::shared_ptr<BaseObject> obj) noexcept;

  void
  _show_add_project_fes_file(std::shared_ptr<fes::FesFileObjectAST> file_object) noexcept;
protected:
  std::shared_ptr<fresh::FesLoaderResource> _project_fes_file;

  idk::Vector<idk::Pair<idk::usize, std::shared_ptr<fresh::FesLoaderResource>>> _preloaded_fes_files;
  std::shared_ptr<CameraObject> _editor_camera;

  static bool control_key_pressed;

  static idk::isize _resource_id;
  static idk::isize _group_index;
  static idk::isize _selected_tree_node;

  static SDL_Texture* _gizmo_y_axis;
  static SDL_Texture* _gizmo_x_axis;
  static SDL_Texture* _editor_texture;

  static idk::isize   _editor_focus_group_id;
  static bool         _first_loop;

  static idk::Vector<idk::StringViewChar> _code_editor_files;

  static idk::StringViewChar _state;

  static idk::StringViewChar _fes_file_path;
  static idk::StringViewChar _fes_save_file_path;
  static idk::StringViewChar _project_file_path;

  idk::isize _current_resource_id { -1_isize };

  EditorOperationHandler _operation_handler;
};
}

#endif // FRESHENGINE_EDITOR_HPP
