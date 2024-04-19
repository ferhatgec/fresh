#include "../../include/fescript/fescript_array.hpp"
#include "../../include/fescript/fescript_expr.hpp"
#include "../../include/fescript/fescript_interpreter.hpp"
#include "../../include/fescript/fescript_runtime_error.hpp"

namespace fescript {
FescriptArray::FescriptArray() {
}

FescriptArray::~FescriptArray() {
}

[[nodiscard]] Object FescriptArray::get(const int index) {
  // bellek
  if(index < this->values.size())
    return this->values[index];
  return nullptr;
}

[[nodiscard]] std::string FescriptArray::to_string() {
  std::string as_text = "[";
  for(std::size_t i = 0; i < this->values.size(); ++i) {
    as_text.append(Token::to_string(this->values[i]));
    if(i + 1 < this->values.size())
      as_text.append(", ");
  }
  as_text.push_back(']');
  return as_text;
}
}