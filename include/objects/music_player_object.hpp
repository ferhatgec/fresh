#pragma once

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/types/stringview.hpp"
#include "../../include/fescript/fescript_token.hpp"
#include "base_object.hpp"
#include "../resources/music_resource.hpp"

#define CHECK_IS_MUSIC_RESOURCE_EMPTY(function_name) \
  if(!this->_music_resource) {          \
    std::cout << "Engine [language] error: MusicPlayerObject assigned with no resource, using `" #function_name "` is not allowed.\n"; \
    std::exit(0); \
  }

namespace fresh {
class MusicPlayerObject : public BaseObject {
public:
  MusicPlayerObject();
  MusicPlayerObject(const idk::StringViewChar& music_file_path,
                idk::i32 frequency = 44100,
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2,
                idk::i32 buffer_size = 256
  ) noexcept;

  MusicPlayerObject(idk::StringViewChar&& music_file_path,
                idk::i32 frequency = 44100,
                idk::u16 format = AUDIO_S16SYS,
                idk::i32 channel = 2,
                idk::i32 buffer_size = 256) noexcept;
  ~MusicPlayerObject();

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;

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

  [[nodiscard]] std::string to_string() {
    return "musicplayerobject";
  }
protected:
  std::shared_ptr<MusicResource> _music_resource;
};
} // namespace fresh