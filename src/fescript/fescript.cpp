// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_error.hpp>
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_parser.hpp>
#include <fescript/fescript_resolver.hpp>
#include <fescript/fescript_scanner.hpp>
#include <fstream>

using namespace fescript;

[[nodiscard]] std::string read_file(std::string_view path) noexcept {
  std::ifstream file(path.data());
  if (!file)
    return "print \"failed to open file\";";
  std::string contents;
  for (std::string temp; std::getline(file, temp); contents.append(temp + "\n"))
    ;
  file.close();
  return std::move(contents);
}

Interpreter interpreter;

void run(std::string_view source) noexcept {
  Scanner scanner(std::move(source));
  std::vector<Token> tokens = scanner.scan_tokens();
  Parser parser(tokens);
  auto statements = parser.parse();
  if (had_error || had_runtime_error)
    return;
  Resolver resolver{interpreter};
  resolver.resolve(statements);
  if (had_error || had_runtime_error)
    return;
  interpreter.interpret(statements);
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "Usage: fescript [script]\n";
  } else if (argc == 2) {
    run(read_file(argv[1]));
  } else {
    // TODO: implement REPL
  }
}