// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_expr.hpp>

namespace fescript {
Expr::~Expr() {
}

Assign::Assign(Token name, std::shared_ptr<Expr> value)
    : name{std::move(name)}, value{std::move(value)} {}

Assign::~Assign() {
}

[[nodiscard]] Object Assign::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Binary::Binary(std::shared_ptr<Expr> left, Token op,
               std::shared_ptr<Expr> right)
    : left{std::move(left)}, op{std::move(op)}, right{std::move(right)} {
}

Binary::~Binary() {
}

[[nodiscard]] Object Binary::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Call::Call(std::shared_ptr<Expr> callee, Token paren,
           std::vector<std::shared_ptr<Expr>> arguments)
    : callee{std::move(callee)}, paren{std::move(paren)},
      arguments{std::move(arguments)} {
}

Call::~Call() {
}

[[nodiscard]] Object Call::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Get::Get(std::shared_ptr<Expr> object,
         Token name,
         std::shared_ptr<Variable> optional_variable)
    : object{std::move(object)},
      name{std::move(name)},
      is_name_an_expr{false},
      optional_variable{std::move(optional_variable)} {
}

Get::Get(std::shared_ptr<Expr> object,
         std::shared_ptr<Expr> name_expr,
         Token name,
         std::shared_ptr<Variable> optional_variable)
    : object{std::move(object)},
      name_expr{std::move(name_expr)},
      name{std::move(name)},
      is_name_an_expr{true},
      optional_variable{std::move(optional_variable)} {
}

Get::~Get() {
}

[[nodiscard]] Object Get::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Grouping::Grouping(std::shared_ptr<Expr> expression)
    : expression{std::move(expression)} {}

Grouping::~Grouping() {
}

[[nodiscard]] Object Grouping::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Literal::Literal(Object value) : value{std::move(value)} {}

Literal::~Literal() {
}

[[nodiscard]] Object Literal::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Array::Array(std::vector<std::shared_ptr<Expr>> values)
  : values{std::move(values)} {
}

Array::~Array() noexcept {
}

[[nodiscard]] Object Array::accept(fescript::ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Dict::Dict(std::unordered_map<std::shared_ptr<Expr>, std::shared_ptr<Expr>> values)
  : values{std::move(values)} {
}

Dict::~Dict() {
}

[[nodiscard]] Object Dict::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Logical::Logical(std::shared_ptr<Expr> left, Token op,
                 std::shared_ptr<Expr> right)
    : left{std::move(left)}, op{std::move(op)}, right{std::move(right)} {}

Logical::~Logical() {}

[[nodiscard]] Object Logical::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Set::Set(std::shared_ptr<Expr> object, Token name, std::shared_ptr<Expr> value)
    : object{std::move(object)}, name{std::move(name)},
      value{std::move(value)} {}

Set::~Set() {
}

[[nodiscard]] Object Set::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Super::Super(Token keyword, Token method)
    : keyword{std::move(keyword)}, method{std::move(method)} {}

Super::~Super() {
}

[[nodiscard]] Object Super::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

This::This(Token keyword) : keyword{std::move(keyword)} {
}

This::~This() {
}

[[nodiscard]] Object This::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Unary::Unary(Token op, std::shared_ptr<Expr> right)
    : op{std::move(op)}, right{std::move(right)} {}

Unary::~Unary() {
}

[[nodiscard]] Object Unary::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}

Variable::Variable(Token name) : name{std::move(name)} {}

Variable::~Variable() {
}

[[nodiscard]] Object Variable::accept(ExprVisitor &visitor) {
  return visitor.visit(shared_from_this());
}
}// namespace fescript