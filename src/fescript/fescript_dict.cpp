#include <fescript/fescript_dict.hpp>
#include <fescript/fescript_expr.hpp>
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_runtime_error.hpp>

namespace fescript {
FescriptDict::FescriptDict() {
}

FescriptDict::~FescriptDict() {
}

[[nodiscard]] Object FescriptDict::get(Object key) {
  if(auto elem = this->dictionary.find(key); elem != this->dictionary.end())
    return elem->second;
  return nullptr;
}

[[nodiscard]] std::string FescriptDict::to_string() {
  std::string as_text = "{";
  for(auto& [key, value]: this->dictionary) {
    as_text.append(Interpreter::stringify(key));
    as_text.push_back(':');
    as_text.append(Interpreter::stringify(value) + ", ");
  }
  if(as_text.length() > 1) { // at least one element is found.
    as_text.pop_back(); // removing whitespace
    as_text.pop_back(); // removing comma
  }
  as_text.push_back('}');
  return as_text;
}
}