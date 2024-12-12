// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#pragma once

#include <functional>
#include "fescript_callable.hpp"
#include "fescript_class.hpp"
#include "fescript_environment.hpp"
#include "fescript_error.hpp"
#include "fescript_expr.hpp"
#include "fescript_function.hpp"
#include "fescript_instance.hpp"
#include "fescript_return.hpp"
#include "fescript_runtime_error.hpp"
#include "fescript_stmt.hpp"

#include <types/stringview.hpp>

#define SET_VISIT_IMPL_OBJECT(object_index) \
case object_index: { \
  std::get<object_index>(object)->set(expr->name, value); \
  return value; \
}

#define GET_STRINGIFY_IMPL_OBJECT(object_index) \
case object_index: { \
  return std::get<object_index>(object)->to_string();\
}

// reserved variable names:
// * pos_x = x coord. position of object
// * pos_y = y coord. position of object
// * visible = visibility of object
// * disabled = disable parameter of object
// TODO: These are just BaseObject parameters. Expand it through whole SpriteObject and LabelObject params.
namespace fescript {
class Interpreter : public ExprVisitor, public StmtVisitor, public std::enable_shared_from_this<Interpreter> {
  friend class FescriptFunction;
  friend class Resolver;
  enum class State {
    Init,
    Update,
    Last,
    Invalid
  };
public:
  Interpreter();

  void interpret(const std::vector<std::shared_ptr<Stmt>> &statements);
  void interpret_update();
  void interpret_init();
  void interpret_last();

  std::vector<std::shared_ptr<Stmt>>& get_statements() noexcept;
  idk::isize& get_render_object_id() noexcept;

  [[nodiscard]] static std::string stringify(const Object &object);
  [[nodiscard]] idk::i64& get_global_seed() noexcept;

  [[nodiscard]] static Object get_object_property(const Token& keyword, const Object& value);
  [[nodiscard]] static Object baseobject_to_fescript_object(std::shared_ptr<fresh::BaseObject> base_obj) noexcept;
  [[nodiscard]] static std::shared_ptr<fresh::BaseObject> fescript_object_to_baseobject(Object obj) noexcept;

  [[nodiscard]] std::shared_ptr<fresh::BaseObject>& get_parent_object() noexcept;
private:
  [[nodiscard]] Object evaluate(std::shared_ptr<Expr> expr);
  [[nodiscard]] Object look_up_variable(const Token &name, const std::shared_ptr<Expr>& expr);

  void execute(const std::shared_ptr<Stmt>& stmt);
  void resolve(const std::shared_ptr<Expr>& expr, int depth);
  void execute_block(const std::vector<std::shared_ptr<Stmt>> &statements,
                     std::shared_ptr<Environment> environment);
  void check_number_operand(const Token &op, const Object &operand);
  void check_number_operands(const Token &op,
                             const Object &left,
                             const Object &right);

  [[nodiscard]] bool is_truthy(const Object &object);
  [[nodiscard]] bool is_equal(const Object &a, const Object &b);

  [[nodiscard]] Object visit(std::shared_ptr<Block> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<Class> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<Expression> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<Function> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<If> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<Return> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<Var> stmt) override;
  [[nodiscard]] Object visit(std::shared_ptr<While> stmt) override;

  [[nodiscard]] Object visit(std::shared_ptr<Assign> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Binary> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Call> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Get> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Grouping> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Literal> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Array> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Dict> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Logical> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Set> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Super> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<This> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Unary> expr) override;
  [[nodiscard]] Object visit(std::shared_ptr<Variable> expr) override;
private:
  State current_state { State::Invalid };
  idk::isize render_object_id { -1 }; // RenderObject index of object that linked to this interpreter.
                                      // RenderObject priority may be differ dynamically, so this should be changed by engine directly.
                                      // but it's ok for now, it's TODO.
  std::shared_ptr<Environment> globals;
  std::shared_ptr<Environment> environment;
  std::map<std::shared_ptr<Expr>, int> locals;
  std::vector<std::shared_ptr<Stmt>> statements;

  std::shared_ptr<fresh::BaseObject> _parent_object;
  idk::i64 global_seed;

  bool is_initialized { false };

  std::vector<std::shared_ptr<fresh::BaseObject>> _acquired_objects; // TODO: All not moved objects will be stored here, variables will take reference of specific object.
};
}// namespace fescript