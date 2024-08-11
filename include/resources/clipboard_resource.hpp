#pragma once

#include <types/stringview.hpp>

namespace fresh {
// maybe adding history is can be great idea but also it can be done by developer easily.
// no need to bloat ClipboardResource for that thing.
class ClipboardResource {
public:
  ClipboardResource();
  ~ClipboardResource();

  __idk_nodiscard
  idk::StringViewChar& // it's changeable because you can set the clipboard data with it.
  get_clipboard_data() noexcept;

  void
  set_clipboard_data() noexcept; // just change _clipboard_data, then call set_clipboard_data()

  void
  sync_clipboard_data() noexcept; // almost identical with get_clipboard_data() but no any data returned just assigned to _clipboard_data.
private:
  idk::StringViewChar _clipboard_data;
};
} // namespace fresh