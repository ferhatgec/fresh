//
// Created by gech on 2/5/2024.
//

#ifndef FRESHENGINE_FES_PARSER_HPP
#define FRESHENGINE_FES_PARSER_HPP

#include "../../libs/idk/idk/containers/vector.hpp"
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

#endif // FRESHENGINE_FES_PARSER_HPP
