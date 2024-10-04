#include <resources/timer_resource.hpp>
#include <SDL.h>
#include <iostream>

namespace fresh {
TimerResource::TimerResource() {
}

TimerResource::~TimerResource() {
}

__idk_nodiscard
idk::u64 // in milliseconds
TimerResource::get_ticks() noexcept {
  if(!this->is_started())
    return 0_u64;

  if(this->is_paused()) {
    return this->_pause_tick;
  }

  return SDL_GetTicks64() - this->_start_tick;
}

void TimerResource::start() noexcept {
  this->_started = true;
  this->_paused = false;
  this->_start_tick = SDL_GetTicks64(); // in milliseconds
}

void TimerResource::pause() noexcept {
  if(this->_paused) {
    this->unpause();
    return;
  }

  if(this->_started) {
    this->_paused = true;
    this->_pause_tick = SDL_GetTicks64() - this->_start_tick;
    this->_start_tick = 0_u64;
  } else {
    std::cout << "Engine info: TimerResource is not even started, yet trying to pause it is bad idea.\n";
  }
}

void TimerResource::unpause() noexcept {
  if(!this->_paused) {
    std::cout << "Engine info: TimerResource is not paused before, trying to unpause it does nothing.\n";
    return;
  }

  if(this->_started) {
    this->_paused = false;
    this->_start_tick = SDL_GetTicks64() - this->_pause_tick;
    this->_pause_tick = 0_u64;
  } else {
    std::cout << "Engine info: TimerResource is not even started, yet trying to unpause it is bad idea.\n";
  }
}

void TimerResource::stop() noexcept {
  this->_started = false;
  this->_paused = false;
  this->_start_tick = this->_pause_tick = 0_u64;
}

__idk_nodiscard bool
TimerResource::is_started() noexcept {
  return this->_started;
}

__idk_nodiscard bool
TimerResource::is_paused() noexcept {
  return this->_paused;
}
}// namespace fresh