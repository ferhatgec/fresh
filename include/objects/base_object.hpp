#pragma once

#include <vector>

#include <types/predefined.hpp>
#include <types/stringview.hpp>
#include <utilities/type_traits.hpp>

#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_token.hpp>

#include "../../libs/SDL/include/SDL.h"


#define APPLY_DELTAS() for(auto& object: this->_sub_objects) { \
                        object->_pos_info.x += this->delta_x(); \
                        object->_pos_info.y += this->delta_y(); \
                        object->_pos_info.w += this->delta_w(); \
                        object->_pos_info.h += this->delta_h(); \
                        object->sync(is_sync_with_camera); \
                        object->get_position_info(); \
                       } \
                       this->get_position_info();

namespace fresh {
// BaseObject is must be inherited if any object gonna be rendered with any position
// visibility etc. data.
class BaseObject {
public:
  friend class SpriteObject; // all predefined objects are friend class of BaseObject by default.
  friend class LabelObject;
  friend class AreaObject;
  friend class RectangleAreaObject;
  friend class CircleAreaObject;
  friend class PolygonAreaObject;
  friend class CollisionObject;
  friend class CameraObject;
  friend class FesLoaderResource;
  friend class GuiBaseObject;
  friend class GuiButtonObject;
  friend class AudioPlayerObject;
  friend class MusicPlayerObject;
  friend class AnimationPlayerObject;
  friend class AnimationFrameObject;
  friend class CircleObject;
  friend class PolygonObject;
  friend class RectangleObject;
  friend class Engine;
  friend class Editor;
  friend class fescript::Interpreter;

  BaseObject();
  BaseObject(bool disabled, bool visible, idk::i32 pos_x, idk::i32, idk::i32 width, idk::i32 height);

  virtual ~BaseObject();

  __idk_nodiscard
  bool&
  get_is_disabled() noexcept;

  __idk_nodiscard
  bool&
  get_is_visible() noexcept;

  void
  set_disabled(bool disabled) noexcept;

  void
  set_visible(bool visible) noexcept;

  virtual void
  sync_pos_with_camera(bool is_sync_with_camera = false) noexcept;

  virtual void
  sync(bool is_sync_with_camera = false) noexcept; // sync your *object*, pass through the renderer every frame

  __idk_nodiscard
  virtual SDL_FRect&
  get_position_info() noexcept;

  __idk_nodiscard
  SDL_FRect&
  get_raw_position_info() noexcept;

  __idk_nodiscard
  const idk::u64&
  get_object_id() noexcept;

  __idk_nodiscard
  idk::f32
  delta_x() noexcept;

  __idk_nodiscard
  idk::f32
  delta_y() noexcept;

  __idk_nodiscard
  idk::f32
  delta_w() noexcept;

  __idk_nodiscard
  idk::f32
  delta_h() noexcept;

  void
  push_object(std::shared_ptr<BaseObject> sub_object) noexcept;

  [[nodiscard]] std::string to_string() { return "baseobject"; }
  virtual void set(const fescript::Token& name, fescript::Object value);

  __idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>&
  get_sub_objects() noexcept;

  __idk_nodiscard
  idk::StringViewChar&
  get_name() noexcept;

  void load_fescript_rt(const idk::StringViewChar& script, bool is_file = false) noexcept;

  void push_to_sub_objects(std::shared_ptr<BaseObject> obj) noexcept;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  get_object_by_path(const std::string& path) noexcept;

private:
  [[nodiscard]]
  std::shared_ptr<BaseObject>
  _give_shared_ptr() noexcept;

  std::shared_ptr<BaseObject> _shared_ptr_this;
protected:
  idk::StringViewChar _object_def;
  std::vector<std::shared_ptr<BaseObject>> _sub_objects;
  std::shared_ptr<BaseObject> _parent = nullptr;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  _get_object_by_single_path(const std::string& path) noexcept;

  bool _disabled { false };
  bool _visible { true };
  bool _block_transform { false };

  SDL_FRect _pos_info;
  SDL_FRect _render_pos_info;

  SDL_FRect _blocked_pos_info; // we return this to block the changing of _pos_info.
  SDL_FRect _copy_last_pos_info; // it's here to calculate velocity
  idk::i64 _object_id;

  idk::StringViewChar _name;

  fescript::Interpreter _code;
  idk::StringViewChar script_file_name;
  idk::StringViewChar script_content;
  idk::StringViewChar imported_from;
};
} // namespace fresh