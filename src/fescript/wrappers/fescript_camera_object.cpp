#include "../../../include/fescript/wrappers/fescript_camera_object.hpp"
#include "../../../include/objects/camera_object.hpp"

namespace fescript {
__idk_nodiscard Object FescriptCameraObjectMemberIsVisibleOnCamera::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!this->_self) {
    std::cout << "Engine error: CameraObject is not initialized, yet using CameraObject.is_visible_on_camera() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "CameraObject.is_visible_on_camera() must take 1 argument.\n";
    std::exit(1);
  }
  RETURN_MEMBER_FUNCTION(is_visible_on_camera, "CameraObject.is_visible_on_camera()")
}

CameraObjectWrapper::CameraObjectWrapper() {
  this->_object_def = "cameraobject";
}

CameraObjectWrapper::~CameraObjectWrapper() noexcept {

}

[[nodiscard]] std::string CameraObjectWrapper::to_string() {
  return "cameraobject";
}

[[nodiscard]] Object CameraObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto camera_object = std::make_shared<fresh::CameraObject>();
  this->_object_id = camera_object->get_object_id();
  return std::move(camera_object);
}
} // namespace fescript