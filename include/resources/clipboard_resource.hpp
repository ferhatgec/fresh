#pragma once

#include <string>

namespace fresh {
// maybe adding history is can be great idea but also it can be done by developer easily.
// no need to bloat ClipboardResource for that thing.
class ClipboardResource {
public:
  ClipboardResource() noexcept = default;
  ~ClipboardResource() noexcept = default;

  [[nodiscard]] const std::string& get_clipboard_data() noexcept;

  void set_clipboard_data(const std::string& text) noexcept;
  void sync_clipboard_data() noexcept;
private:
  std::string _clipboard_data;
};
} // namespace fresh