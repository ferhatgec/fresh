// MIT License
//
// Copyright (c) 2024-2025 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_token.hpp>
#include <resources/bbox_resource.hpp>
#include <resources/point_resource.hpp>
#include <resources/color_resource.hpp>
#include <source_location>
#include <types/predefined.hpp>
#include <vector>

#define CHECK_DISABLED() if(this->_disabled) return;

namespace fre2d {
class Texture;
} // namespace fre2d

namespace fresh {
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
  BaseObject();
  virtual ~BaseObject() = default;

  /// BaseObject::get_disabled() is read-only access to _disabled property.
  [[nodiscard]] const bool& get_disabled() const noexcept;

  /// BaseObject::get_visible() is read-only access to _visible property.
  [[nodiscard]] const bool& get_visible() const noexcept;

  /// BaseObject::get_initialized() is read-only access to _initialized
  /// property.
  [[nodiscard]] const bool& get_initialized() const noexcept;

  /// BaseObject::set_disabled(bool) is write-only access to _disabled property.
  void set_disabled(bool disabled) noexcept;

  /// BaseObject::set_visible(bool) is write-only access to _visible property.
  void set_visible(bool visible) noexcept;

  /// BaseObject::sync() applies position/rotation/size changes
  /// and calls attached script every frame.
  /// ----
  /// note: no need to call sync() directly;
  ///       instance of Engine class will do it for you automatically.
  virtual void sync(bool is_member_of_camera = false) noexcept;

  /// BaseObject::apply_changes() iterates over child objects and applies
  /// position/rotation/size changes of parent object.
  /// it does same functionality as this->apply_changes(); from old API; with
  /// C++ interface instead of using preprocessors.
  /// ----
  /// note: no need to call apply_changes() directly;
  ///       sync() will call it for you automatically.
  void apply_changes(bool is_member_of_camera = false) noexcept;

  /// BaseObject::get_position() is read-only access to _pos_info property.
  [[nodiscard]] const BBoxResource& get_position() const noexcept;
  /// BaseObject::set_position(BBoxResource) is write-only access to _pos_info
  /// property.
  void set_position(const BBoxResource& pos) noexcept;

  /// BaseObject::get_x() is read-only access to _pos_info._x property.
  [[nodiscard]] const idk::f32& get_x() const noexcept;
  /// BaseObject::get_y() is read-only access to _pos_info._y property.
  [[nodiscard]] const idk::f32& get_y() const noexcept;
  /// BaseObject::get_w() is read-only access to _pos_info._w property.
  [[nodiscard]] const idk::f32& get_w() const noexcept;
  /// BaseObject::get_h() is read-only access to _pos_info._h property.
  [[nodiscard]] const idk::f32& get_h() const noexcept;
  /// BaseObject::get_color() is read-only access to _color property.
  [[nodiscard]] const ColorResource& get_color() const noexcept;

  /// does not set anything if self is BaseObject.
  virtual void set_flip_vertically(bool flip_vertically) noexcept;
  virtual void set_flip_horizontally(bool flip_horizontally) noexcept;

  /// returns dummy value if self is BaseObject.
  [[nodiscard]] virtual const bool& get_flip_vertically() const noexcept;
  [[nodiscard]] virtual const bool& get_flip_horizontally() const noexcept;

  /// BaseObject::is_imported_from_somewhere() checks if imported_from is empty
  /// or not. if it's empty then given object is not generated from importing
  /// other fes file.
  [[nodiscard]] bool is_imported_from_somewhere() const noexcept;

  /// BaseObject::get_x() is write-only access to _pos_info._x property.
  void set_x(idk::f32 x, const std::source_location& instance = std::source_location::current()) noexcept;
  /// BaseObject::get_y() is write-only access to _pos_info._y property.
  void set_y(idk::f32 y) noexcept;
  /// BaseObject::get_w() is write-only access to _pos_info._w property.
  void set_w(idk::f32 w) noexcept;
  /// BaseObject::get_h() is write-only access to _pos_info._h property.
  void set_h(idk::f32 h) noexcept;
  /// BaseObject::set_color() is write-only access to _color property.
  void set_color(const ColorResource& res) noexcept;

  void lazy_set_x(idk::f32 x) noexcept;
  void lazy_set_y(idk::f32 y) noexcept;
  void lazy_set_w(idk::f32 w) noexcept;
  void lazy_set_h(idk::f32 h) noexcept;

  virtual void notify_x() noexcept;
  virtual void notify_y() noexcept;
  virtual void notify_w() noexcept;
  virtual void notify_h() noexcept;

  /// BaseObject::get_id() is read-only access to _object_id property.
  [[nodiscard]] const idk::u32& get_id() const noexcept;

  /// BaseObject::get_delta() copies current delta values into BBoxResource.
  /// calculation done by _pos_info - _copy_last_pos_info.
  [[nodiscard]] BBoxResource get_delta() const noexcept;

  /// BaseObject::get_delta_x() copies and calculates current delta x.
  [[nodiscard]] idk::f32 get_delta_x() const noexcept;
  /// BaseObject::get_delta_y() copies and calculates current delta y.
  [[nodiscard]] idk::f32 get_delta_y() const noexcept;
  /// BaseObject::get_delta_w() copies and calculates current delta w.
  [[nodiscard]] idk::f32 get_delta_w() const noexcept;
  /// BaseObject::get_delta_h() copies and calculates current delta h.
  [[nodiscard]] idk::f32 get_delta_h() const noexcept;
  /// BaseObject::get_delta_rot() copies and calculates current delta rotation.
  [[nodiscard]] idk::f32 get_delta_rot() const noexcept;

  /// BaseObject::get_fescript_path() is read-only access to script_file_name
  /// property.
  [[nodiscard]] const std::string& get_fescript_path() const noexcept;

  /// BaseObject::reset_delta() sets delta values to 0.
  void reset_delta() noexcept;

  /// BaseObject::push_object(std::shared_ptr<BaseObject>) pushes given object
  /// into child object list.
  void push_object(std::shared_ptr<BaseObject> sub_object) noexcept;

  /// BaseObject::to_string() returns lowercase object class name.
  [[nodiscard]] virtual constexpr const char* to_string() noexcept {
    return "baseobject";
  }

  virtual void set(const fescript::Token& name, fescript::Object value);
  virtual void init_signal() noexcept {}

  /// BaseObject::sync_init() pushes initialize signal for every child object
  void sync_init() noexcept;

  /// BaseObject::get_childs() returns a reference of container where
  /// all child objects are stored. you can change or even nullptr it.
  [[nodiscard]] std::vector<std::shared_ptr<BaseObject>>& get_childs() noexcept;

  /// BaseObject::get_name() returns current name of object.
  [[nodiscard]] const std::string& get_name() const noexcept;

  /// BaseObject::set_name(std::string) is write-only access to _name property.
  void set_name(const std::string& name) noexcept;

  /// BaseObject::load_fescript_rt(std::string, bool) loads given script
  /// that can be either file or script's content; then loads it using fescript
  /// parser and interpreter classes. first run of script must be done since
  /// global variables are only read and assigned once; then only functions
  /// are being called.
  /// --------
  /// fun fact: i don't remember what _rt stands for.
  void load_fescript_rt(const std::string& script, bool is_file = false) noexcept;

  /// BaseObject::get_object_by_path(std::string) splits given path
  /// by '/' or '\' -depends on filesystem- then walks through to the parent
  /// or child objects.
  /// ----
  /// note: ".."  will let you access to parent object;
  /// meanwhile "." will point to current object.
  [[nodiscard]] const std::shared_ptr<BaseObject>& get_object_by_path(const std::string& path) noexcept;

  /// BaseObject::get_rotation() returns current rotation angle by radian
  /// degrees.
  [[nodiscard]] const idk::f32& get_rotation() const noexcept;

  /// BaseObject::set_rotation(float) sets current rotation to given
  /// rad_degrees. this method is overridable because some classes creates new
  /// resources in-place upon rotation changes to cache it then use.
  virtual void set_rotation(idk::f32 rad_degrees) noexcept;

  [[nodiscard]] static idk::f32 counter_clockwise_to_clockwise(idk::f32 rad_degrees) noexcept;

  [[nodiscard]] static inline bool are_textures_same(
    const std::optional<fre2d::Texture>& tex1,
    const fre2d::Texture& tex2
  ) noexcept;

  static void sync_textures_if_necessary(std::optional<fre2d::Texture>& tex1, fre2d::Texture& tex2) noexcept;

  std::unordered_map<std::string_view, std::shared_ptr<fescript::FescriptCallable>> cache_fn;
 private:
  /// BaseObject::_give_shared_ptr() mimics std::enable_shared_from_this when
  /// multiple inheritance applied to the class; creates additional shared_ptr
  /// that constructed only for once from this pointer; then used over and over
  /// again. normally you don't need this so this is private; since every
  /// objects should use shared_ptr by default instead of raw pointers. since
  /// fresh not multithreaded; there should be no problem to change what it
  /// points to.
  [[nodiscard]] const std::shared_ptr<BaseObject>& _give_shared_ptr() noexcept;

  /// BaseObject::_get_object_by_single_path returns an object that takes only
  /// one name which is extracted using
  /// BaseObject::get_object_by_path(std::string).
  /// BaseObject::get_object_by_path(std::string) iterates over every name;
  /// then calls BaseObject::_get_object_by_single_path(std::string).
  [[nodiscard]] const std::shared_ptr<BaseObject>& _get_object_by_single_path(
      const std::string& path) noexcept;

  /// BaseObject::_shared_ptr_this stores what _give_shared_ptr() returns.
  std::shared_ptr<BaseObject> _shared_ptr_this;
 protected:
  /// BaseObject::_sub_objects stores child objects.
  std::vector<std::shared_ptr<BaseObject>> _sub_objects;
  /// BaseObject::_parent points to parent object; by default it's nullptr.
  std::shared_ptr<BaseObject> _parent = nullptr;

  bool _disabled, _visible;

  idk::f32 _rotation_degrees, _last_rotation_degrees;
  BBoxResource _pos_info, _copy_last_pos_info;
  ColorResource _color;
  idk::u32 _object_id;

  std::string _name;

  /// _code property is fescript instance of given fescript code, also one copy
  /// is stored in this BaseObject.
  fescript::Interpreter _code;

  /// script_file_name property stores fescript code path.
  std::string script_file_name;

  /// script_content property stores fescript code of this BaseObject.
  std::string script_content;

  /// imported_from property stores path of fes scene where this BaseObject
  /// imported from.
  std::string imported_from;

  bool _member_of_camera;
  bool _initialized;

  friend class SpriteObject;
  friend class LabelObject;
  friend class AreaObject;
  friend class RectangleAreaObject;
  friend class CircleAreaObject;
  friend class PolygonAreaObject;
  friend class CameraObject;
  friend class FesLoaderResource;
  friend class AudioPlayerObject;
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
  friend class fescript::Interpreter;
};
} // namespace fresh