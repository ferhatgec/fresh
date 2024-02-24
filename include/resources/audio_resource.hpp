#ifndef FRESHENGINE_AUDIO_RESOURCE_HPP
#define FRESHENGINE_AUDIO_RESOURCE_HPP

#include "../../libs/idk/idk/types/stringview.hpp"
#include "../../libs/SDL_mixer/include/SDL_mixer.h"

namespace fresh {
class AudioResource {
public:
  AudioResource();
  AudioResource(const idk::StringViewChar& audio_file_path,
                idk::i32 frequency = 44100, // cd quality
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2, // stereo
                idk::i32 buffer_size = 512 // i think it's large enough. otherwise it would be laggy so much.
                                           // in the end we use stacks which made play state slower.
                                           // use MusicResource if your *audio file* large enough.
  ) noexcept;

  AudioResource(idk::StringViewChar&& audio_file_path,
                idk::i32 frequency = 44100,
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2,
                idk::i32 buffer_size = 512) noexcept;

  __idk_nodiscard
  Mix_Chunk*&
  get_audio_source() noexcept;

  void
  load_audio_source(const idk::StringViewChar& audio_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 512) noexcept;

  void
  load_audio_source(idk::StringViewChar&& audio_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 512) noexcept;

  __idk_nodiscard
  idk::i32&
  get_audio_volume() noexcept;

  void
  sync_audio_volume() noexcept;

  void
  pause_audio() noexcept;

  void
  pause_all_audio() noexcept;

  void
  resume_audio() noexcept;

  void
  resume_all_audio() noexcept;

  void
  play_audio(bool loop = false) noexcept;

  void
  play_fade_in_audio(bool loop = false, idk::i32 ms = 10_i32) noexcept;

  void
  stop_audio() noexcept;

  void
  stop_fade_out_audio(bool loop = false, idk::i32 ms = 10_i32) noexcept;

  void
  stop_all_audio() noexcept;

  ~AudioResource();
private:
  Mix_Chunk* _audio_source = nullptr;
  idk::i32 _audio_volume { MIX_MAX_VOLUME };
  idk::i32 _audio_channel;

  static idk::u16 _channel;
};
} // namespace fresh
#endif // FRESHENGINE_AUDIO_RESOURCE_HPP