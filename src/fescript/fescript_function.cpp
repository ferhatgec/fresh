// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_function.hpp>
#include <fescript/fescript_function.hpp>
#include <fescript/fescript_environment.hpp>
#include <fescript/fescript_instance.hpp>
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_stmt.hpp>
#include <fescript/fescript_array.hpp>

namespace fescript {
FescriptFunction::FescriptFunction(std::shared_ptr<Function> declaration,
                         std::shared_ptr<Environment> closure,
                         bool is_initializer)
    : is_initializer{is_initializer},
      closure{std::move(closure)},
      declaration{std::move(declaration)} {
  this->is_variadic = this->declaration->is_variadic;
}

[[nodiscard]] int FescriptFunction::arity() {
  return this->is_variadic ? (this->declaration->params.size() - 1) : this->declaration->params.size();
}

[[nodiscard]] Object FescriptFunction::call(Interpreter &interpreter, std::vector<Object> arguments) {
  auto environment = std::make_shared<Environment>(closure);
  for (std::size_t i = 0; i < this->declaration->params.size(); ++i) {
    if(this->declaration->params[i].is_variadic) {
      if(i + 1 >= this->declaration->params.size()) {
        std::shared_ptr<FescriptArray> variadic_args = std::make_shared<FescriptArray>();
        for(std::size_t j = i; j < arguments.size(); ++j) {
          variadic_args->push_value(arguments[j]);
        }
        environment->define(this->declaration->params[i].lexeme, variadic_args);
        break; // that was last argument.
      } else {
        std::cout << "Engine [language] error: variable that linked with variadic arguments must on the last argument of function.\n";
        std::exit(1);
      }
    }
    environment->define(this->declaration->params[i].lexeme, arguments[i]);
  }
  try {
    interpreter.execute_block(declaration->body, environment);
  } catch (const FescriptReturnException &return_value) {
    if (this->is_initializer)
      return this->closure->get_at(0, "this");
    return return_value.value;
  }
  if (this->is_initializer)
    return this->closure->get_at(0, "this");
  return nullptr;
}

[[nodiscard]] std::string FescriptFunction::to_string() {
  return "<fn " + declaration->name.lexeme + ">";
}

[[nodiscard]] std::shared_ptr<FescriptFunction> FescriptFunction::bind(std::shared_ptr<FescriptInstance> instance) {
  auto environment = std::make_shared<Environment>(this->closure);
  environment->define("this", instance);
  return std::make_shared<FescriptFunction>(this->declaration, std::move(environment), this->is_initializer);
}
}// namespace fescript