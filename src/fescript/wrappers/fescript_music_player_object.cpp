#include <fescript/wrappers/fescript_music_player_object.hpp>
#include <objects/animation/animation_player_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/music_player_object.hpp>

namespace fescript {
__idk_nodiscard Object FescriptMusicPlayerObjectMemberLoadMusicSource::call(Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) { // MusicPlayerObject::load_music_source()
    case 0: {
      this->_self->load_music_source("");
      break;
    }
    case 1: { // MusicPlayerObject::load_music_source(music_file_path)
      this->_self->load_music_source(std::get<StringIndex>(arguments[0]).data());
      break;
    }
    case 2: { // MusicPlayerObject::load_music_source(music_file_path, frequency)
      this->_self->load_music_source(std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    case 3: { // MusicPlayerObject::load_music_source(music_file_path, frequency, format)
      this->_self->load_music_source(std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])));
      break;
    }
    case 4: { // MusicPlayerObject::load_music_source(music_file_path, frequency, format, channel)
      this->_self->load_music_source(std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])));
      break;
    }
    case 5: { // MusicPlayerObject::load_music_source(music_file_path, frequency, format, channel, buffer_size)
      this->_self->load_music_source(std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[4])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: MusicPlayerObject_load_music_source cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberGetMusicVolume::call(Interpreter& interpreter, std::vector <Object> arguments) {
  return static_cast<idk::f80>(this->_self->get_music_volume());
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberSyncMusicVolume::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->sync_music_volume();
  return nullptr;
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberPauseMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->pause_music();
  return nullptr;
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberResumeMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->resume_music();
  return nullptr;
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberPlayMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(arguments.empty())
    this->_self->play_music();
  else
    this->_self->play_music(std::get<BoolIndex>(arguments[0]));
  return nullptr;
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberPlayFadeInMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) {
    case 0: { // MusicPlayerObject::play_fade_in_music()
      this->_self->play_fade_in_music();
      break;
    }
    case 1: { // MusicPlayerObject::play_fade_in_music(loop)
      this->_self->play_fade_in_music(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // MusicPlayerObject::play_fade_in_music(loop, ms)
      this->_self->play_fade_in_music(std::get<BoolIndex>(arguments[1]), static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: MusicPlayerObject_play_fade_in_music cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberStopMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  this->_self->stop_music();
  return nullptr;
}

__idk_nodiscard Object FescriptMusicPlayerObjectMemberStopFadeOutMusic::call(Interpreter& interpreter, std::vector <Object> arguments) {
  switch(arguments.size()) {
    case 0: { // MusicPlayerObject::stop_fade_out_music()
      this->_self->stop_fade_out_music();
      break;
    }
    case 1: { // MusicPlayerObject::stop_fade_out_music(loop)
      this->_self->stop_fade_out_music(std::get<BoolIndex>(arguments[0]));
      break;
    }
    case 2: { // MusicPlayerObject::stop_fade_out_music(loop, ms)
      this->_self->stop_fade_out_music(std::get<BoolIndex>(arguments[1]), static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])));
      break;
    }
    default: {
      std::cout << "Engine [language] error: MusicPlayerObject_stop_fade_out_music cannot take more than 2 arguments.\n";
      std::exit(1);
    }
  }
  return nullptr; // never reach, just for suppress compiler warning.
}

MusicPlayerObjectWrapper::MusicPlayerObjectWrapper() {
}

MusicPlayerObjectWrapper::~MusicPlayerObjectWrapper() noexcept {
}

[[nodiscard]] std::string MusicPlayerObjectWrapper::to_string() {
  return "musicplayerobject";
}

[[nodiscard]] Object MusicPlayerObjectWrapper::call(Interpreter &interpreter, std::vector<Object> arguments) {
  // TODO: we must do type check.
  switch(arguments.size()) { // MusicPlayerObject::MusicPlayerObject()
    case 0: {
      return std::make_shared<fresh::MusicPlayerObject>("");
    }
    case 1: { // MusicPlayerObject::MusicPlayerObject(music_file_path)
      return std::make_shared<fresh::MusicPlayerObject>(
        std::get<StringIndex>(arguments[0]).data()
        );
    }
    case 2: { // MusicPlayerObject::MusicPlayerObject(music_file_path, frequency)
      return std::make_shared<fresh::MusicPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1]))
        );
    }
    case 3: { // MusicPlayerObject::MusicPlayerObject(music_file_path, frequency, format)
      return std::make_shared<fresh::MusicPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2]))
        );
    }
    case 4: { // MusicPlayerObject::MusicPlayerObject(music_file_path, frequency, format, channel)
      return std::make_shared<fresh::MusicPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3]))
      );
    }
    case 5: { // MusicPlayerObject::MusicPlayerObject(music_file_path, frequency, format, channel, buffer_size)
      return std::make_shared<fresh::MusicPlayerObject>(
        std::get<StringIndex>(arguments[0]).data(),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[1])),
        static_cast<idk::u16>(std::get<LongDoubleIndex>(arguments[2])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[3])),
        static_cast<idk::i32>(std::get<LongDoubleIndex>(arguments[4]))
      );
    }
    default: {
      std::cout << "Engine [language] error: MusicPlayerObject cannot take more than 5 arguments!";
      std::exit(1);
    }
  }
}
} // namespace fescript
