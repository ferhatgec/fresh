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
  if(index < this->values.size())
    return this->values[index];
  return nullptr;
}

[[nodiscard]] std::string FescriptArray::to_string() {
  std::string as_text = "[";
  for(std::size_t i = 0; i < this->values.size(); ++i) {
    as_text.append(Interpreter::stringify(this->values[i]));
    if(i + 1 < this->values.size())
      as_text.append(", ");
  }
  as_text.push_back(']');
  return as_text;
}

[[nodiscard]]
std::vector<Object>& FescriptArray::get_values() noexcept {
  return this->values;
}

void FescriptArray::push_value(Object value) noexcept {
  this->values.push_back(value);
}
}