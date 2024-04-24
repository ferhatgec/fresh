#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../../include/fescript/fescript_interpreter.hpp"
#include "../../../include/fescript/fescript_array.hpp"
#include "../../../include/fescript/modules/fescript_io.hpp"

namespace fescript {
__idk_nodiscard Object FescriptIOPrint::call(Interpreter& interpreter, std::vector <Object> arguments) {
  for(auto& argument: arguments)
    std::cout << Interpreter::stringify(argument);
  return true;
}

__idk_nodiscard Object FescriptIOPrintln::call(Interpreter& interpreter, std::vector <Object> arguments) {
  for(auto& argument: arguments)
    std::cout << Interpreter::stringify(argument) << '\n';
  return true;
}

__idk_nodiscard Object FescriptIOReadFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("IO_read_file()", 1)
  std::ifstream stream(std::get<StringIndex>(arguments.front()));
  if(!stream)
    return false;
  std::string content;
  for(std::string temp; std::getline(stream, temp); content.append(temp + "\n"))
    ;
  stream.close();
  return content;
}

__idk_nodiscard Object FescriptIOWriteFile::call(Interpreter& interpreter, std::vector <Object> arguments) {
  ERR_CHECK_STRING("IO_write_file()", 2)
  std::ofstream stream(std::get<StringIndex>(arguments[0]), std::ios::app);
  if(!stream)
    return false;
  stream << std::get<StringIndex>(arguments[1]);
  stream.close();
  return true;
}

__idk_nodiscard Object FescriptIOInput::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!arguments.empty())
    std::cout << Interpreter::stringify(arguments.front());
  std::string input_str;
  std::cin >> input_str;
  return input_str;
}

__idk_nodiscard Object FescriptIOCharInput::call(Interpreter& interpreter, std::vector <Object> arguments) {
  if(!arguments.empty())
    std::cout << Interpreter::stringify(arguments.front());
  idk::u8 ch = getchar();
  return std::string(1, ch);
}
}