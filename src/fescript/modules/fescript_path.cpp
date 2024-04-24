#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/fescript/modules/fescript_path.hpp"

#define WRAP_AS_ARRAY(fn) if(arguments.size() > 1) { \
std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>(); \
for(const auto& entry: arguments) { \
if(entry.index() == StringIndex) { \
array->get_values().push_back(fn(std::get<StringIndex>(entry))); \
continue; \
} \
array->get_values().push_back(false); \
} \
return std::move(array); \
}

namespace fescript {
static inline std::function<bool(const std::string&)> is_file = [](const std::string& extract) -> bool {
  return std::filesystem::is_block_file(extract) ||
         std::filesystem::is_regular_file(extract) ||
         std::filesystem::is_character_file(extract);
};

__idk_nodiscard Object FescriptPathExists::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(std::filesystem::exists)
  ERR_CHECK_STRING("Path_exists()", 1);
  return std::filesystem::exists(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsDir::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(std::filesystem::is_directory)
  ERR_CHECK_STRING("Path_is_dir()", 1)
  return std::filesystem::is_directory(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(is_file)
  ERR_CHECK_STRING("Path_is_file()", 1)
  auto& extract = std::get<StringIndex>(arguments.front());
  return is_file(extract);
}

__idk_nodiscard Object FescriptPathIsSymlink::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(std::filesystem::is_symlink)
  ERR_CHECK_STRING("Path_is_symlink()", 1)
  return std::filesystem::is_symlink(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsSocket::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(std::filesystem::is_socket)
  ERR_CHECK_STRING("Path_is_socket()", 1)
  return std::filesystem::is_socket(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsEmpty::call(Interpreter& interpreter, std::vector <Object> arguments) {
  WRAP_AS_ARRAY(std::filesystem::is_empty)
  ERR_CHECK_STRING("Path_is_empty()", 1)
  return std::filesystem::is_empty(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathCwd::call(Interpreter& interpreter, std::vector <Object> arguments) {
  return std::filesystem::current_path().filename().string();
}

__idk_nodiscard Object FescriptPathRwalk::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_rwalk()", 1)
  std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
  for(const auto& entry: std::filesystem::recursive_directory_iterator(std::get<StringIndex>(arguments.front())))
    array->get_values().push_back(entry.path().filename().string());
  return std::move(array);
}

__idk_nodiscard Object FescriptPathWalk::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_walk()", 1)
  std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
  for(const auto& entry: std::filesystem::directory_iterator(std::get<StringIndex>(arguments.front())))
    array->get_values().push_back(entry.path().filename().string());
  return std::move(array);
}
}