#pragma once

#include <types/stringview.hpp>
#include "../../libs/SDL_mixer/include/SDL_mixer.h"

namespace fresh {
// MusicResource and AudioResource is not the same thing,
// MusicResource decodes file at the time, and need to be decoded when it's going to be played.
// AudioResource is allocated enough into memory, loads as chunks. It's using much more memory but
// no need for decoding again. Mostly, sound effects are AudioResource, musics from game soundtrack are MusicResource.
// it's your choice.
// also, MusicResource is not channeled.
class MusicResource {
public:
  MusicResource();
  MusicResource(const idk::StringViewChar& music_file_path,
                idk::i32 frequency = 44100, // cd quality
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2, // stereo
                idk::i32 buffer_size = 256 // i think it's large enough. otherwise it would be laggy so much.
                                           // in the end we use stacks which made play state slower.
                                           // use MusicResource if your *audio file* large enough.
                ) noexcept;

  MusicResource(idk::StringViewChar&& music_file_path,
                idk::i32 frequency = 44100,
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2,
                idk::i32 buffer_size = 256) noexcept;

  __idk_nodiscard
  Mix_Music*&
  get_music_source() noexcept;

  void
  load_music_source(const idk::StringViewChar& music_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 256) noexcept;

  void
  load_music_source(idk::StringViewChar&& audio_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 256) noexcept;

  __idk_nodiscard
  idk::i32&
  get_music_volume() noexcept;

  void
  sync_music_volume() noexcept;

  void
  pause_music() noexcept;

  void
  resume_music() noexcept;

  void
  play_music(bool loop = false) noexcept;

  void
  play_fade_in_music(bool loop = false, idk::i32 ms = 10_i32) noexcept;

  void
  stop_music() noexcept;

  void
  stop_fade_out_music(bool loop = false, idk::i32 ms = 10_i32) noexcept;

  ~MusicResource();
private:
  Mix_Music* _music_source = nullptr;
  idk::i32 _music_volume { MIX_MAX_VOLUME };
};
} // namespace fresh