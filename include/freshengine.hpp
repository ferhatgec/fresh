#pragma once

#include "application/window.hpp"

#include "input/keyboard_input.hpp"
#include "input/mouse_input.hpp"

#include "objects/base_object.hpp"
#include "objects/sprite_object.hpp"
#include "objects/label_object.hpp"
#include "objects/physics/area_object.hpp"
#include "objects/physics/world_object.hpp"
#include "objects/physics/body_object.hpp"
#include "objects/physics/rectangle_body_object.hpp"
#include "objects/physics/circle_body_object.hpp"
#include "objects/physics/polygon_body_object.hpp"
#include "objects/camera_object.hpp"

#include "resources/sprite_resource.hpp"
#include "resources/timer_resource.hpp"
#include "resources/cursor_resource.hpp"
#include "resources/font_resource.hpp"
#include "resources/clipboard_resource.hpp"
#include "resources/audio_resource.hpp"
#include "resources/fes_loader_resource.hpp"

#include "fes/fes_ast.hpp"
#include "fes/fes_keywords.hpp"
#include "fes/fes_parser.hpp"
#include "fes/fes_tokenizer.hpp"

#include "render_objects.hpp"
#include "resources/polygon_resource.hpp"
#include "log/log.hpp"

#include <any>
#include <memory>
#include <vector>

#include "renderer.hpp"
#include <thread>

// it can be changed after definition, that's here for guarantee.
#ifdef FreshInstanceInit
# undef FreshInstanceInit
#endif

#define FreshInstanceInit() fresh::Engine::_instance = std::unique_ptr<fresh::Engine>(dynamic_cast<fresh::Engine*>(this))
#define FreshInstance fresh::Engine::get_instance()

namespace fresh {
class Engine {
 public:
  /// Engine::Engine() is constructor of Engine class.
  /// it is called automatically.
  Engine() noexcept;

  /// Engine::~Engine() is destructor of Engine class. override it for your
  /// game that derives Engine class.
  virtual ~Engine() noexcept = default;

  /// Engine::get_instance() returns active global instance of Engine class.
  /// if there is not; then creates one.
  [[nodiscard]] static std::unique_ptr<Engine>& get_instance() noexcept;

  /// Engine::get_window() returns current active window.
  [[nodiscard]] std::shared_ptr<Window>& get_window() noexcept;

  /// Engine::update() is overridable method that is called right before
  /// draw calls are applied to the framebuffer.
  virtual void update();

  /// Engine::init() is overridable method that is called right after
  /// first initialization of all objects is done.
  virtual void init();

  /// Engine::last() is overridable method that is called at the end of
  /// Engine::run() method; might be great fit for deallocating resources or
  /// for debugging purposes.
  virtual void last();

  /// Engine::run() does the required calls; like doing first initialization;
  /// delta time calculation; handling input/outputs, etc.
  void run();

  /// Engine::get_engine_running() returns _engine_running property;
  /// which used for checking if engine encountered any errors.
  /// to exit safely without leaking memory;
  /// use Engine::set_engine_running() method. it will check the value of
  /// _engine_running property 1 tick after.
  [[nodiscard]] const bool& get_engine_running() const noexcept;

  /// Engine::set_engine_running(bool) is write-only access to the
  /// _engine_running property. set _engine_running to false; to stop render
  /// loop after 1 tick.
  void set_engine_running(bool engine_running) noexcept;

  __idk_nodiscard KeyboardInput& get_keyboard_input() noexcept;

  __idk_nodiscard MouseInput& get_mouse_input() noexcept;

  __idk_nodiscard CursorResource& get_cursor_resource() noexcept;

  __idk_nodiscard ClipboardResource& get_clipboard_resource() noexcept;

  [[nodiscard]] fre2d::FontManager& get_font_manager() noexcept;

  /// Engine::link_camera(std::shared_ptr<CameraObject>) links given camera
  /// with Engine-backed camera instance.
  void link_camera(std::shared_ptr<CameraObject> camera_object) noexcept;

  /// Engine::get_camera() returns current Engine-backed/bounded Camera.
  [[nodiscard]] static const std::shared_ptr<CameraObject>&
  get_camera() noexcept;

  /// Engine::get_id() returns global id that counts how many objects
  /// have been created. not thread-safe; generally fresh isn't thread-safe too.
  [[nodiscard]] static const idk::u32& get_id() noexcept;

  /// Engine::increase_global_id() increases global id by 1.
  static void increase_global_id() noexcept;

  /// Engine::reset_global_id() resets global id to 0.
  static void reset_global_id() noexcept;

  static std::unique_ptr<Engine> _instance;
 private:
  friend class FontResource;

  std::shared_ptr<Window> _window;
  std::shared_ptr<CameraObject> _camera_object;

  KeyboardInput _keyboard_input;
  MouseInput _mouse_input;
  fre2d::FontManager _font_manager;

  bool _engine_running{true};

  idk::u32 _fps{60_u32};

  CursorResource _cursor_resource;
  ClipboardResource _clipboard_resource;
  TimerResource _timer_resource;

  static inline idk::u32 _id{0};
};
} // namespace fresh