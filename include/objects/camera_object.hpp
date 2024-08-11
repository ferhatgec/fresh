#pragma once

#include "base_object.hpp"

namespace fresh {
class CameraObject : public BaseObject {
public:
  friend class FesLoaderResource;
  friend class Engine;

  CameraObject();
  ~CameraObject();

  __idk_nodiscard
  bool
  is_visible_on_camera(std::shared_ptr<BaseObject> object) noexcept;

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] std::string to_string() {
    return "cameraobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  SDL_FRect get_viewport() noexcept {
    return {
      this->_pos_info.x - this->_pos_info.w / (2 * this->_zoom_level),
      this->_pos_info.y - this->_pos_info.h / (2 * this->_zoom_level),
      this->_pos_info.w / this->_zoom_level,
      this->_pos_info.h / this->_zoom_level
    };
  }

  void apply(std::shared_ptr<BaseObject> obj) noexcept;
  void set_zoom(idk::f32 new_zoom) noexcept;
  void move(idk::f32 dx, idk::f32 dy) noexcept;
protected:
  idk::f32 _zoom_level, _scale_ratio_w, _scale_ratio_h;
};
} // namespace fresh