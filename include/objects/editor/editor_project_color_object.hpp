//
// Created by gech on 2/15/2024.
//

#ifndef FRESHENGINE_EDITOR_PROJECT_COLOR_OBJECT_HPP
#define FRESHENGINE_EDITOR_PROJECT_COLOR_OBJECT_HPP

#include "../base_object.hpp"

namespace fresh {
class EditorProjectColorObject : public BaseObject {
public:
  friend class FesLoaderResource;

  EditorProjectColorObject();
  ~EditorProjectColorObject();
protected:
  idk::u32 _red;
  idk::u32 _green;
  idk::u32 _blue;
  idk::u32 _alpha;
};
} // namespace fresh

#endif // FRESHENGINE_EDITOR_PROJECT_COLOR_OBJECT_HPP
