#ifndef FRESHENGINE_HPP
#define FRESHENGINE_HPP

#include "application/window.hpp"

#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"

#include "objects/base_object.hpp"
#include "objects/sprite_object.hpp"
#include "objects/label_object.hpp"
#include "objects/area_object.hpp"
#include "objects/collision_object.hpp"
#include "objects/camera_object.hpp"

#include "objects/gui/gui_base_object.hpp"
#include "objects/gui/gui_button_object.hpp"

// those objects are used in editor but it doesn't mean that it can't be used
// in other things. those are just basic data structures.
#include "objects/editor/editor_project_color_object.hpp"
#include "objects/editor/editor_project_file_object.hpp"
#include "objects/editor/editor_project_object.hpp"

#include "resources/sprite_resource.hpp"
#include "resources/timer_resource.hpp"
#include "resources/cursor_resource.hpp"
#include "resources/font_resource.hpp"
#include "resources/clipboard_resource.hpp"
#include "resources/audio_resource.hpp"
#include "resources/music_resource.hpp"
#include "resources/animation_key_resource.hpp"
#include "resources/animation_resource.hpp"
#include "resources/id_resource.hpp"
#include "resources/animation_property_resource.hpp"
#include "resources/animated_sprite_resource.hpp"
#include "resources/fes_loader_resource.hpp"

#include "fes/fes_ast.hpp"
#include "fes/fes_keywords.hpp"
#include "fes/fes_object.hpp"
#include "fes/fes_parser.hpp"
#include "fes/fes_tokenizer.hpp"

#include <memory>
#include <vector>
#include <any>

#ifdef FreshInstanceInit
// it can be changed after definition, that's here for guarantee.
# undef FreshInstanceInit
#endif

#define FreshInstanceInit() Engine::_instance = std::unique_ptr<fresh::Engine>(dynamic_cast<fresh::Engine*>(this))

namespace fresh {
class Engine {
public:
  friend class Editor;

  Engine();
  Engine(std::shared_ptr<Window> window);

  virtual ~Engine();

  __idk_nodiscard
  static std::unique_ptr<Engine>&
  get_instance() noexcept;

  __idk_nodiscard
  static SDL_Event&
  get_event_instance() noexcept;

  __idk_nodiscard
  std::shared_ptr<Window>&
  get_window() noexcept;

  virtual void
  update();

  virtual void
  init();

  virtual void
  last();

  void
  run(); // it will run the engine with user overridden update() and init().

  __idk_nodiscard
  idk::u32&
  get_fps() noexcept;

  __idk_nodiscard
  bool
  is_engine_running() noexcept;

  __idk_nodiscard
  KeyboardInput&
  get_keyboard_input() noexcept;

  __idk_nodiscard
  MouseInput&
  get_mouse_input() noexcept;

  __idk_nodiscard
  CursorResource&
  get_cursor_resource() noexcept;

  __idk_nodiscard
  ClipboardResource&
  get_clipboard_resource() noexcept;

  __idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>&
  get_objects_to_render() noexcept;

  void
  push_object(std::shared_ptr<BaseObject> object) noexcept;

  void
  link_camera(std::shared_ptr<CameraObject> camera_object) noexcept;

  static std::unique_ptr<Engine> _instance;
private:
  std::shared_ptr<Window>       _window;
  std::shared_ptr<CameraObject> _camera_object;

  KeyboardInput _keyboard_input;
  MouseInput    _mouse_input;

  bool _engine_running { true };

  static SDL_Event _event_instance;

  idk::u32 _fps { 60_u32 };

  CursorResource    _cursor_resource;
  ClipboardResource _clipboard_resource;
  TimerResource     _timer_resource;
};
} // namespace fresh
#endif // FRESHENGINE_HPP