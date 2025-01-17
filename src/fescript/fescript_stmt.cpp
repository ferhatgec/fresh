// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_stmt.hpp>

namespace fescript {
Stmt::~Stmt() {
}

Block::Block(std::vector<std::shared_ptr<Stmt>> statements)
    : statements{std::move(statements)} {}

Block::~Block() {
}

[[nodiscard]] Object Block::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Class::Class(Token name, std::shared_ptr<Variable> superclass,
             std::vector<std::shared_ptr<Function>> methods)
    : name{std::move(name)}, superclass{std::move(superclass)},
      methods{std::move(methods)} {}

Class::~Class() {
}

[[nodiscard]] Object Class::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Expression::Expression(std::shared_ptr<Expr> expression)
    : expression{std::move(expression)} {}

Expression::~Expression() {
}

[[nodiscard]] Object Expression::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Function::Function(Token name,
                   std::vector<Token> params,
                   std::vector<std::shared_ptr<Stmt>> body,
                   bool is_variadic)
    : name{std::move(name)},
      params{std::move(params)},
      body{std::move(body)},
      is_variadic{is_variadic} {}

Function::~Function() {
}

[[nodiscard]] Object Function::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

If::If(std::shared_ptr<Expr> condition,
       std::shared_ptr<Block> then_branch,
       std::map<std::shared_ptr<Expr>, std::shared_ptr<Block>> elifs,
       std::shared_ptr<Block> else_branch)
    : condition{std::move(condition)},
      then_branch{std::move(then_branch)},
      elifs{std::move(elifs)},
      else_branch{std::move(else_branch)} {
}

If::~If() {
}

[[nodiscard]] Object If::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Return::Return(Token keyword, std::shared_ptr<Expr> value)
    : keyword{std::move(keyword)}, value{std::move(value)} {}

Return::~Return() {
}

[[nodiscard]] Object Return::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Var::Var(Token name, std::shared_ptr<Expr> initializer)
    : name{std::move(name)}, initializer{std::move(initializer)} {}

Var::~Var() {
}

[[nodiscard]] Object Var::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

While::While(std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body)
    : condition{std::move(condition)}, body{std::move(body)} {}

While::~While() {
}

[[nodiscard]] Object While::accept(StmtVisitor &visitor) {
  return visitor.visit(shared_from_this());
}
}// namespace fescript