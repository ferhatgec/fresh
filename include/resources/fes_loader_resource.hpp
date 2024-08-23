#pragma once

#include <fes/fes_ast.hpp>
#include <fes/fes_keywords.hpp>
#include <fes/fes_parser.hpp>
#include <fes/fes_tokenizer.hpp>
#include <objects/base_object.hpp>
#include <functional>

// FesLoaderResource is an easy way to integrate freshEngineScene files into your game.
// it's automatically allocate / deallocate objects behind the scenes.
// also it's easy to change scene with using another FesLoaderResource.

namespace fresh {
class FesLoaderResource {
public:
  friend class Editor;
  FesLoaderResource();
  ~FesLoaderResource();

  __idk_nodiscard
  fes::FesParser&
  get_fes_parser() noexcept;

  void
  load_fes(const idk::StringViewChar& file_or_raw_text, bool file = true) noexcept;

  void
  load_fes(idk::StringViewChar&& file_or_raw_text, bool file = true) noexcept;

  void
  generate_objects() noexcept;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  return_generated_objects() noexcept;

  __idk_nodiscard
  idk::StringViewChar
  convert_into_fes() noexcept;

  idk::StringViewChar scene_fes_file_path = "";
private:
  __idk_nodiscard
  idk::StringViewChar
  _convert_list(std::shared_ptr<fes::FesObjectAST> list_node) noexcept;

  __idk_nodiscard
  idk::StringViewChar
  _convert_object(std::shared_ptr<fes::FesObjectAST> object_node) noexcept;

  __idk_nodiscard
  idk::StringViewChar
  _convert_render_objects() noexcept;

  __idk_nodiscard
  std::shared_ptr<fes::FesObjectAST>
  _convert_object_from_render_objects(std::shared_ptr<BaseObject> object_node) noexcept;

  // TODO: Type must be inherited from AST objects.
  template<typename Type>
  std::shared_ptr<Type>
  _convert_object_from_base_object(std::shared_ptr<BaseObject> object_node,
                                   std::function<void(std::shared_ptr<Type>&, const std::shared_ptr<BaseObject>&)> extra = [&](
                                                                                                                              std::shared_ptr<Type>& obj,
                                                                                                                              const std::shared_ptr<BaseObject>& object_node
                                                                                                                             ) -> void {}) noexcept {
    std::shared_ptr<Type> obj = std::make_shared<Type>();
    FesLoaderResource::_convert_base_object_properties(obj, object_node);
    extra(obj, object_node); // additional function that takes obj and object_node as argument.
    return std::move(obj);
  }

  void
  _convert_base_object_properties(std::shared_ptr<fes::FesObjectAST> conv_obj,
                                 const std::shared_ptr<BaseObject>& object_node) noexcept;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  _generate_object(std::shared_ptr<fes::FesObjectAST> object_node) noexcept;

  void
  _generate() noexcept;

  __idk_nodiscard
  std::shared_ptr<BaseObject>
  _generate_with_return() noexcept;

  template<typename ObjectClassType>
  __idk_nodiscard
  std::shared_ptr<BaseObject>
  _generate_baseobject_ptr(std::shared_ptr<fes::FesObjectAST> object_node) noexcept;

  idk::u64 _object_ids { 0_u64 };
  fes::FesParser _parser;

  static idk::isize _space_indentation;
};
} // namespace fresh