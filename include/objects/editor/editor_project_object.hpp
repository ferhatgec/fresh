//
// Created by gech on 2/15/2024.
//

#ifndef FRESHENGINE_EDITOR_PROJECT_OBJECT_HPP
#define FRESHENGINE_EDITOR_PROJECT_OBJECT_HPP

#include "editor_project_color_object.hpp"
#include "editor_project_file_object.hpp"
#include "../../../libs/idk/idk/containers/vector.hpp"

namespace fresh {
class EditorProjectObject : public BaseObject {
public:
  friend class FesLoaderResource;

  EditorProjectObject();
  ~EditorProjectObject();
protected:
  idk::StringViewChar _project_name;
  idk::u32 _default_window_size_w;
  idk::u32 _default_window_size_h;
  std::shared_ptr<EditorProjectColorObject> _default_clear_color;
  idk::StringViewChar _default_fes_file;
  idk::Vector<std::shared_ptr<EditorProjectFileObject>> _preloaded_fes_files;
};
}

#endif // FRESHENGINE_EDITOR_PROJECT_OBJECT_HPP
