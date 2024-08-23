#include <fescript/wrappers/physics/fescript_area_object.hpp>
#include <objects/physics/area_object.hpp>
#include <objects/camera_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptAreaObjectMemberIsCollidingWith::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!this->_self) {
    std::cout << "Engine error: AreaObject is not initialized, yet using AreaObject.is_colliding_with() is not possible.\n";
    std::exit(1);
  }
  if(arguments.empty()) {
    std::cout << "AreaObject.is_colliding_with() must take 1 argument.\n";
    std::exit(1);
  }
  RETURN_MEMBER_FUNCTION(is_colliding_with, "AreaObject.is_colliding_with()")
}

AreaObjectWrapper::AreaObjectWrapper() {
  this->_object_def = "areaobject";
}

AreaObjectWrapper::~AreaObjectWrapper() {

}

[[nodiscard]] std::string AreaObjectWrapper::to_string() {
  return "areaobject";
}

[[nodiscard]] Object AreaObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  auto area_object = std::make_shared<fresh::AreaObject>();
  this->_object_id = area_object->get_object_id();
  return std::move(area_object);
}
} // namespace fescript