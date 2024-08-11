#include <fescript/wrappers/fescript_audio_player_object.hpp>
#include <objects/audio_player_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/animation/animation_player_object.hpp>

namespace fescript {
[[nodiscard]] Object FescriptAudioPlayerObjectMemberLoadAudioSource::call(fescript::Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) { // AudioPlayerObject::load_audio_source()
    case 0: {
      this->_self->load_audio_source("");
      break;
    }
    case 1: { // AudioPlayerObject::load_audio_source(audio_file_path)
      this->_self->load_audio_source(std::get<StringIndex>(arguments[0]).data());
      break;
    }
    case 2: { // AudioPlayerObject::load_audio_source(audio_file_path, frequency)
      this->_self->load_audio_source(std::get<StringIndex>(arguments[0]).data(),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    case 3: { // AudioPlayerObject::load_audio_source(audio_file_path, frequency, format)
      this->_self->load_audio_source(std::get<StringIndex>(arguments[0]).data(),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
                                     static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])));
      break;
    }
    case 4: { // AudioPlayerObject::load_audio_source(audio_file_path, frequency, format, channel)
      this->_self->load_audio_source(std::get<StringIndex>(arguments[0]).data(),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
                                     static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])));
      break;
    }
    case 5: { // AudioPlayerObject::load_audio_source(audio_file_path, frequency, format, channel, buffer_size)
      this->_self->load_audio_source(std::get<StringIndex>(arguments[0]).data(),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
                                     static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])),
                                     static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[4])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_load_audio_source cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberGetAudioVolume::call(Interpreter& interpreter, std::vector <Object> arguments) {
  return static_cast<idk::f80>(this->_self->get_audio_volume());
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberSyncAudioVolume::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->sync_audio_volume();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberPauseAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->pause_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberPauseAllAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->pause_all_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberResumeAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->resume_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberResumeAllAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->resume_all_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberPlayAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(arguments.empty())
    this->_self->play_audio();
  else
    this->_self->play_audio(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberPlayFadeInAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) {
    case 0: { // AudioPlayerObject::play_fade_in_audio()
      this->_self->play_fade_in_audio();
      break;
    }
    case 1: { // AudioPlayerObject::play_fade_in_audio(loop)
      this->_self->play_fade_in_audio(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // AudioPlayerObject::play_fade_in_audio(loop, ms)
      this->_self->play_fade_in_audio(std::get<BoolIndex>(arguments[1]), static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_play_fade_in_audio cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberStopAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->stop_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberStopAllAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->stop_all_audio();
  return nullptr;
}

__idk_nodiscard Object FescriptAudioPlayerObjectMemberStopFadeOutAudio::call(Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) {
    case 0: { // AudioPlayerObject::stop_fade_out_audio()
      this->_self->stop_fade_out_audio();
      break;
    }
    case 1: { // AudioPlayerObject::stop_fade_out_audio(loop)
      this->_self->stop_fade_out_audio(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // AudioPlayerObject::stop_fade_out_audio(loop, ms)
      this->_self->stop_fade_out_audio(std::get<BoolIndex>(arguments[1]), static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject_stop_fade_out_audio cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

AudioPlayerObjectWrapper::AudioPlayerObjectWrapper() {
}

AudioPlayerObjectWrapper::~AudioPlayerObjectWrapper() noexcept {
}

[[nodiscard]] std::string AudioPlayerObjectWrapper::to_string() {
  return "audioplayerobject";
}

[[nodiscard]] Object AudioPlayerObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  // TODO: we must do type check.
  switch(arguments.size()) { // AudioPlayerObject::AudioPlayerObject()
    case 0: {
      return std::make_shared<fresh::AudioPlayerObject>("");
    }
    case 1: { // AudioPlayerObject::AudioPlayerObject(audio_file_path)
      return std::make_shared<fresh::AudioPlayerObject>(
        std::get<StringIndex>(arguments[0]).data()
      );
    }
    case 2: { // AudioPlayerObject::AudioPlayerObject(audio_file_path, frequency)
      return std::make_shared<fresh::AudioPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]))
      );
    }
    case 3: { // AudioPlayerObject::AudioPlayerObject(audio_file_path, frequency, format)
      return std::make_shared<fresh::AudioPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2]))
      );
    }
    case 4: { // AudioPlayerObject::AudioPlayerObject(audio_file_path, frequency, format, channel)
      return std::make_shared<fresh::AudioPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3]))
      );
    }
    case 5: { // AudioPlayerObject::AudioPlayerObject(audio_file_path, frequency, format, channel, buffer_size)
      return std::make_shared<fresh::AudioPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[4]))
      );
    }
    default: {
      std::cout << "Engine [language] error: AudioPlayerObject cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
}
} // namespace fescript