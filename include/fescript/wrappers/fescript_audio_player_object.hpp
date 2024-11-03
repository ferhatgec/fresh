// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>
#include <objects/audio_player_object.hpp>
#include <objects/base_object.hpp>

#define AUDIO_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AudioPlayerObjectMember, arg_count)

namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(LoadAudioSource, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(GetAudioVolume, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(ResumeAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(ResumeAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayFadeInAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopAllAudio, AudioPlayerObjectMember, 0, fresh::AudioPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopFadeOutAudio, AudioPlayerObjectMember, -1, fresh::AudioPlayerObject)
DEFINE_MODULE_CLASS_CUSTOM_DERIVED_FROM(Wrapper, AudioPlayerObject, -1, FescriptBaseObjectWrapper)
} // namespace fescript