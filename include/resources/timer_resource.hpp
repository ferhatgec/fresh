// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <types/predefined.hpp>

namespace fresh {
class TimerResource {
public:
  TimerResource() noexcept;
  ~TimerResource() noexcept = default;

  /// TimerResource::get_ticks() returns current tick as milliseconds.
  [[nodiscard]] idk::u64 get_ticks() const noexcept;

  /// TimerResource::start() saves current tick; starts the timer.
  void start() noexcept;

  /// TimerResource::pause() pauses the timer.
  void pause() noexcept;

  /// TimerResource::resume() resumes the timer if it's already been paused.
  void resume() noexcept;

  /// TimerResource::stop() resets the timer.
  void stop() noexcept;

  /// TimerResource::started() is read-only access to _started property.
  [[nodiscard]] const bool& started() const noexcept;

  /// TimerResource::paused() is read-only access to _paused property.
  /// pause() and paused() are seem to be easily confused functions;
  /// that's where [[nodiscard]] attribute will make sense; unless discarding
  /// it using (void) or using the value; compiler will warn you.
  [[nodiscard]] const bool& paused() const noexcept;

  [[nodiscard]] static idk::u64 get_universal_tick() noexcept;
private:
  idk::u64 _start_tick;
  idk::u64 _pause_tick;
  bool _started;
  bool _paused;
};
} // namespace fresh