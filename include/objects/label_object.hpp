#pragma once

#include "base_object.hpp"
#include <resources/font_resource.hpp>
#include <resources/sprite_resource.hpp>

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
  sync(bool is_sync_with_camera = false) noexcept override;

  __idk_nodiscard
  idk::StringViewChar&
  get_label_text() noexcept;

  __idk_nodiscard
  FontResource&
  get_label_font_resource() noexcept;

  __idk_nodiscard
  SpriteResource&
  get_label_font_texture() noexcept;

  void
  initialize_label_font_surface() noexcept;

  [[nodiscard]] std::string to_string() {
    return "labelobject";
  }

  void set(const fescript::Token& name, fescript::Object value) override;

  [[nodiscard]] SDL_Color& get_background_color() noexcept {
    return this->_bg;
  }

  [[nodiscard]] SDL_Color& get_foreground_color() noexcept {
    return this->_fg;
  }
protected:
  SDL_Color _bg;
  SDL_Color _fg;

  LabelRenderType _label_render_type;

  idk::StringViewChar _label_text;

  SpriteResource _label_font_texture;
  FontResource _label_font_resource;
};
} // namespace fresh