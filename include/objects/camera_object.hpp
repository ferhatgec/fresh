//
// Created by gech on 2/3/2024.
//

#ifndef FRESHENGINE_CAMERA_OBJECT_HPP
#define FRESHENGINE_CAMERA_OBJECT_HPP

#include "base_object.hpp"

namespace fresh {
class CameraObject : public BaseObject {
public:
  friend class FesLoaderResource;

  CameraObject();
  ~CameraObject();

  __idk_nodiscard
  bool
  is_visible_on_camera(std::shared_ptr<BaseObject> object) noexcept;

  void
  sync() noexcept override;

  [[nodiscard]] std::string to_string() {
    return "cameraobject";
  }

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;
};
} // namespace fresh

#endif // FRESHENGINE_CAMERA_OBJECT_HPP
