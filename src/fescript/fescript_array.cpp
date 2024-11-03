#include <fescript/fescript_array.hpp>
#include <fescript/fescript_expr.hpp>
#include <fescript/fescript_interpreter.hpp>
#include <fescript/fescript_runtime_error.hpp>
#include <log/log.hpp>

namespace fescript {
FescriptArray::FescriptArray() noexcept
  : _needs_update{false} {}

[[nodiscard]] const Object& FescriptArray::get_value(std::size_t index) const noexcept {
  if(index < this->_values.size()) {
    return this->_values[index];
  }
  fresh::log_error(fresh::src(), "index is out of bounds: '{}'", index);
  return nullptr;
}

[[nodiscard]] const std::string& FescriptArray::to_string() noexcept {
  if(!this->_needs_update) {
    return this->_to_string_cache;
  }
  this->_to_string_cache = "[";
  for(std::size_t i = 0; i < this->_values.size(); ++i) {
    this->_to_string_cache.append(Interpreter::stringify(this->_values[i]));
    if(i + 1 < this->_values.size()) {
      this->_to_string_cache.append(", ");
    }
  }
  this->_to_string_cache.push_back(']');
  return this->_to_string_cache;
}

[[nodiscard]] const std::vector<Object>& FescriptArray::get_values() noexcept {
  return this->_values;
}

void FescriptArray::set_array(const std::vector<Object>& values) noexcept {
  this->_values = values;
}

void FescriptArray::set_array(std::vector<Object>&& values) noexcept {
  this->_values = std::move(values);
}

void FescriptArray::push_value(const Object& value) noexcept {
  this->_needs_update = true;
  this->_values.push_back(value);
}

void FescriptArray::pop_value() noexcept {
  if(!this->_values.empty()) {
    this->_values.pop_back();
  }
}

void FescriptArray::clear() noexcept {
  this->_values.clear();
}

void FescriptArray::remove_value(std::size_t index) noexcept {
  if(index >= this->_values.size()) {
    fresh::log_error(fresh::src(), "index out of bounds: '{}'", index);
    return;
  }
  this->_values.erase(this->_values.begin() + static_cast<long long>(index));
}

void FescriptArray::push_value(std::size_t index,
                               const Object& value) noexcept {
  this->_values.insert(this->_values.begin() + static_cast<long long>(index), value);
}
}  // namespace fescript