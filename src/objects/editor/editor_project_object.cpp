#include "../../../include/freshengine.hpp"

namespace fresh {
EditorProjectObject::EditorProjectObject()
    : _project_name(""),
      _default_window_size_w(960),
      _default_window_size_h(480),
      _default_fes_file("") {
  this->_default_clear_color = std::make_shared<EditorProjectColorObject>();
  this->_object_def = "projectobject";
}

EditorProjectObject::~EditorProjectObject() {
}
}// namespace fresh