#ifndef FRESHENGINE_CURSOR_RESOURCE_HPP
#define FRESHENGINE_CURSOR_RESOURCE_HPP

#include "sprite_resource.hpp"

// cursorresource is not an object,
// it maybe seems much better to use SpriteObject instead of SpriteResource with SDL_Rect but
// we don't need any position info of our cursor at *scene*.
namespace fresh {
class CursorResource {
public:
  CursorResource();
  CursorResource(const SpriteResource& cursor_sprite);
  CursorResource(SpriteResource&& cursor_sprite);

  ~CursorResource();

  virtual void
  init_cursor() noexcept; // you can override init_cursor() to change show_cursor from false to true,
                          // or just for other things.

  __idk_nodiscard
  SpriteResource&
  get_cursor_sprite() noexcept;

  __idk_nodiscard
  SDL_Rect&
  get_position_info() noexcept;

  void
  sync_position() noexcept;

  void
  sync_sprite() noexcept;

  void
  show_cursor(bool show) noexcept;

  __idk_nodiscard
  CursorResource&
  operator=(const CursorResource& right) noexcept;

  __idk_nodiscard
  CursorResource&
  operator=(CursorResource&& right) noexcept;
private:
  SpriteResource _cursor_sprite;
  SDL_Rect _pos_info;
};
} // namespace fresh
#endif // FRESHENGINE_CLIPBOARD_RESOURCE_HPP