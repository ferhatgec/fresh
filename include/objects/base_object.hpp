#pragma once

#include <vector>
#include <numbers>
#include <concepts>

#include <types/predefined.hpp>
#include <types/stringview.hpp>
#include <utilities/type_traits.hpp>

#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_token.hpp>

#include <resources/point_resource.hpp>

#include "../../libs/SDL/include/SDL.h"

#define CHECK_DISABLED() if(this->_disabled) return;
#define APPLY_DELTAS() for(auto& object: this->_sub_objects) { \
                        object->_pos_info.x += this->delta_x(); \
                        object->_pos_info.y += this->delta_y(); \
                        object->_pos_info.w += this->delta_w(); \
                        object->_pos_info.h += this->delta_h(); \
                        object->set_rotation_by_radian_degrees(object->get_rotation_by_radian_degrees() + this->delta_rot()); \
                        object->sync(is_sync_with_camera); \
                        object->get_position_info(); \
                        object->get_is_visible() = this->get_is_visible(); \
                        object->get_is_disabled() = this->get_is_disabled(); \
                       } \
                       this->_last_rotation_degrees = this->_rotation_degrees; \
                       this->get_position_info();

namespace fresh {
template<std::floating_point Fp>
inline constexpr Fp mul_2_pi_v = static_cast<Fp>(2) * std::numbers::pi_v<Fp>;

enum : idk::u8 {
  PosXIndex,
  PosYIndex,
  WidthIndex,
  HeightIndex
};

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
  friend class BodyObject;
  friend class RectangleBodyObject;
  friend class CircleBodyObject;
  friend class PolygonBodyObject;
  friend class WorldObject;
  friend class Engine;
  friend class Editor;
  friend class fescript::Interpreter;

  BaseObject();
  BaseObject(bool disabled, bool visible, idk::f32 pos_x, idk::f32, idk::f32 width, idk::f32 height, idk::f32 rotation_degrees = 0.f);

  virtual ~BaseObject();

  __idk_nodiscard
  bool& get_is_disabled() noexcept;

  __idk_nodiscard
  bool& get_is_visible() noexcept;

  void set_disabled(bool disabled) noexcept;
  void set_visible(bool visible) noexcept;

  virtual void sync_pos_with_camera(bool is_sync_with_camera = false) noexcept;
  virtual void sync(bool is_sync_with_camera = false) noexcept; // sync your *object*, pass through the renderer every frame

  __idk_nodiscard
  virtual SDL_FRect& get_position_info() noexcept;

  __idk_nodiscard
  SDL_FRect& get_raw_position_info() noexcept;

  __idk_nodiscard
  SDL_FRect& get_render_position_info() noexcept;

  __idk_nodiscard
  const idk::u32& get_object_id() noexcept;

  __idk_nodiscard
  idk::f32 delta_x() noexcept;

  __idk_nodiscard
  idk::f32 delta_y() noexcept;

  __idk_nodiscard
  idk::f32 delta_w() noexcept;

  __idk_nodiscard
  idk::f32 delta_h() noexcept;

  __idk_nodiscard
  idk::f32 delta_rot() noexcept;

  void push_object(std::shared_ptr<BaseObject> sub_object) noexcept;

  [[nodiscard]] std::string to_string() { return "baseobject"; }
  virtual void set(const fescript::Token& name, fescript::Object value);

  __idk_nodiscard
  std::vector<std::shared_ptr<BaseObject>>& get_sub_objects() noexcept;

  __idk_nodiscard
  idk::StringViewChar& get_name() noexcept;

  void load_fescript_rt(const idk::StringViewChar& script, bool is_file = false) noexcept;
  void push_to_sub_objects(std::shared_ptr<BaseObject> obj) noexcept;

  [[nodiscard]] SDL_FRect copy_get_position_info() const noexcept {
    return this->_pos_info;
  }

  __idk_nodiscard
  std::shared_ptr<BaseObject> get_object_by_path(const std::string& path) noexcept;

  [[nodiscard]]
  const idk::f32& get_rotation_by_radian_degrees() const noexcept;

  virtual void set_rotation_by_radian_degrees(idk::f32 rad_degrees) noexcept;

  [[nodiscard]] static idk::f32 counter_clockwise_to_clockwise(idk::f32 rad_degrees) noexcept;
private:
  [[nodiscard]]
  std::shared_ptr<BaseObject> _give_shared_ptr() noexcept;

  [[nodiscard]]
  static SDL_FRect _center_to_top_left_pivot(SDL_FRect pos_size) noexcept;

  std::shared_ptr<BaseObject> _shared_ptr_this;
protected:
  idk::StringViewChar _object_def;
  std::vector<std::shared_ptr<BaseObject>> _sub_objects;
  std::shared_ptr<BaseObject> _parent = nullptr;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  _get_object_by_single_path(const std::string& path) noexcept;

  __idk_nodiscard static PointResource _rectangle_convert_to_top_left(const SDL_FRect& pos) noexcept;
  __idk_nodiscard static PointResource _rectangle_convert_to_top_right(const SDL_FRect& pos) noexcept;
  __idk_nodiscard static PointResource _rectangle_convert_to_bottom_left(const SDL_FRect& pos) noexcept;
  __idk_nodiscard static PointResource _rectangle_convert_to_bottom_right(const SDL_FRect& pos) noexcept;

  bool _disabled { false };
  bool _visible { true };
  bool _block_transform { false };

  idk::f32 _rotation_degrees;
  idk::f32 _last_rotation_degrees;

  SDL_FRect _pos_info;
  SDL_FRect _render_pos_info;

  SDL_FRect _blocked_pos_info; // we return this to block the changing of _pos_info.
  SDL_FRect _copy_last_pos_info; // it's here to calculate velocity
  idk::u32 _object_id;

  idk::StringViewChar _name;

  fescript::Interpreter _code;
  idk::StringViewChar script_file_name;
  idk::StringViewChar script_content;
  idk::StringViewChar imported_from;
};
} // namespace fresh