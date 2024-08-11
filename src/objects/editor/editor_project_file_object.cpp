#include <freshengine.hpp>

namespace fresh {
EditorProjectFileObject::EditorProjectFileObject()
    : _file_path("") {
  this->_object_def = "fileobject";
}

EditorProjectFileObject::~EditorProjectFileObject() {
}
}// namespace fresh