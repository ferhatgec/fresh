#include <freshengine.hpp>

namespace fresh {
EditorProjectColorObject::EditorProjectColorObject()
    : _red(255),
      _green(255),
      _blue(255),
      _alpha(255) {
  this->_object_def = "colorobject";
}

EditorProjectColorObject::~EditorProjectColorObject() {
}
}// namespace fresh