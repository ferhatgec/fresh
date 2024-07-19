#pragma once

#include "../../libs/idk/idk/types/predefined.hpp"
#include "../../libs/idk/idk/types/stringview.hpp"
#include "../../include/fescript/fescript_token.hpp"
#include "base_object.hpp"
#include "../resources/audio_resource.hpp"

#define CHECK_IS_AUDIO_RESOURCE_EMPTY(function_name) \
  if(!this->_audio_resource) {          \
    std::cout << "Engine [language] error: AudioPlayerObject assigned with no resource, using `" #function_name "` is not allowed.\n"; \
    std::exit(0); \
  }

namespace fresh {
class AudioPlayerObject : public BaseObject {
public:
  AudioPlayerObject();
  AudioPlayerObject(const idk::StringViewChar& audio_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 512) noexcept;

  AudioPlayerObject(idk::StringViewChar&& audio_file_path,
                    idk::i32 frequency = 44100,
                    idk::u16 format = AUDIO_S16SYS,
                    idk::i32 channel = 2,
                    idk::i32 buffer_size = 512) noexcept;

  ~AudioPlayerObject();

  void
  sync(bool is_sync_with_camera = false) noexcept override;

  [[nodiscard]] void set(const fescript::Token& name, fescript::Object value) override;

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

  [[nodiscard]] std::string to_string() {
    return "audioplayerobject";
  }
protected:
  std::shared_ptr<AudioResource> _audio_resource;
};
} // namespace fresh