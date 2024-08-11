#pragma once

#include <objects/base_object.hpp>

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