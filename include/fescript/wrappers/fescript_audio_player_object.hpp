#pragma once

#include "fescript_base_object.hpp"
#include "../modules/module_helpers.hpp"
#include "../../objects/audio_player_object.hpp"
#include "../../objects/base_object.hpp"

#define AUDIO_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AudioPlayerObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(LoadAudioSource, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(GetAudioVolume, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(SyncAudioVolume, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(ResumeAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(ResumeAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayFadeInAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopFadeOutAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)

class AudioPlayerObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<AudioPlayerObjectWrapper> {
public:
  /// Constructor of AudioPlayerObjectWrapper.
  AudioPlayerObjectWrapper();

  /// Destructor of AudioPlayerObjectWrapper.
  ~AudioPlayerObjectWrapper();

  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
}