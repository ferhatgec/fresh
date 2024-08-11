#pragma once

#include <objects/base_object.hpp>

namespace fresh {
class EditorProjectFileObject : public BaseObject {
public:
  friend class FesLoaderResource;
  friend class Editor;

  EditorProjectFileObject();
  ~EditorProjectFileObject();
protected:
  idk::StringViewChar _file_path;
};
} // namespace fresh