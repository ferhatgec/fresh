// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <resources/timer_resource.hpp>
#include <iostream>
#include <chrono>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <log/log.hpp>

namespace fresh {
TimerResource::TimerResource() noexcept
  : _start_tick{0}, _pause_tick{0}, _started{false}, _paused{false} {}

[[nodiscard]] idk::u64 // in milliseconds
TimerResource::get_ticks() const noexcept {
  if(!this->started()) {
    return 0;
  }
  if(this->paused()) {
    return this->_pause_tick;
  }
  return TimerResource::get_universal_tick() - this->_start_tick;
}

void TimerResource::start() noexcept {
  this->_started = true;
  this->_paused = false;
  this->_start_tick = TimerResource::get_universal_tick(); // in milliseconds
}

void TimerResource::pause() noexcept {
  if(this->paused()) {
    log_info(src(), "already paused; calling pause() multiple times won't effect.");
    return;
  }
  if(this->_started) {
    this->_paused = true;
    this->_pause_tick = TimerResource::get_universal_tick() - this->_start_tick;
    this->_start_tick = 0;
    return;
  }
  log_info(src(), "already not started; yet trying to pause is not possible.");
}

void TimerResource::resume() noexcept {
  if(!this->_paused) {
    log_info(src(), "already not paused; calling resume() won't effect.");
    return;
  }
  if(this->_started) {
    this->_paused = false;
    this->_start_tick = TimerResource::get_universal_tick() - this->_pause_tick;
    this->_pause_tick = 0;
    return;
  }
  log_info(src(), "already not started; yet trying to resume is not possible.");
}

void TimerResource::stop() noexcept {
  this->_started = this->_paused = false;
  this->_start_tick = this->_pause_tick = 0;
}

[[nodiscard]] const bool&
TimerResource::started() const noexcept {
  return this->_started;
}

[[nodiscard]] const bool& TimerResource::paused() const noexcept {
  return this->_paused;
}

[[nodiscard]] idk::u64 TimerResource::get_universal_tick() noexcept {
  const auto& duration = std::chrono::steady_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
}  // namespace fresh