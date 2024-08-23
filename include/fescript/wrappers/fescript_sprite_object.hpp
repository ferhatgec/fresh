#pragma once

#include "fescript_base_object.hpp"

namespace fescript {
class FescriptSpriteObjectMemberInitSprite : public FescriptCallable {
public:
  FescriptSpriteObjectMemberInitSprite(const std::shared_ptr<fresh::SpriteObject>& self)
    : _self{self} {}

  [[nodiscard]] int arity() override { return 0; }
  [[nodiscard]] std::string to_string() override { return "InitSprite"; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
private:
  std::shared_ptr<fresh::SpriteObject> _self;
};

class SpriteObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<SpriteObjectWrapper> {
public:
  SpriteObjectWrapper();
  ~SpriteObjectWrapper();
  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return -1; }
  [[nodiscard]] Object call([[maybe_unused]] Interpreter& interpreter, const std::vector<Object>& arguments) override;
};
} // namespace fescript