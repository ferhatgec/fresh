#include <fescript/wrappers/fescript_audio_player_object.hpp>
#include <objects/audio_player_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/animation/animation_player_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptAudioPlayerObjectMemberLoadAudioSource::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  switch(arguments.size()) { // AudioPlayerObject::load_audio_source()
    case 0: {
      this->_self->get_audio_resource().load_audio_source("");
      break;
    }
    case 1: { // AudioPlayerObject::load_audio_source(audio_file_path)
      this->_self->get_audio_resource().load_audio_source(
        std::get<StringIndex>(arguments[0]).data()
      );
      break;
    }
    case 2: { // AudioPlayerObject::load_audio_source(audio_file_path, frequency)
      this->_self->get_audio_resource().load_audio_source(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]))
      );
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_load_audio_source cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberGetAudioVolume::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  return static_cast<idk::f80>(this->_self->get_audio_resource().get_audio_volume());
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberPauseAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->get_audio_resource().pause_audio();
  return nullptr;
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberResumeAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->get_audio_resource().resume_audio();
  return nullptr;
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberPlayAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(arguments.empty())
    this->_self->get_audio_resource().play_audio();
  else
    this->_self->get_audio_resource().play_audio(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberPlayFadeInAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  switch(arguments.size()) {
    case 0: { // AudioPlayerObject::play_fade_in_audio()
      this->_self->get_audio_resource().fade_in_audio();
      break;
    }
    case 1: { // AudioPlayerObject::play_fade_in_audio(loop)
      this->_self->get_audio_resource().fade_in_audio(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // AudioPlayerObject::play_fade_in_audio(loop, ms)
      this->_self->get_audio_resource().fade_in_audio(std::get<BoolIndex>(arguments[1]), static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_play_fade_in_audio cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberStopAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  this->_self->get_audio_resource().stop_audio();
  return nullptr;
}

[[nodiscard]] Object FescriptAudioPlayerObjectMemberStopFadeOutAudio::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  switch(arguments.size()) {
    case 0: { // AudioPlayerObject::stop_fade_out_audio()
      this->_self->get_audio_resource().fade_out_audio();
      break;
    }
    case 1: { // AudioPlayerObject::stop_fade_out_audio(loop)
      this->_self->get_audio_resource().fade_out_audio(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // AudioPlayerObject::stop_fade_out_audio(loop, ms)
      this->_self->get_audio_resource().fade_out_audio(
        std::get<BoolIndex>(arguments[1]),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]))
      );
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_stop_fade_out_audio cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

[[nodiscard]] Object FescriptAudioPlayerObjectWrapper::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  // TODO: we must do type check.
  switch(arguments.size()) { // AudioPlayerObject::AudioPlayerObject()
    case 0: {
      return std::make_shared<fresh::AudioPlayerObject>();
    }
    case 1: { // AudioPlayerObject::AudioPlayerObject(audio_file_path)
      auto object = std::make_shared<fresh::AudioPlayerObject>();
      object->get_audio_resource().load_audio_source(std::get<StringIndex>(arguments[0]).data());
      return std::move(object);
    }
    case 2: { // AudioPlayerObject::AudioPlayerObject(audio_file_path, frequency)
      auto object = std::make_shared<fresh::AudioPlayerObject>();
      object->get_audio_resource().load_audio_source(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]))
      );
      return std::move(object);
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
}
} // namespace fescript