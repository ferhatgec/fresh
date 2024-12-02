// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_array.hpp>

#include <fescript/modules/fescript_io.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fescript {
[[nodiscard]] Object FescriptIOPrint::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  for(const auto& argument: arguments) {
    std::cout << Interpreter::stringify(argument);
  }
  return true;
}

[[nodiscard]] Object FescriptIOPrintln::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  for(const auto& argument: arguments) {
    std::cout << Interpreter::stringify(argument) << '\n';
  }
  return true;
}

[[nodiscard]] Object FescriptIOReadFile::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("IO_read_file()", 1)
  std::string content;
  {
    std::ifstream stream(std::get<StringIndex>(arguments.front()));
    if(!stream) {
      return false;
    }
    for(std::string temp; std::getline(stream, temp); content.append(temp + "\n"))
      ;
  }
  return content;
}

[[nodiscard]] Object FescriptIOWriteFile::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  ERR_CHECK_STRING("IO_write_file()", 2)
  std::ofstream stream(std::get<StringIndex>(arguments[0]), std::ios::app);
  if(!stream) {
    return false;
  }
  stream << std::get<StringIndex>(arguments[1]);
  stream.close();
  return true;
}

[[nodiscard]] Object FescriptIOInput::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!arguments.empty()) {
    std::cout << Interpreter::stringify(arguments.front());
  }
  std::string input_str;
  std::cin >> input_str;
  return input_str;
}

[[nodiscard]] Object FescriptIOCharInput::call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) {
  if(!arguments.empty()) {
    std::cout << Interpreter::stringify(arguments.front());
  }
  idk::u8 ch = getchar();
  return std::string(1, ch);
}
}