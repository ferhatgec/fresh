#pragma once

#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/modules/module_helpers.hpp>
#include <objects/base_object.hpp>

#define ANIMATION_FRAME_OBJECT_FUNCTION(name, arg_count) DEFINE_MODULE_CLASS(name, AnimationFrameObjectMember, arg_count)

/// @namespace fescript
/// @brief Global Fescript namespace.
namespace fescript {
/// @class AnimationFrameObjectWrapper
/// @brief Wrapper for Engine::AnimationFrameObject
///
/// Wraps Engine::AnimationFrameObject for Fescript to create new instances.
class AnimationFrameObjectWrapper : public BaseObjectWrapper, public std::enable_shared_from_this<AnimationFrameObjectWrapper> {
public:
  /// Constructor of AnimationFrameObjectWrapper
  AnimationFrameObjectWrapper();

  /// Destructor of AnimationFrameObjectWrapper
  ~AnimationFrameObjectWrapper();

  [[nodiscard]] std::string to_string() override;
  [[nodiscard]] int arity() override { return 5; }
  [[nodiscard]] Object call(Interpreter &interpreter, std::vector<Object> arguments) override;
};
} // namespace fescript