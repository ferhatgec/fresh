#pragma once

#include "fescript_base_object.hpp"
#include <fescript/modules/module_helpers.hpp>
#include <objects/base_object.hpp>

#define MUSIC_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, MusicPlayerObjectMember, arg_count)

/// @namespace fescript
/// @brief Global Fescript namespace.
namespace fescript {
DEFINE_MEMBER_MODULE_CLASS(LoadMusicSource, MusicPlayerObjectMember, -1, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(GetMusicVolume, MusicPlayerObjectMember, 0, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(SyncMusicVolume, MusicPlayerObjectMember, 0, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PauseMusic, MusicPlayerObjectMember, 0, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(ResumeMusic, MusicPlayerObjectMember, 0, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayMusic, MusicPlayerObjectMember, -1, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(PlayFadeInMusic, MusicPlayerObjectMember, -1, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopMusic, MusicPlayerObjectMember, 0, fresh::MusicPlayerObject)
DEFINE_MEMBER_MODULE_CLASS(StopFadeOutMusic, MusicPlayerObjectMember, -1, fresh::MusicPlayerObject)

/// @class MusicPlayerObjectWrapper
/// @brief Wrapper for Engine::MusicPlayerObject.
///
/// Wraps Engine::MusicPlayerObject for Fescript to create new instances.
class MusicPlayerObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<MusicPlayerObjectWrapper> {
public:
  /// Constructor of MusicPlayerObjectWrapper.
  MusicPlayerObjectWrapper();

  /// Destructor of MusicPlayerObjectWrapper.
  ~MusicPlayerObjectWrapper();

  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript