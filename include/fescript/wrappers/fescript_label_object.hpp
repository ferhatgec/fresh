#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
class FescriptLabelObjectMemberInitFont : public FescriptCallable {
public:
  FescriptLabelObjectMemberInitFont(const std::shared_ptr<fresh::LabelObject>& self)
    : _self{self} {}

  [[nodiscard]] int arity() override { return 0; }
  [[nodiscard]] std::string to_string() override { return "InitFont"; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
private:
  std::shared_ptr<fresh::LabelObject> _self;
};

class FescriptLabelObjectMemberInitText : public FescriptCallable {
public:
  FescriptLabelObjectMemberInitText(const std::shared_ptr<fresh::LabelObject>& self)
    : _self{self} {}

  [[nodiscard]] int arity() override { return 0; }
  [[nodiscard]] std::string to_string() override { return "InitText"; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
private:
  std::shared_ptr<fresh::LabelObject> _self;
};

class LabelObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<LabelObjectWrapper> {
public:
  LabelObjectWrapper();
  ~LabelObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript