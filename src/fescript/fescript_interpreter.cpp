// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include "../../include/fescript/fescript_array.hpp"
#include "../../include/fescript/fescript_dict.hpp"
#include "../../include/fescript/fescript_interpreter.hpp"
#include "../../include/render_objects.hpp"

#include "../../include/fescript/modules/fescript_math.hpp"
#include "../../include/fescript/modules/fescript_os.hpp"
#include "../../include/fescript/modules/fescript_path.hpp"
#include "../../include/fescript/modules/fescript_io.hpp"

#include "../../include/fescript/modules/engine_io.hpp"
#include "../../include/fescript/modules/engine.hpp"

#include "../../include/fescript/wrappers/fescript_base_object.hpp"
#include "../../include/fescript/wrappers/fescript_sprite_object.hpp"
#include "../../include/fescript/wrappers/fescript_label_object.hpp"
#include "../../include/fescript/wrappers/fescript_area_object.hpp"
#include "../../include/fescript/wrappers/fescript_collision_object.hpp"
#include "../../include/fescript/wrappers/fescript_camera_object.hpp"

#include "../../include/objects/area_object.hpp"
#include "../../include/objects/collision_object.hpp"
#include "../../include/objects/camera_object.hpp"

namespace fescript {
Interpreter::Interpreter() {
  this->globals = std::make_shared<Environment>();
  this->environment = this->globals;

  this->globals->define("Math_abs", std::make_shared<FescriptMathAbs>());
  this->globals->define("Math_max", std::make_shared<FescriptMathMax>());
  this->globals->define("Math_min", std::make_shared<FescriptMathMin>());
  this->globals->define("Math_exp", std::make_shared<FescriptMathExp>());
  this->globals->define("Math_log", std::make_shared<FescriptMathLog>());
  this->globals->define("Math_pow", std::make_shared<FescriptMathPow>());
  this->globals->define("Math_sqrt", std::make_shared<FescriptMathSqrt>());
  this->globals->define("Math_cbrt", std::make_shared<FescriptMathCbrt>());
  this->globals->define("Math_sin", std::make_shared<FescriptMathSin>());
  this->globals->define("Math_cos", std::make_shared<FescriptMathCos>());
  this->globals->define("Math_tan", std::make_shared<FescriptMathTan>());
  this->globals->define("Math_asin", std::make_shared<FescriptMathAsin>());
  this->globals->define("Math_acos", std::make_shared<FescriptMathAcos>());
  this->globals->define("Math_atan", std::make_shared<FescriptMathAtan>());
  this->globals->define("Math_sinh", std::make_shared<FescriptMathSinh>());
  this->globals->define("Math_cosh", std::make_shared<FescriptMathCosh>());
  this->globals->define("Math_tanh", std::make_shared<FescriptMathTanh>());
  this->globals->define("Math_asinh", std::make_shared<FescriptMathAsinh>());
  this->globals->define("Math_acosh", std::make_shared<FescriptMathAcosh>());
  this->globals->define("Math_atanh", std::make_shared<FescriptMathAtanh>());
  this->globals->define("Math_erf", std::make_shared<FescriptMathErf>());
  this->globals->define("Math_gamma", std::make_shared<FescriptMathGamma>());
  this->globals->define("Math_ceil", std::make_shared<FescriptMathCeil>());
  this->globals->define("Math_floor", std::make_shared<FescriptMathFloor>());
  this->globals->define("Math_trunc", std::make_shared<FescriptMathTrunc>());
  this->globals->define("Math_round", std::make_shared<FescriptMathRound>());

  this->globals->define("OS_platform", std::make_shared<FescriptOSPlatform>());
  this->globals->define("OS_exec", std::make_shared<FescriptOSExec>());
  this->globals->define("OS_arch", std::make_shared<FescriptOSArch>());

  this->globals->define("Path_exists", std::make_shared<FescriptPathExists>());
  this->globals->define("Path_is_dir", std::make_shared<FescriptPathIsDir>());
  this->globals->define("Path_is_file", std::make_shared<FescriptPathIsFile>());
  this->globals->define("Path_is_symlink", std::make_shared<FescriptPathIsSymlink>());
  this->globals->define("Path_is_socket", std::make_shared<FescriptPathIsSocket>());
  this->globals->define("Path_is_empty", std::make_shared<FescriptPathIsEmpty>());
  this->globals->define("Path_cwd", std::make_shared<FescriptPathCwd>());
  this->globals->define("Path_rwalk", std::make_shared<FescriptPathRwalk>());
  this->globals->define("Path_walk", std::make_shared<FescriptPathWalk>());

  this->globals->define("IO_print", std::make_shared<FescriptIOPrint>());
  this->globals->define("IO_println", std::make_shared<FescriptIOPrintln>());
  this->globals->define("IO_read_file", std::make_shared<FescriptIOReadFile>());
  this->globals->define("IO_write_file", std::make_shared<FescriptIOWriteFile>());
  this->globals->define("IO_input", std::make_shared<FescriptIOInput>());
  this->globals->define("IO_char_input", std::make_shared<FescriptIOCharInput>());

  this->globals->define("EngineIO_is_key_pressed", std::make_shared<FescriptEngineIOIsKeyPressed>());
  this->globals->define("EngineIO_is_key_just_pressed", std::make_shared<FescriptEngineIOIsKeyJustPressed>());
  this->globals->define("EngineIO_is_key_released", std::make_shared<FescriptEngineIOIsKeyReleased>());
  this->globals->define("EngineIO_is_mouse_button_pressed", std::make_shared<FescriptEngineIOIsMouseButtonPressed>());
  this->globals->define("EngineIO_is_mouse_button_just_pressed", std::make_shared<FescriptEngineIOIsMouseButtonJustPressed>());

  ENGINEIO_INIT_CONSTANTS()

  this->globals->define("Engine_BaseObject", std::make_shared<BaseObjectWrapper>());
  this->globals->define("Engine_SpriteObject", std::make_shared<SpriteObjectWrapper>());
  this->globals->define("Engine_LabelObject", std::make_shared<LabelObjectWrapper>());
  this->globals->define("Engine_AreaObject", std::make_shared<AreaObjectWrapper>());
  this->globals->define("Engine_CollisionObject", std::make_shared<CollisionObjectWrapper>());
  this->globals->define("Engine_CameraObject", std::make_shared<CameraObjectWrapper>());
  this->globals->define("Engine_render_objects_push", std::make_shared<FescriptEngineRenderObjectsPush>());
}

void Interpreter::interpret(
  const std::vector<std::shared_ptr<Stmt>> &statements) {

  if(this->current_state != State::Invalid) {
    try {
      for(const std::shared_ptr<Stmt>& statement: statements) {
        if(auto cast_ptr = std::dynamic_pointer_cast<Function>(statement);
          cast_ptr != nullptr) {
          if((this->current_state == State::Update && cast_ptr->name.lexeme == "update")) {
            this->execute(statement);
            break;
          }
        }
      }
    } catch(const RuntimeError& error) {
      runtime_error(error);
    }
    return;
  }

  try {
    for (const std::shared_ptr<Stmt> &statement: statements) {
      this->execute(statement);
    }
  } catch (const RuntimeError &error) {
    runtime_error(error);
  }
}

void Interpreter::interpret_update() {
  this->current_state = State::Update;
  this->interpret(this->statements);
  this->current_state = State::Invalid;
}

void Interpreter::interpret_init() {
  this->current_state = State::Init;
  this->interpret(this->statements);
  this->current_state = State::Invalid;
}

void Interpreter::interpret_last() {
  this->current_state = State::Last;
  this->interpret(this->statements);
  this->current_state = State::Invalid;
}

std::vector<std::shared_ptr<Stmt>>& Interpreter::get_statements() noexcept {
  return this->statements;
}

idk::isize& Interpreter::get_render_object_id() noexcept {
  return this->render_object_id;
}

[[nodiscard]] Object Interpreter::evaluate(std::shared_ptr<Expr> expr) {
  return expr->accept(*this);
}

[[nodiscard]] Object Interpreter::look_up_variable(const Token &name, std::shared_ptr<Expr> expr) {
  if(const auto& cast_to_variable = std::dynamic_pointer_cast<Get>(expr);
      (cast_to_variable != nullptr) && (cast_to_variable->name.literal.index() == NullptrIndex)) { // variable name
    return this->look_up_variable(name, cast_to_variable->optional_variable);
  }
  if (auto it = this->locals.find(expr); it != this->locals.end())
    return this->environment->get_at(it->second, name.lexeme);
  return this->globals->get(name);
}

void Interpreter::execute(std::shared_ptr<Stmt> stmt) {
  stmt->accept(*this);
}

void Interpreter::resolve(std::shared_ptr<Expr> expr, int depth) {
  this->locals[expr] = depth;
}

void Interpreter::execute_block(const std::vector<std::shared_ptr<Stmt>> &statements,
                                std::shared_ptr<Environment> environment) {
  std::shared_ptr<Environment> previous = this->environment;
  try {
    this->environment = environment;
    for (const std::shared_ptr<Stmt> &statement : statements)
      this->execute(statement);
  } catch (...) {
    this->environment = previous;
    throw;
  }
  this->environment = previous;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Block> stmt) {
  this->execute_block(stmt->statements, std::make_shared<Environment>(this->environment));
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Class> stmt) {
  Object superclass;
  if (stmt->superclass != nullptr) {
    superclass = this->evaluate(stmt->superclass);
    if (superclass.index() != FescriptClassIndex)
      throw RuntimeError(stmt->superclass->name, "superclass must be a class.");
  }
  this->environment->define(stmt->name.lexeme, nullptr);
  if (stmt->superclass != nullptr) {
    this->environment = std::make_shared<Environment>(this->environment);
    this->environment->define("super", superclass);
  }
  std::map<std::string, std::shared_ptr<FescriptFunction>> methods;
  for (std::shared_ptr<Function> method : stmt->methods) {
    auto function = std::make_shared<FescriptFunction>(method, this->environment, method->name.lexeme == "init");
    methods[method->name.lexeme] = std::move(function);
  }
  std::shared_ptr<FescriptClass> superklass = nullptr;
  if (superclass.index() == FescriptClassIndex)
    superklass = std::get<FescriptClassIndex>(superclass);
  auto klass = std::make_shared<FescriptClass>(stmt->name.lexeme, superklass, methods);
  if (superklass != nullptr)
    this->environment = this->environment->enclosing;
  this->environment->assign(stmt->name, std::move(klass));
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Expression> stmt) {
  (void)this->evaluate(stmt->expression);
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Function> stmt) {
  if(auto it = this->globals->values.find(stmt->name.lexeme); it != this->globals->values.end()) {
    if((it->second.index() == FescriptFunctionIndex || it->second.index() == FescriptCallableIndex)
      && !(stmt->name.lexeme == "update" && this->current_state == State::Update)) {
      std::cout << "Engine [language] error: There is already a function named as '" << stmt->name.lexeme << "'.\n";
      std::exit(1);
    }
  }
  auto function = std::make_shared<FescriptFunction>(stmt, environment, false);
  this->environment->define(stmt->name.lexeme, std::move(function));
  if((stmt->name.lexeme == "update" && this->current_state == State::Update) ||
    (stmt->name.lexeme == "init" && this->current_state == State::Init) ||
    (stmt->name.lexeme == "last" && this->current_state == State::Last)) {
    this->visit(std::make_shared<Call>(std::make_shared<Variable>(Token(TokenType::IDENTIFIER,
                                                                        stmt->name.lexeme,
                                                                        stmt->name.lexeme,
                                                                        -1)),
                                                  Token(),
                                                  std::vector<std::shared_ptr<Expr>>{
      std::make_shared<Literal>(fresh::RenderObjects::delta_ms)
    }));
  }
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<If> stmt) {
  if (this->is_truthy(this->evaluate(stmt->condition)))
    this->execute(stmt->then_branch);
  else {
    bool is_elif { false };
    for(const auto& [cond, block]: stmt->elifs) {
      if(this->is_truthy(this->evaluate(cond))) {
        this->execute(block);
        is_elif = true;
        break;
      }
    }
    if(!is_elif && (stmt->else_branch != nullptr)) {
      this->execute(stmt->else_branch);
    }
  }
  return nullptr;
}
//
//[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Print> stmt) {
//  Object value = this->evaluate(stmt->expression);
//  std::cout << this->stringify(value) << "\n";
//  return nullptr;
//}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Return> stmt) {
  Object value = nullptr;
  if (stmt->value != nullptr)
    value = this->evaluate(stmt->value);
  throw FescriptReturnException(value);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Var> stmt) {
  Object value = nullptr;
  if (stmt->initializer != nullptr)
    value = this->evaluate(stmt->initializer);
  this->environment->define(stmt->name.lexeme, value);
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<While> stmt) {
  while (this->is_truthy(this->evaluate(stmt->condition)))
    this->execute(stmt->body);
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Assign> expr) {
  Object value = this->evaluate(expr->value);
  // FIXME: we assume engine reserved variables are assigned with their OWN type.
  // we need to type check here. pos_x and pos_y must be int32, so Object.index() must be LongDoubleIndex.
  // also, visible and disabled must be bool, so Object.index() must be BoolIndex.
  if(expr->name.lexeme == "pos_x")
    fresh::RenderObjects::find(this->render_object_id)->get_position_info().x = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(expr->name.lexeme == "pos_y")
    fresh::RenderObjects::find(this->render_object_id)->get_position_info().y = static_cast<idk::i32>(std::get<LongDoubleIndex>(value));
  else if(expr->name.lexeme == "visible")
    fresh::RenderObjects::find(this->render_object_id)->get_is_visible() = std::get<BoolIndex>(value);
  else if(expr->name.lexeme == "disabled")
    fresh::RenderObjects::find(this->render_object_id)->get_is_disabled() = std::get<BoolIndex>(value);
  else if(expr->name.lexeme == "width")
    fresh::RenderObjects::find(this->render_object_id)->get_position_info().w = static_cast<idk::i32>(fabsl(std::get<LongDoubleIndex>(value)));
  else if(expr->name.lexeme == "height")
    fresh::RenderObjects::find(this->render_object_id)->get_position_info().h = static_cast<idk::i32>(fabsl(std::get<LongDoubleIndex>(value)));
  else {
    if (auto it = this->locals.find(expr); it != this->locals.end())
      this->environment->assign_at(it->second, expr->name, value);
    else
      this->globals->assign(expr->name, value);
  }
  return value;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Binary> expr) {
  Object left = this->evaluate(expr->left);
  Object right = this->evaluate(expr->right);
  switch (expr->op.type) {
  case TokenType::BANG_EQUAL: {
    return !this->is_equal(left, right);
  }
  case TokenType::EQUAL_EQUAL: {
    return this->is_equal(left, right);
  }
  case TokenType::GREATER: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) > std::get<LongDoubleIndex>(right);
  }
  case TokenType::GREATER_EQUAL: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) >= std::get<LongDoubleIndex>(right);
  }
  case TokenType::LESS: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) < std::get<LongDoubleIndex>(right);
  }
  case TokenType::LESS_EQUAL: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) <= std::get<LongDoubleIndex>(right);
  }
  case TokenType::MINUS: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) - std::get<LongDoubleIndex>(right);
  }
  case TokenType::PLUS: {
    if (left.index() == LongDoubleIndex && right.index() == LongDoubleIndex) {
      return std::get<LongDoubleIndex>(left) + std::get<LongDoubleIndex>(right);
    }
    if (left.index() == StringIndex && right.index() == StringIndex) {
      return std::get<StringIndex>(left) + std::get<StringIndex>(right);
    }
    if(left.index() == FescriptArrayIndex) {
      auto copy_left_array = std::get<FescriptArrayIndex>(left)->get_values();

      if(right.index() == FescriptArrayIndex) {
        for(auto& right_array_element: std::get<FescriptArrayIndex>(right)->get_values()) {
          copy_left_array.push_back(right_array_element);
        }
      } else {
        copy_left_array.push_back(right);
      }
      std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
      array->get_values() = std::move(copy_left_array);
      return std::move(array);
    }
    throw RuntimeError{expr->op, "operands must be two numbers or two strings."};
  }
  case TokenType::SLASH: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) / std::get<LongDoubleIndex>(right);
  }
  case TokenType::STAR: {
    this->check_number_operands(expr->op, left, right);
    return std::get<LongDoubleIndex>(left) * std::get<LongDoubleIndex>(right);
  }
  case TokenType::PERCENT: {
    this->check_number_operands(expr->op, left, right);
    return fmodl(std::get<LongDoubleIndex>(left), std::get<LongDoubleIndex>(right));
  }
  }
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Call> expr) {
  Object callee = this->evaluate(expr->callee);
  std::vector<Object> arguments;
  for (const std::shared_ptr<Expr> &argument : expr->arguments)
    arguments.push_back(this->evaluate(argument));
  std::shared_ptr<FescriptCallable> function;
  if (callee.index() == FescriptFunctionIndex) {
    function = std::get<FescriptFunctionIndex>(callee);
  } else if (callee.index() == FescriptClassIndex) {
    function = std::get<FescriptClassIndex>(callee);
  } else if(callee.index() == FescriptCallableIndex) {
    function = std::get<FescriptCallableIndex>(callee);
  } else {
    throw RuntimeError{expr->paren, "can only call functions and classes."};
  }
  if ((arguments.size() != function->arity()) && function->arity() != -1) {
    throw RuntimeError{expr->paren, "expected " + std::to_string(function->arity()) + " arguments but got " + std::to_string(arguments.size()) + "."};
  }
  return function->call(*this, std::move(arguments));
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Get> expr) {
  Object object = this->evaluate(expr->object);
  switch(object.index()) {
    case FescriptInstanceIndex: {
      return std::get<FescriptInstanceIndex>(object)->get(expr->name);
    }
    case FescriptArrayIndex: {
      if(expr->name.literal.index() == LongDoubleIndex)
        return std::get<FescriptArrayIndex>(object)->get(static_cast<int>(std::get<LongDoubleIndex>(expr->name.literal)));
      if(expr->is_name_an_expr)
        if(auto value = this->evaluate(expr->name_expr); value.index() == LongDoubleIndex)
          return std::get<FescriptArrayIndex>(object)->get(static_cast<int>(std::get<LongDoubleIndex>(value)));
      if(const auto& variable_value = this->look_up_variable(expr->name, expr);
        variable_value.index() == LongDoubleIndex)
        return std::get<FescriptArrayIndex>(object)->get(static_cast<int>(std::get<LongDoubleIndex>(variable_value)));
      throw RuntimeError(expr->name, "array must take an index by integer type.");
    }
    case FescriptDictIndex: {
      if(expr->is_name_an_expr)
        return std::get<FescriptDictIndex>(object)->get(this->evaluate(expr->name_expr));
      return std::get<FescriptDictIndex>(object)->get(expr->name.literal);
    }
    case FescriptBaseObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptBaseObjectIndex)
      else throw RuntimeError(expr->name, "BaseObject property cannot be found.");
    }
    case FescriptSpriteObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptSpriteObjectIndex)
      else if(expr->name.lexeme == "sprite_resource") return std::string(std::get<FescriptSpriteObjectIndex>(object)->get_sprite_resource()._texture_path.data());
      else throw RuntimeError(expr->name, "SpriteObject property cannot be found.");
    }
    case FescriptLabelObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptLabelObjectIndex)
      else if(expr->name.lexeme == "background_red") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_background_color().r);
      else if(expr->name.lexeme == "background_green") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_background_color().g);
      else if(expr->name.lexeme == "background_blue") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_background_color().b);
      else if(expr->name.lexeme == "background_alpha") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_background_color().a);
      else if(expr->name.lexeme == "foreground_red") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_foreground_color().r);
      else if(expr->name.lexeme == "foreground_green") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_foreground_color().g);
      else if(expr->name.lexeme == "foreground_blue") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_foreground_color().b);
      else if(expr->name.lexeme == "foreground_alpha") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_foreground_color().a);
      else if(expr->name.lexeme == "label_text") return std::string(std::get<FescriptLabelObjectIndex>(object)->get_label_text().data());
      else if(expr->name.lexeme == "font_size") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(object)->get_label_font_resource().get_font_size());
      else if(expr->name.lexeme == "font_resource") return std::string(std::get<FescriptLabelObjectIndex>(object)->get_label_font_resource().get_font_path().data());
      else if(expr->name.lexeme == "init_font") return std::make_shared<FescriptLabelObjectMemberInitFont>(std::get<FescriptLabelObjectIndex>(object));
      else if(expr->name.lexeme == "init_text") return std::make_shared<FescriptLabelObjectMemberInitText>(std::get<FescriptLabelObjectIndex>(object));
      else throw RuntimeError(expr->name, "LabelObject property cannot be found.");
    }
    case FescriptAreaObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptAreaObjectIndex)
      else if(expr->name.lexeme == "is_colliding_with") return std::make_shared<FescriptAreaObjectMemberIsCollidingWith>(std::get<FescriptAreaObjectIndex>(object));
      else throw RuntimeError(expr->name, "AreaObject property cannot be found.");
    }
    case FescriptCollisionObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCollisionObjectIndex)
      else throw RuntimeError(expr->name, "CollisionObject property cannot be found.");
    }
    case FescriptCameraObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCameraObjectIndex)
      else if(expr->name.lexeme == "is_visible_on_camera") return std::make_shared<FescriptCameraObjectMemberIsVisibleOnCamera>(std::get<FescriptCameraObjectIndex>(object));
      else throw RuntimeError(expr->name, "CameraObject property cannot be found.");
    }
    default: {
      throw RuntimeError(expr->name, "only instances have properties.");
    }
  }
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Grouping> expr) {
  return this->evaluate(expr->expression);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Literal> expr) {
  return expr->value;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Array> expr) {
  std::shared_ptr<FescriptArray> array = std::make_shared<FescriptArray>();
  for(auto& element: expr->values) {
    array->values.push_back(this->evaluate(element));
  }
  return std::move(array);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Dict> expr) {
  std::shared_ptr<FescriptDict> dict = std::make_shared<FescriptDict>();
  for(const auto& [key, value]: expr->values) {
    dict->dictionary[this->evaluate(key)] = this->evaluate(value);
  }
  return std::move(dict);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Logical> expr) {
  if (Object left = this->evaluate(expr->left); expr->op.type == TokenType::OR) {
    if (this->is_truthy(left))
      return left;
  } else if (!this->is_truthy(left))
    return left;
  return this->evaluate(expr->right);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Set> expr) {
  Object object = this->evaluate(expr->object);
  Object value = this->evaluate(expr->value);
  switch(object.index()) {
    case FescriptBaseObjectIndex: {
      std::get<FescriptBaseObjectIndex>(object)->set(expr->name, value);
      return value;
    }
    case FescriptSpriteObjectIndex: {
      std::get<FescriptSpriteObjectIndex>(object)->set(expr->name, value);
      return value;
    }
    case FescriptLabelObjectIndex: {
      std::get<FescriptLabelObjectIndex>(object)->set(expr->name, value);
      return value;
    }
    case FescriptAreaObjectIndex: {
      std::get<FescriptAreaObjectIndex>(object)->set(expr->name, value);
      return value;
    }
    case FescriptCollisionObjectIndex: {
      std::get<FescriptCollisionObjectIndex>(object)->set(expr->name, value);
      return value;
    }
    case FescriptCameraObjectIndex: {
      std::get<FescriptCameraObjectIndex>(object)->set(expr->name, value);
      return value;
    }
  }
  if (object.index() != FescriptInstanceIndex)
    throw RuntimeError(expr->name, "only instances have fields.");
  std::get<FescriptInstanceIndex>(object)->set(expr->name, value);
  return value;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Super> expr) {
  const int &distance = this->locals[expr];
  auto superclass = std::get<FescriptClassIndex>(this->environment->get_at(distance, "super"));
  auto object = std::get<FescriptInstanceIndex>(this->environment->get_at(distance - 1, "this"));
  std::shared_ptr<FescriptFunction> method = superclass->find_method(expr->method.lexeme);
  if (method == nullptr)
    throw RuntimeError(expr->method, "undefined property '" + expr->method.lexeme + "'.");
  return method->bind(object);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<This> expr) {
  return this->look_up_variable(expr->keyword, expr);
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Unary> expr) {
  Object right = this->evaluate(expr->right);
  switch (expr->op.type) {
  case TokenType::BANG: {
    return !this->is_truthy(right);
  }
  case MINUS: {
    this->check_number_operand(expr->op, right);
    return -std::get<LongDoubleIndex>(right);
  }
  }
  return nullptr;
}

[[nodiscard]] Object Interpreter::visit(std::shared_ptr<Variable> expr) {
  // engine reserved names are has priority, so we don't need to look up from scope. they are global.
  if(expr->name.lexeme == "pos_x")
    return static_cast<idk::f80>(fresh::RenderObjects::find(this->render_object_id)->get_position_info().x);
  if(expr->name.lexeme == "pos_y")
    return static_cast<idk::f80>(fresh::RenderObjects::find(this->render_object_id)->get_position_info().y);
  if(expr->name.lexeme == "visible")
    return fresh::RenderObjects::find(this->render_object_id)->get_is_visible();
  if(expr->name.lexeme == "disabled")
    return fresh::RenderObjects::find(this->render_object_id)->get_is_disabled();
  // TODO: object specific variables.
  return this->look_up_variable(expr->name, expr);
}

void Interpreter::check_number_operand(const Token &op, const Object &operand) {
  if (operand.index() == LongDoubleIndex)
    return;
  throw RuntimeError(op, "operand must be a number.");
}

void Interpreter::check_number_operands(const Token &op, const Object &left,
                                        const Object &right) {
  if (left.index() == LongDoubleIndex && right.index() == LongDoubleIndex)
    return;
  throw RuntimeError(op, "operands must be numbers.");
}

[[nodiscard]] bool Interpreter::is_truthy(const Object &object) {
  switch (object.index()) {
  case NullptrIndex: {
    return false;
  }
  case BoolIndex: {
    return std::get<BoolIndex>(object);
  }
  }
  return true;
}

[[nodiscard]] bool Interpreter::is_equal(const Object &a, const Object &b) {
  if (a.index() == NullptrIndex && b.index() == NullptrIndex)
    return true;
  if (a.index() == NullptrIndex)
    return false;
  if (a.index() == StringIndex && b.index() == StringIndex)
    return std::get<StringIndex>(a) == std::get<StringIndex>(b);
  if (a.index() == LongDoubleIndex && b.index() == LongDoubleIndex)
    return std::get<LongDoubleIndex>(a) == std::get<LongDoubleIndex>(b);
  if (a.index() == BoolIndex && b.index() == BoolIndex)
    return std::get<BoolIndex>(a) == std::get<BoolIndex>(b);
  return false;
}

std::string Interpreter::stringify(const Object &object) {
  switch (object.index()) {
  case StringIndex: {
    return std::get<StringIndex>(object);
  }
  case BoolIndex: {
    return std::get<BoolIndex>(object) ? "true" : "false";
  }
  case LongDoubleIndex: {
    std::string text = std::to_string(std::get<LongDoubleIndex>(object));
    if (text.ends_with(".0"))
      text = text.substr(0, text.length() - 2);
    return text;
  }
  case FescriptFunctionIndex: {
    return std::get<FescriptFunctionIndex>(object)->to_string();
  }
  case FescriptClassIndex: {
    return std::get<FescriptClassIndex>(object)->to_string();
  }
  case FescriptInstanceIndex: {
    return std::get<FescriptInstanceIndex>(object)->to_string();
  }
  case FescriptArrayIndex: {
    return std::get<FescriptArrayIndex>(object)->to_string();
  }
  case FescriptDictIndex: {
    return std::get<FescriptDictIndex>(object)->to_string();
  }
  case FescriptCallableIndex: {
    return std::get<FescriptCallableIndex>(object)->to_string();
  }
  case FescriptBaseObjectIndex: {
    return std::get<FescriptBaseObjectIndex>(object)->to_string();
  }
  case FescriptSpriteObjectIndex: {
    return std::get<FescriptSpriteObjectIndex>(object)->to_string();
  }
  case FescriptLabelObjectIndex: {
    return std::get<FescriptLabelObjectIndex>(object)->to_string();
  }
  case FescriptAreaObjectIndex: {
    return std::get<FescriptAreaObjectIndex>(object)->to_string();
  }
  case FescriptCollisionObjectIndex: {
    return std::get<FescriptCollisionObjectIndex>(object)->to_string();
  }
  case FescriptCameraObjectIndex: {
    return std::get<FescriptCameraObjectIndex>(object)->to_string();
  }
  }
  return "nil";
}
}// namespace fescript