#include <freshengine.hpp>

namespace fresh {
void KeyboardInput::init() noexcept {
  glfwSetKeyCallback(Engine::get_instance()->get_window()->get_raw_window(),
                     KeyboardInput::key_state_cb);
}

void KeyboardInput::reset_states() noexcept {
  std::ranges::for_each(KeyboardInput::keys, [](auto& c) noexcept {
    c.just_pressed = c.released = false;
  });
}

[[nodiscard]] const bool& KeyboardInput::is_key_pressed(idk::i32 key) noexcept {
  // no bounds checking done here.
  return KeyboardInput::keys[key].pressed;
}

[[nodiscard]] const bool& KeyboardInput::is_key_just_pressed(idk::i32 key) noexcept {
  return KeyboardInput::keys[key].just_pressed;
}

[[nodiscard]] const bool& KeyboardInput::is_key_released(idk::i32 key) noexcept {
  return KeyboardInput::keys[key].released;
}

void KeyboardInput::key_state_cb(GLFWwindow* window,
                                 idk::i32 key,
                                 idk::i32 scancode,
                                 idk::i32 action,
                                 idk::i32 mods) {
  // no unicode support for now.
  if(key < 0 || key >= KeyboardInput::keys.size()) {
    log_info(src(), "given key value is out of bounds (might be unicode character): '{}'", key);
    return;
  }
  switch(action) {
    case GLFW_PRESS: {
      if(!keys[key].pressed) {
        keys[key].just_pressed = true;
      }
      keys[key].pressed = true;
      break;
    }
    case GLFW_RELEASE: {
      keys[key].pressed = false;
      keys[key].released = true;
      break;
    }
  }
}
}  // namespace fresh