#include <freshengine.hpp>
#include "../../libs/SDL_image/include/SDL_image.h"

// TODO: sprite batching?
namespace fresh {
SpriteResource::SpriteResource() {
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF) == 0) {
    std::cout << "Engine error: Cannot initialize SpriteResource back end.\n";
    return;
  }
}

SpriteResource::SpriteResource(const idk::StringViewChar& sprite_file) {
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF) == 0) {
    std::cout << "Engine error: Cannot initialize SpriteResource back end.\n";
    return;
  }

  this->_texture_path = sprite_file;
  this->_sprite_texture = IMG_LoadTexture(Engine::get_instance()->get_window()->get_renderer(), sprite_file.data());
}

SpriteResource::SpriteResource(idk::StringViewChar&& sprite_file) {
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF) == 0) {
    std::cout << "Engine error: Cannot initialize SpriteResource back end.\n";
    return;
  }

  this->_texture_path = sprite_file;
  this->_sprite_texture = IMG_LoadTexture(Engine::get_instance()->get_window()->get_renderer(), idk::move(sprite_file).data());
}

SpriteResource::SpriteResource(const SpriteResource& sprite_resource) {
  if(this->_sprite_texture) {
    SDL_DestroyTexture(this->_sprite_texture);
  }

  _texture_path = sprite_resource._texture_path;
  this->_sprite_texture = const_cast<SpriteResource&>(sprite_resource)._sprite_texture;
  this->_sprite_blend_mode = sprite_resource._sprite_blend_mode;
}

SpriteResource::SpriteResource(SpriteResource&& sprite_resource) {
  if(this->_sprite_texture) {
    SDL_DestroyTexture(this->_sprite_texture);
  }

  _texture_path = idk::move(sprite_resource._texture_path);
  this->_sprite_texture = idk::move(sprite_resource._sprite_texture);
  this->_sprite_blend_mode = idk::move(sprite_resource._sprite_blend_mode);
}

SpriteResource::~SpriteResource() {
  if(this->_sprite_texture) {
    SDL_DestroyTexture(this->_sprite_texture);
  }
}

__idk_nodiscard
  SDL_Texture*&
  SpriteResource::get_texture() noexcept {
  // if(!this->_sprite_texture) {
  //   std::cout << "Engine info: SpriteResource is not initialized, initialize it then call SpriteResource::get_texture()\n";
  //   return this->_sprite_texture; // nullptr
  // }
  // we use different approach to set data by returning data as reference so you can change member _sprite_texture directly.

  return this->_sprite_texture;
}

__idk_nodiscard
  SpriteBlendMode&
  SpriteResource::get_blend_mode() noexcept {
  return this->_sprite_blend_mode;
}

void
SpriteResource::load_resource(const idk::StringViewChar& sprite_file) noexcept {
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF) == 0) {
    std::cout << "Engine error: Cannot initialize SpriteResource back end.\n";
    return;
  }

  _texture_path = sprite_file;
  this->_sprite_texture = IMG_LoadTexture(Engine::get_instance()->get_window()->get_renderer(), sprite_file.data());
}

void
SpriteResource::load_resource(idk::StringViewChar&& sprite_file) noexcept {
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF) == 0) {
    std::cout << "Engine error: Cannot initialize SpriteResource back end.\n";
    return;
  }

  _texture_path = sprite_file;
  this->_sprite_texture = IMG_LoadTexture(Engine::get_instance()->get_window()->get_renderer(), idk::move(sprite_file).data());
}

__idk_nodiscard
  SpriteResource&
  SpriteResource::operator=(const SpriteResource& right) noexcept {
  this->_sprite_texture = right._sprite_texture;
  this->_texture_path = right._texture_path;
  this->_sprite_blend_mode = right._sprite_blend_mode;

  return *this;
}

__idk_nodiscard
  SpriteResource&
  SpriteResource::operator=(SpriteResource&& right) noexcept {
  this->_sprite_texture = idk::move(right._sprite_texture);
  this->_texture_path = idk::move(right._texture_path);
  this->_sprite_blend_mode = idk::move(right._sprite_blend_mode);

  return *this;
}
}// namespace fresh