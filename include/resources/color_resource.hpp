#pragma once

#include <types/predefined.hpp>

namespace fresh {
class ColorResource {
public:
  ColorResource(idk::u8 r = 0, idk::u8 g = 0, idk::u8 b = 0, idk::u8 a = 255) noexcept;
  ~ColorResource();

  // FIXME: we must get rid of these functions. (not the priority but should be easy to do, just a bit duplicated code)
  // _r can get any value as it is not checked after any value assign operation performed.
  __idk_nodiscard
  idk::u8& get_red() noexcept;

  __idk_nodiscard
  idk::u8& get_green() noexcept;

  __idk_nodiscard
  idk::u8& get_blue() noexcept;

  __idk_nodiscard
  idk::u8& get_alpha() noexcept;
protected:
  idk::u8 _r, _g, _b, _a;
};
} // namespace fresh