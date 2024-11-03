#include <resources/font_resource.hpp>
#include <freshengine.hpp>

namespace fresh {
FontResource::FontResource() noexcept : _font_size{16} {
  this->_font = std::make_shared<fre2d::Font>();
}

FontResource::FontResource(const std::string& font_path, idk::u32 default_size) noexcept {
  this->_font = std::make_shared<fre2d::Font>();
  this->_font_size = default_size;
  this->load_font(font_path);
}

void FontResource::load_font(const std::string& font_path) noexcept {
  this->_font_path = font_path;
  this->_font->initialize_font(
    Engine::get_instance()->_font_manager,
    font_path.c_str(),
    32
  );
}

[[nodiscard]] const std::string& FontResource::get_font_path() noexcept {
  return this->_font_path;
}

[[nodiscard]] const idk::u32& FontResource::get_font_size() const noexcept {
  return this->_font_size;
}

void FontResource::set_font_size(idk::u32 font_size) noexcept {
  this->_font_size = font_size;
  this->load_font(this->get_font_path());
}

[[nodiscard]] fre2d::Font& FontResource::get_font() noexcept {
  return *this->_font;
}
}  // namespace fresh