#ifndef FRESHENGINE_TIMER_RESOURCE_HPP
#define FRESHENGINE_TIMER_RESOURCE_HPP

#include "../../libs/idk/idk/types/predefined.hpp"

namespace fresh {
class TimerResource {
public:
  TimerResource();
  ~TimerResource();

  __idk_nodiscard
  idk::u64
  get_ticks() noexcept;

  void
  start() noexcept;

  void
  pause() noexcept;

  void
  unpause() noexcept;

  void
  stop() noexcept;

  __idk_nodiscard
  bool
  is_started() noexcept;

  __idk_nodiscard
  bool
  is_paused() noexcept;
private:
  idk::u64 _start_tick { 0_u64 };
  idk::u64 _pause_tick { 0_u64 };
  bool _started { false };
  bool _paused { false };
};
} // namespace
#endif // FRESHENGINE_TIMER_RESOURCE_HPP