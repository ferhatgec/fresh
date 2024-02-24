#ifndef FRESHENGINE_LABEL_OBJECT_HPP
#define FRESHENGINE_LABEL_OBJECT_HPP

#include "base_object.hpp"
#include "../resources/font_resource.hpp"
#include "../resources/sprite_resource.hpp"

namespace fresh {
enum class LabelRenderType {
  LCD,
  Solid,
  Shaded,
  Blended
};

class LabelObject : public BaseObject {
public:
  friend class FesLoaderResource;

  LabelObject();
  LabelObject(LabelObject* label_object);
  LabelObject(const FontResource& label_font_resource, const BaseObject& metadata);
  LabelObject(FontResource&& label_font_resource, BaseObject&& metadata);

  ~LabelObject();

  void
  initialize_text(const idk::StringViewChar& label_text,
                  SDL_Color fg,
                  SDL_Color bg,
                  LabelRenderType label_render_type) noexcept;

  void
  initialize_text(idk::StringViewChar&& label_text,
                  SDL_Color fg,
                  SDL_Color bg,
                  LabelRenderType label_render_type) noexcept;

  void
  sync() noexcept override;

  __idk_nodiscard
  idk::StringViewChar&
  get_label_text() noexcept;

  __idk_nodiscard
  FontResource&
  get_label_font_resource() noexcept;

  __idk_nodiscard
  SpriteResource&
  get_label_font_texture() noexcept;

  template<typename KeyType>
  KeyType&
  get_property() noexcept {
    return this->_fg;
  }

  template<>
  SpriteResource&
  get_property<SpriteResource>() noexcept {
    return this->_label_font_texture;
  }

  template<>
  FontResource&
  get_property<FontResource>() noexcept {
    return this->_label_font_resource;
  }

  template<>
  idk::StringViewChar&
  get_property<idk::StringViewChar>() noexcept {
    return this->_label_text;
  }

  void
  initialize_label_font_surface() noexcept;
protected:
  SDL_Color _bg;
  SDL_Color _fg;

  LabelRenderType _label_render_type;

  idk::StringViewChar _label_text;

  SpriteResource _label_font_texture;
  FontResource _label_font_resource;
};
} // namespace fresh

#endif // FRESHENGINE_LABEL_OBJECT_HPP