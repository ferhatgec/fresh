#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/fescript/modules/fescript_path.hpp"

namespace fescript {
__idk_nodiscard Object FescriptPathExists::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_exists()", 1)
  return std::filesystem::exists(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsDir::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_is_dir()", 1)
  return std::filesystem::is_directory(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_is_file()", 1)
  auto& extract = std::get<StringIndex>(arguments.front());
  return std::filesystem::is_block_file(extract) ||
    std::filesystem::is_regular_file(extract) ||
    std::filesystem::is_character_file(extract);
}

__idk_nodiscard Object FescriptPathIsSymlink::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_is_symlink()", 1)
  return std::filesystem::is_symlink(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsSocket::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_is_socket()", 1)
  return std::filesystem::is_socket(std::get<StringIndex>(arguments.front()));
}

__idk_nodiscard Object FescriptPathIsEmpty::call(Interpreter& interpreter, std::vector <Object> arguments) {
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

__idk_nodiscard Object FescriptPathReadFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_read_file()", 1)
  std::ifstream stream(std::get<StringIndex>(arguments.front()));
  if(!stream)
    return false;
  std::string content;
  for(std::string temp; std::getline(stream, temp); content.append(temp + "\n"))
    ;
  stream.close();
  return content;
}

__idk_nodiscard Object FescriptPathWriteFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("Path_write_file()", 2)
  std::ofstream stream(std::get<StringIndex>(arguments[0]), std::ios::app);
  if(!stream)
    return false;
  stream << std::get<StringIndex>(arguments[1]);
  stream.close();
  return true;
}
}