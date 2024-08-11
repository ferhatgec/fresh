#pragma once

#include <types/predefined.hpp>

namespace fresh {
class CircleResource {
public:
  friend class CircleObject;

  CircleResource(idk::f32 radius = 16.0f, idk::i32 segments = 0, bool is_filled = true) noexcept;
  ~CircleResource() noexcept;

  __idk_nodiscard
  idk::f32& get_radius() noexcept;

  __idk_nodiscard
  idk::i32& get_segments() noexcept;

  __idk_nodiscard
  bool& get_is_filled() noexcept;
private:
  idk::f32 _radius;
  idk::i32 _segments;
  bool _is_filled;
};
} // namespace fresh