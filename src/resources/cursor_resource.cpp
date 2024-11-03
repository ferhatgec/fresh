#include <stb_image.h>
#include <freshengine.hpp>

#include "log/log.hpp"

namespace fresh {
CursorResource::CursorResource() noexcept {
  this->_sprite.width = this->_sprite.height = -1;
}

CursorResource::~CursorResource() noexcept {
  if(this->_cursor) {
    glfwDestroyCursor(this->_cursor);
  }
}

[[nodiscsard]] const PointResource& CursorResource::get_position() noexcept {
  this->sync_position();
  return this->_pos;
}

[[nodiscard]] const idk::i32& CursorResource::get_w() const noexcept {
  return this->_sprite.width;
}

[[nodiscard]] const idk::i32& CursorResource::get_h() const noexcept {
  return this->_sprite.height;
}

[[nodiscard]] const CursorResource::CursorMode& CursorResource::get_mode() const noexcept {
  return this->_mode;
}

void CursorResource::set_position(const PointResource& pos) noexcept {
  this->_pos = pos;
  // convert pivot from center to top left.
  const auto& coord = PointResource::top_left_transform(
    this->_pos,
    FreshInstance->get_window()->get_width(),
    FreshInstance->get_window()->get_height()
  );
  glfwSetCursorPos(
    Engine::get_instance()->get_window()->get_raw_window(),
    coord.get_x(),
    coord.get_y()
  );
}

void CursorResource::load_sprite(const std::string& sprite_path, idk::i32 w, idk::i32 h) noexcept {
  if(this->_cursor) {
    glfwDestroyCursor(this->_cursor);
  }
  stbi_set_flip_vertically_on_load(true);
  int channels;
  auto* image_data = stbi_load(
    sprite_path.data(),
    &this->_sprite.width,
    &this->_sprite.height,
    &channels,
    0
  );
  if(!image_data) {
    log_error(src(), "corrupted sprite data; path: '{}'", sprite_path);
    return;
  }
  // must be rgba
  if(channels != 4) {
    log_error(src(), "sprite must be in 4 channels; got '{}'.", channels);
    stbi_image_free(image_data);
    return;
  }
  if(w >= 0) {
    this->_sprite.width = w;
  }
  if(h >= 0) {
    this->_sprite.height = h;
  }
  this->_sprite.pixels = image_data;
  this->_cursor = glfwCreateCursor(&this->_sprite, 0, 0);
  if(!this->_cursor) {
    log_error(src(), "cursor initialization failed; path '{}'", sprite_path);
  }
}

// TODO: it might be better if we use callbacks,
// glfwSetCursorPosCallback should work.
void CursorResource::sync_position() noexcept {
  idk::f64 x, y;
  glfwGetCursorPos(
    Engine::get_instance()->get_window()->get_raw_window(),
    &x, &y
  );
  // TODO: we lose precision here; it might be better
  // if we define BBoxResource that takes a template type.
  this->_pos = PointResource::center_transform(
    PointResource { static_cast<idk::f32>(x), static_cast<idk::f32>(y) },
    FreshInstance->get_window()->get_width(),
    FreshInstance->get_window()->get_height()
  );
}

void CursorResource::sync_mode() noexcept {
  const auto& mode = glfwGetInputMode(
    Engine::get_instance()->get_window()->get_raw_window(),
    GLFW_CURSOR
  );
  switch(mode) {
    case GLFW_CURSOR_DISABLED: {
      this->_mode = CursorMode::Disabled;
      break;
    }
    case GLFW_CURSOR_HIDDEN: {
      this->_mode = CursorMode::Hidden;
      break;
    }
    case GLFW_CURSOR_NORMAL:
    default: {
      this->_mode = CursorMode::Normal;
      break;
    }
  }
}

void CursorResource::set_mode(CursorMode mode) noexcept {
  int bitf;
  switch (mode) {
    case CursorMode::Disabled: {
      bitf = GLFW_CURSOR_DISABLED;
      break;
    }
    case CursorMode::Hidden: {
      bitf = GLFW_CURSOR_HIDDEN;
      break;
    }
    case CursorMode::Normal:
    default: {
      bitf = GLFW_CURSOR_NORMAL;
      break;
    }
  }
  glfwSetInputMode(Engine::get_instance()->get_window()->get_raw_window(),
                   GLFW_CURSOR, bitf);
  this->_mode = mode;
}

[[nodiscard]] glm::vec2 CursorResource::get_ndc() noexcept {
  const auto& pos = this->get_position();
  return {
      2 * (pos.get_x() / FreshInstance->get_window()->get_width()) - 1.f,
      -2 * (pos.get_y() / FreshInstance->get_window()->get_height()) + 1.f
  };
}

[[nodiscard]] glm::vec2 CursorResource::get_world_space_position() noexcept {
  const auto& screen_pos = glm::vec4(this->get_ndc().x, this->get_ndc().y, -1.f, 1.f);
  const auto& view_proj_inv = glm::inverse(
    FreshInstance->get_camera()->get_camera()->get_projection_matrix() *
    FreshInstance->get_camera()->get_camera()->get_view_matrix()
  );
  return glm::vec2{view_proj_inv * screen_pos};
}
}  // namespace fresh