//
// Created by gech on 2/5/2024.
//

#pragma once

#include <containers/vector.hpp>
#include "fes_ast.hpp"
#include "fes_tokenizer.hpp"
#include <memory>

namespace fresh {
namespace fes {
class FesParser {
public:
  friend class FesLoaderResource;

  FesParser();
  ~FesParser();

  __idk_nodiscard
  FesTokenizer&
  get_tokenizer() noexcept;

  void
  parse_variable(std::shared_ptr<FesObjectAST>& object_node) noexcept;

  void
  parse_list(std::shared_ptr<FesObjectAST>& object_node) noexcept;

  void
  parse_object(std::shared_ptr<FesObjectAST> object_node) noexcept;

  void
  parse() noexcept;

  std::shared_ptr<FesObjectAST> _objects;
private:
  idk::usize i = 0;
protected:
  FesTokenizer _tokenizer;
};
}
}