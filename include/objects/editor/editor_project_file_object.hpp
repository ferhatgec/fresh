//
// Created by gech on 2/15/2024.
//

#ifndef FRESHENGINE_EDITOR_PROJECT_FILE_OBJECT_HPP
#define FRESHENGINE_EDITOR_PROJECT_FILE_OBJECT_HPP

#include "../base_object.hpp"

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

#endif // FRESHENGINE_EDITOR_PROJECT_FILE_OBJECT_HPP
