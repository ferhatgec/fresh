// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_array.hpp>
#include <fescript/fescript_dict.hpp>
#include <fescript/fescript_interpreter.hpp>
#include <render_objects.hpp>

#include <fescript/modules/fescript_math.hpp>
#include <fescript/modules/fescript_os.hpp>
#include <fescript/modules/fescript_path.hpp>
#include <fescript/modules/fescript_io.hpp>
#include <fescript/modules/fescript_prng.hpp>

#include <fescript/modules/engine_io.hpp>
#include <fescript/modules/engine.hpp>
#include <fescript/modules/engine_window.hpp>

#include <fescript/wrappers/animation/fescript_animation_frame_object.hpp>
#include <fescript/wrappers/animation/fescript_animation_player_object.hpp>
#include <fescript/wrappers/physics/fescript_area_object.hpp>
#include <fescript/wrappers/physics/fescript_rectangle_area_object.hpp>
#include <fescript/wrappers/physics/fescript_circle_area_object.hpp>
#include <fescript/wrappers/physics/fescript_polygon_area_object.hpp>
#include <fescript/wrappers/physics/fescript_world_object.hpp>
#include <fescript/wrappers/physics/fescript_body_object.hpp>
#include <fescript/wrappers/physics/fescript_rectangle_body_object.hpp>
#include <fescript/wrappers/physics/fescript_circle_body_object.hpp>
#include <fescript/wrappers/physics/fescript_polygon_body_object.hpp>
#include <fescript/wrappers/fescript_audio_player_object.hpp>
#include <fescript/wrappers/fescript_base_object.hpp>
#include <fescript/wrappers/fescript_camera_object.hpp>
#include <fescript/wrappers/fescript_circle_object.hpp>
#include <fescript/wrappers/fescript_label_object.hpp>
#include <fescript/wrappers/fescript_music_player_object.hpp>
#include <fescript/wrappers/fescript_polygon_object.hpp>
#include <fescript/wrappers/fescript_rectangle_object.hpp>
#include <fescript/wrappers/fescript_sprite_object.hpp>

#include <objects/animation/animation_player_object.hpp>
#include <objects/audio_player_object.hpp>
#include <objects/camera_object.hpp>
#include <objects/circle_object.hpp>
#include <objects/music_player_object.hpp>
#include <objects/polygon_object.hpp>
#include <objects/rectangle_object.hpp>
#include <objects/physics/circle_area_object.hpp>
#include <objects/physics/polygon_area_object.hpp>
#include <objects/physics/rectangle_area_object.hpp>
#include <objects/physics/world_object.hpp>
#include <objects/physics/rectangle_body_object.hpp>
#include <objects/physics/circle_body_object.hpp>
#include <objects/physics/polygon_body_object.hpp>
#include <chrono>

// TODO: Do not create new shared_ptr every member function call.
// Just create one for every BaseObject instance, make them *real* class member.
namespace fescript {
Interpreter::Interpreter() {
  this->globals = std::make_shared<Environment>();
  this->environment = this->globals;
  
  this->global_seed = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
    ).count();

  MATH_GLOBAL_FUNCTIONS()
  MATH_GLOBAL_CONSTANTS()

  this->globals->define("OS_platform", std::make_shared<FescriptOSPlatform>());
  this->globals->define("OS_exec", std::make_shared<FescriptOSExec>());
  this->globals->define("OS_arch", std::make_shared<FescriptOSArch>());
  this->globals->define("OS_get_clipboard_text", std::make_shared<FescriptOSGetClipboardText>());
  this->globals->define("OS_set_clipboard_text", std::make_shared<FescriptOSSetClipboardText>());

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

  this->globals->define("PRNG_get_global_seed", std::make_shared<FescriptPRNGGetGlobalSeed>());
  this->globals->define("PRNG_set_global_seed", std::make_shared<FescriptPRNGSetGlobalSeed>());
  this->globals->define("PRNG_generate_prn", std::make_shared<FescriptPRNGGeneratePRN>());
  this->globals->define("PRNG_generate_prn_between", std::make_shared<FescriptPRNGGeneratePRNBetween>());

  PRNG_GLOBAL_CONSTANTS()

  this->globals->define("EngineIO_is_key_pressed", std::make_shared<FescriptEngineIOIsKeyPressed>());
  this->globals->define("EngineIO_is_key_just_pressed", std::make_shared<FescriptEngineIOIsKeyJustPressed>());
  this->globals->define("EngineIO_is_key_released", std::make_shared<FescriptEngineIOIsKeyReleased>());
  this->globals->define("EngineIO_is_mouse_button_pressed", std::make_shared<FescriptEngineIOIsMouseButtonPressed>());
  this->globals->define("EngineIO_is_mouse_button_just_pressed", std::make_shared<FescriptEngineIOIsMouseButtonJustPressed>());

  ENGINEIO_INIT_CONSTANTS()

  // TODO: better we get rid of this but not top priority.
  this->globals->define("EngineWindow_get_current_window_size", std::make_shared<FescriptEngineWindowGetCurrentWindowSize>());
  this->globals->define("EngineWindow_get_current_window_pos", std::make_shared<FescriptEngineWindowGetCurrentWindowPos>());
  this->globals->define("EngineWindow_get_current_cursor_pos", std::make_shared<FescriptEngineWindowGetCurrentCursorPos>());
  this->globals->define("EngineWindow_set_window_icon", std::make_shared<FescriptEngineWindowSetWindowIcon>());
  this->globals->define("EngineWindow_set_window_title", std::make_shared<FescriptEngineWindowSetWindowTitle>());
  this->globals->define("EngineWindow_get_window_title", std::make_shared<FescriptEngineWindowGetWindowTitle>());
  this->globals->define("EngineWindow_set_window_cursor", std::make_shared<FescriptEngineWindowSetWindowCursor>());
  this->globals->define("EngineWindow_set_window_mode", std::make_shared<FescriptEngineWindowSetWindowMode>());
  this->globals->define("EngineWindow_get_window_mode", std::make_shared<FescriptEngineWindowGetWindowMode>());
  this->globals->define("EngineWindow_set_default_clear_color", std::make_shared<FescriptEngineWindowSetDefaultClearColor>());
  this->globals->define("EngineWindow_set_vsync", std::make_shared<FescriptEngineWindowSetVSync>());
  this->globals->define("EngineWindow_close_window", std::make_shared<FescriptEngineWindowCloseWindow>());
  this->globals->define("EngineWindow_maximize_window", std::make_shared<FescriptEngineWindowMaximizeWindow>());
  this->globals->define("EngineWindow_minimize_window", std::make_shared<FescriptEngineWindowMinimizeWindow>());
  this->globals->define("EngineWindow_restore_window", std::make_shared<FescriptEngineWindowRestoreWindow>());
  this->globals->define("EngineWindow_is_window_maximized", std::make_shared<FescriptEngineWindowIsWindowMaximized>());
  this->globals->define("EngineWindow_is_window_minimized", std::make_shared<FescriptEngineWindowIsWindowMinimized>());
  this->globals->define("EngineWindow_set_window_opacity", std::make_shared<FescriptEngineWindowSetWindowOpacity>());
  this->globals->define("EngineWindow_get_window_opacity", std::make_shared<FescriptEngineWindowGetWindowOpacity>());

  ENGINEWINDOW_GLOBAL_CONSTANTS()

  this->globals->define("Engine_BaseObject", std::make_shared<BaseObjectWrapper>());
  this->globals->define("Engine_SpriteObject", std::make_shared<SpriteObjectWrapper>());
  this->globals->define("Engine_LabelObject", std::make_shared<LabelObjectWrapper>());
  this->globals->define("Engine_AreaObject", std::make_shared<AreaObjectWrapper>());
  this->globals->define("Engine_CameraObject", std::make_shared<CameraObjectWrapper>());
  this->globals->define("Engine_AnimationPlayerObject", std::make_shared<AnimationPlayerObjectWrapper>());
  this->globals->define("Engine_AnimationFrameObject", std::make_shared<AnimationFrameObjectWrapper>());
  this->globals->define("Engine_MusicPlayerObject", std::make_shared<MusicPlayerObjectWrapper>());
  this->globals->define("Engine_AudioPlayerObject", std::make_shared<AudioPlayerObjectWrapper>());
  this->globals->define("Engine_CircleObject", std::make_shared<CircleObjectWrapper>());
  this->globals->define("Engine_PolygonObject", std::make_shared<PolygonObjectWrapper>());
  this->globals->define("Engine_RectangleObject", std::make_shared<RectangleObjectWrapper>());
  this->globals->define("Engine_RectangleAreaObject", std::make_shared<RectangleAreaObjectWrapper>());
  this->globals->define("Engine_CircleAreaObject", std::make_shared<CircleAreaObjectWrapper>());
  this->globals->define("Engine_PolygonAreaObject", std::make_shared<PolygonAreaObjectWrapper>());
  this->globals->define("Engine_WorldObject", std::make_shared<WorldObjectWrapper>());
  this->globals->define("Engine_BodyObject", std::make_shared<BodyObjectWrapper>());
  this->globals->define("Engine_RectangleBodyObject", std::make_shared<RectangleBodyObjectWrapper>());
  this->globals->define("Engine_PolygonBodyObject", std::make_shared<PolygonBodyObjectWrapper>());
  this->globals->define("Engine_CircleBodyObject", std::make_shared<CircleBodyObjectWrapper>());

  this->globals->define("Engine_load_fes", std::make_shared<FescriptEngineLoadFes>());
  this->globals->define("Engine_get_object", std::make_shared<FescriptEngineGetObject>());
  this->globals->define("Engine_link_camera", std::make_shared<FescriptEngineLinkCamera>());
}

void Interpreter::interpret(
  const std::vector<std::shared_ptr<Stmt>> &statements) {

  if(this->current_state != State::Invalid) {
    try {
      for(const std::shared_ptr<Stmt>& statement: statements) {
        if(auto cast_ptr = std::dynamic_pointer_cast<Function>(statement);
          cast_ptr != nullptr) {
          if((this->current_state == State::Update && cast_ptr->name.lexeme == "update")
            || (this->current_state == State::Init && cast_ptr->name.lexeme == "init")) {
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
  if(this->statements.empty())
    return;
  if(!this->is_initialized) {
    this->interpret_init();
    this->is_initialized = true;
  }
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
      && !(stmt->name.lexeme == "update" && this->current_state == State::Update)
      && !(stmt->name.lexeme == "init" && this->current_state == State::Init)) {
      std::cout << "Engine [language] error: There is already a function named as '" << stmt->name.lexeme << "'.\n";
      std::exit(1);
    }
  }
  auto function = std::make_shared<FescriptFunction>(stmt, environment, false);
  this->environment->define(stmt->name.lexeme, std::move(function));
  if((stmt->name.lexeme == "update" && this->current_state == State::Update) ||
    (stmt->name.lexeme == "init" && this->current_state == State::Init) ||
    (stmt->name.lexeme == "last" && this->current_state == State::Last)) {
    (void)this->visit(std::make_shared<Call>(std::make_shared<Variable>(Token(TokenType::IDENTIFIER,
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
      return static_cast<idk::f80>(std::get<LongDoubleIndex>(left) + std::get<LongDoubleIndex>(right));
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
  switch(callee.index()) {
    case FescriptFunctionIndex: {
      function = std::get<FescriptFunctionIndex>(callee);
      break;
    }
    case FescriptClassIndex: {
      function = std::get<FescriptClassIndex>(callee);
      break;
    }
    case FescriptCallableIndex: {
      function = std::get<FescriptCallableIndex>(callee);
      break;
    }
    default: {
      throw RuntimeError{expr->paren, "can only call functions and classes."};
    }
  }
  if ((arguments.size() != function->arity()) && (function->arity() != -1)) {
    if (function->is_variadic) {
      if (arguments.size() < function->arity())
        throw RuntimeError{expr->paren,
                           "expected at least " + std::to_string(function->arity()) + " arguments but got " +
                           std::to_string(arguments.size()) + "."};
    } else
        throw RuntimeError{expr->paren, "expected " + std::to_string(function->arity()) + " arguments but got " + std::to_string(arguments.size()) + "."};
  }
  return function->call(*this, arguments);
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
    case FescriptBaseObjectIndex:
    case FescriptSpriteObjectIndex:
    case FescriptLabelObjectIndex:
    case FescriptAreaObjectIndex:
    case FescriptCameraObjectIndex:
    case FescriptAnimationPlayerObjectIndex:
    case FescriptAnimationFrameObjectIndex:
    case FescriptMusicPlayerObjectIndex:
    case FescriptAudioPlayerObjectIndex:
    case FescriptCircleObjectIndex:
    case FescriptPolygonObjectIndex:
    case FescriptRectangleObjectIndex:
    case FescriptRectangleAreaObjectIndex:
    case FescriptCircleAreaObjectIndex:
    case FescriptPolygonAreaObjectIndex:
    case FescriptWorldObjectIndex:
    case FescriptBodyObjectIndex:
    case FescriptRectangleBodyObjectIndex:
    case FescriptCircleBodyObjectIndex:
    case FescriptPolygonBodyObjectIndex: {
      if(expr->is_name_an_expr)
        return "TODO"; // TODO
      return this->get_object_property(expr->name, object);
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
    SET_VISIT_IMPL_OBJECT(FescriptBaseObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptSpriteObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptLabelObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptAreaObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptCameraObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptAnimationPlayerObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptAnimationFrameObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptMusicPlayerObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptAudioPlayerObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptCircleObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptPolygonObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptRectangleObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptRectangleAreaObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptCircleAreaObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptPolygonAreaObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptWorldObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptBodyObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptRectangleBodyObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptCircleBodyObjectIndex)
    SET_VISIT_IMPL_OBJECT(FescriptPolygonBodyObjectIndex)
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
  // TODO: reserve a keyword that returns object that linked to script. then member variables will be automatically
  //  handled in set, assign and get nodes.
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

#define IS_INHERITED_BY(ptr_type) if(const auto& obj_##ptr_type = std::dynamic_pointer_cast<##ptr_type>(base_obj); obj_##ptr_type != nullptr)

[[nodiscard]] Object Interpreter::get_object_property(const Token& keyword, Object value) {
  using namespace fresh;
  // objects that generated by FesLoaderResource are encapsulated in BaseObject,
  // so we need to dynamic_cast that value to access object specific properties.
  if (value.index() == FescriptBaseObjectIndex) {
    const auto& base_obj = std::get<FescriptBaseObjectIndex>(value);
    IS_INHERITED_BY(SpriteObject) return Interpreter::get_object_property(keyword, obj_SpriteObject);
    else IS_INHERITED_BY(LabelObject) return Interpreter::get_object_property(keyword, obj_LabelObject);
    else IS_INHERITED_BY(AreaObject) return Interpreter::get_object_property(keyword, obj_AreaObject);
    else IS_INHERITED_BY(CameraObject) return Interpreter::get_object_property(keyword, obj_CameraObject);
    else IS_INHERITED_BY(AnimationPlayerObject) return Interpreter::get_object_property(keyword, obj_AnimationPlayerObject);
    else IS_INHERITED_BY(AnimationFrameObject) return Interpreter::get_object_property(keyword, obj_AnimationFrameObject);
    else IS_INHERITED_BY(MusicPlayerObject) return Interpreter::get_object_property(keyword, obj_MusicPlayerObject);
    else IS_INHERITED_BY(AudioPlayerObject) return Interpreter::get_object_property(keyword, obj_AudioPlayerObject);
    else IS_INHERITED_BY(RectangleObject) return Interpreter::get_object_property(keyword, obj_RectangleObject);
    else IS_INHERITED_BY(CircleObject) return Interpreter::get_object_property(keyword, obj_CircleObject);
    else IS_INHERITED_BY(PolygonObject) return Interpreter::get_object_property(keyword, obj_PolygonObject);
    else IS_INHERITED_BY(RectangleAreaObject) return Interpreter::get_object_property(keyword, obj_RectangleAreaObject);
    else IS_INHERITED_BY(PolygonAreaObject) return Interpreter::get_object_property(keyword, obj_PolygonAreaObject);
    else IS_INHERITED_BY(CircleAreaObject) return Interpreter::get_object_property(keyword, obj_CircleAreaObject);
    else IS_INHERITED_BY(BodyObject) return Interpreter::get_object_property(keyword, obj_BodyObject);
    else IS_INHERITED_BY(RectangleBodyObject) return Interpreter::get_object_property(keyword, obj_RectangleBodyObject);
    else IS_INHERITED_BY(CircleBodyObject) return Interpreter::get_object_property(keyword, obj_CircleBodyObject);
    else IS_INHERITED_BY(PolygonBodyObject) return Interpreter::get_object_property(keyword, obj_PolygonBodyObject);
    else IS_INHERITED_BY(WorldObject) return Interpreter::get_object_property(keyword, obj_WorldObject);
  }

  switch (value.index()) {
    case FescriptBaseObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptBaseObjectIndex)
      break;
    }
    case FescriptSpriteObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptSpriteObjectIndex)
      else if (keyword.lexeme == "sprite_resource") return std::string(std::get<FescriptSpriteObjectIndex>(value)->get_sprite_resource()._texture_path.data());
      else if (keyword.lexeme == "init_sprite"    ) return std::make_shared<FescriptSpriteObjectMemberInitSprite>(std::get<FescriptSpriteObjectIndex>(value));
      else throw RuntimeError(keyword, "SpriteObject property cannot be found.");
    }
    case FescriptLabelObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptLabelObjectIndex)
      else if (keyword.lexeme == "background_red"  ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().r);
      else if (keyword.lexeme == "background_green") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().g);
      else if (keyword.lexeme == "background_blue" ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().b);
      else if (keyword.lexeme == "background_alpha") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().a);
      else if (keyword.lexeme == "foreground_red"  ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_foreground_color().r);
      else if (keyword.lexeme == "background_blue" ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().b);
      else if (keyword.lexeme == "background_alpha") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_background_color().a);
      else if (keyword.lexeme == "foreground_red"  ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_foreground_color().r);
      else if (keyword.lexeme == "foreground_green") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_foreground_color().g);
      else if (keyword.lexeme == "foreground_blue" ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_foreground_color().b);
      else if (keyword.lexeme == "foreground_alpha") return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_foreground_color().a);
      else if (keyword.lexeme == "label_text"      ) return std::string(std::get<FescriptLabelObjectIndex>(value)->get_label_text().data());
      else if (keyword.lexeme == "font_size"       ) return static_cast<idk::f80>(std::get<FescriptLabelObjectIndex>(value)->get_label_font_resource().get_font_size());
      else if (keyword.lexeme == "font_resource"   ) return std::string(std::get<FescriptLabelObjectIndex>(value)->get_label_font_resource().get_font_path().data());
      else if (keyword.lexeme == "init_font"       ) return std::make_shared<FescriptLabelObjectMemberInitFont>(std::get<FescriptLabelObjectIndex>(value));
      else if (keyword.lexeme == "init_text"       ) return std::make_shared<FescriptLabelObjectMemberInitText>(std::get<FescriptLabelObjectIndex>(value));
      else throw RuntimeError(keyword, "LabelObject property cannot be found.");
    }
    case FescriptAreaObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptAreaObjectIndex)
      else if (keyword.lexeme == "is_colliding_with") return std::make_shared<FescriptAreaObjectMemberIsCollidingWith>(std::get<FescriptAreaObjectIndex>(value));
      else throw RuntimeError(keyword, "AreaObject property cannot be found.");
    }
    case FescriptCameraObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCameraObjectIndex)
      else if(keyword.lexeme == "is_visible_on_camera") return std::make_shared<FescriptCameraObjectMemberIsVisibleOnCamera>(std::get<FescriptCameraObjectIndex>(value));
      else if(keyword.lexeme == "move") return std::make_shared<FescriptCameraObjectMemberMove>(std::get<FescriptCameraObjectIndex>(value));
      else throw RuntimeError(keyword, "CameraObject property cannot be found.");
    }
    case FescriptAnimationPlayerObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptAnimationPlayerObjectIndex)
      else if(keyword.lexeme == "push_frame") return std::make_shared<FescriptAnimationPlayerObjectMemberPushFrame>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "run_animation") return std::make_shared<FescriptAnimationPlayerObjectMemberRunAnimation>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "pause_animation") return std::make_shared<FescriptAnimationPlayerObjectMemberPauseAnimation>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_animation") return std::make_shared<FescriptAnimationPlayerObjectMemberStopAnimation>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "set_replay_status") return std::make_shared<FescriptAnimationPlayerObjectMemberSetReplayStatus>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "is_started") return std::make_shared<FescriptAnimationPlayerObjectMemberIsStarted>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else if(keyword.lexeme == "synchronize_frames") return std::make_shared<FescriptAnimationPlayerObjectMemberSynchronizeFrames>(std::get<FescriptAnimationPlayerObjectIndex>(value));
      else throw RuntimeError(keyword, "AnimationPlayerObject property cannot be found.");
    }
    case FescriptAnimationFrameObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptAnimationFrameObjectIndex)
      else throw RuntimeError(keyword, "AnimationFrameObject property cannot be found.");
    }
    case FescriptMusicPlayerObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptMusicPlayerObjectIndex)
      else if(keyword.lexeme == "load_music_source") return std::make_shared<FescriptMusicPlayerObjectMemberLoadMusicSource>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "get_music_volume") return std::make_shared<FescriptMusicPlayerObjectMemberGetMusicVolume>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "sync_music_volume") return std::make_shared<FescriptMusicPlayerObjectMemberSyncMusicVolume>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "pause_music") return std::make_shared<FescriptMusicPlayerObjectMemberPauseMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "resume_music") return std::make_shared<FescriptMusicPlayerObjectMemberResumeMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "play_music") return std::make_shared<FescriptMusicPlayerObjectMemberPlayMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "play_fade_in_music") return std::make_shared<FescriptMusicPlayerObjectMemberPlayFadeInMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_music") return std::make_shared<FescriptMusicPlayerObjectMemberStopMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_fade_out_music") return std::make_shared<FescriptMusicPlayerObjectMemberStopFadeOutMusic>(std::get<FescriptMusicPlayerObjectIndex>(value));
      else throw RuntimeError(keyword, "MusicPlayerObject property cannot be found.");
    }
    case FescriptAudioPlayerObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptAudioPlayerObjectIndex)
      else if(keyword.lexeme == "load_audio_source") return std::make_shared<FescriptAudioPlayerObjectMemberLoadAudioSource>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "get_audio_volume") return std::make_shared<FescriptAudioPlayerObjectMemberGetAudioVolume>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "sync_audio_volume") return std::make_shared<FescriptAudioPlayerObjectMemberSyncAudioVolume>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "pause_audio") return std::make_shared<FescriptAudioPlayerObjectMemberPauseAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "pause_all_audio") return std::make_shared<FescriptAudioPlayerObjectMemberPauseAllAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "resume_audio") return std::make_shared<FescriptAudioPlayerObjectMemberResumeAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "resume_all_audio") return std::make_shared<FescriptAudioPlayerObjectMemberResumeAllAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "play_audio") return std::make_shared<FescriptAudioPlayerObjectMemberPlayAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "play_fade_in_audio") return std::make_shared<FescriptAudioPlayerObjectMemberPlayFadeInAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_audio") return std::make_shared<FescriptAudioPlayerObjectMemberStopAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_all_audio") return std::make_shared<FescriptAudioPlayerObjectMemberStopAllAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else if(keyword.lexeme == "stop_fade_out_audio") return std::make_shared<FescriptAudioPlayerObjectMemberStopFadeOutAudio>(std::get<FescriptAudioPlayerObjectIndex>(value));
      else throw RuntimeError(keyword, "AudioPlayerObject property cannot be found.");
    }
    case FescriptCircleObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCircleObjectIndex)
      else if(keyword.lexeme == "get_radius") return std::make_shared<FescriptCircleObjectMemberGetRadius>(std::get<FescriptCircleObjectIndex>(value));
      else if(keyword.lexeme == "get_segments") return std::make_shared<FescriptCircleObjectMemberGetSegments>(std::get<FescriptCircleObjectIndex>(value));
      else if(keyword.lexeme == "get_is_filled") return std::make_shared<FescriptCircleObjectMemberGetIsFilled>(std::get<FescriptCircleObjectIndex>(value));
      else if(keyword.lexeme == "set_radius") return std::make_shared<FescriptCircleObjectMemberSetSegments>(std::get<FescriptCircleObjectIndex>(value));
      else if(keyword.lexeme == "set_segments") return std::make_shared<FescriptCircleObjectMemberSetSegments>(std::get<FescriptCircleObjectIndex>(value));
      else if(keyword.lexeme == "set_is_filled") return std::make_shared<FescriptCircleObjectMemberSetIsFilled>(std::get<FescriptCircleObjectIndex>(value));
      else throw RuntimeError(keyword, "CircleObject property cannot be found.");
    }
    case FescriptPolygonObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptPolygonObjectIndex)
      else if(keyword.lexeme == "push_polygon") return std::make_shared<FescriptPolygonObjectMemberPushPolygon>(std::get<FescriptPolygonObjectIndex>(value));
      else if(keyword.lexeme == "delete_all_polygons") return std::make_shared<FescriptPolygonObjectMemberDeleteAllPolygons>(std::get<FescriptPolygonObjectIndex>(value));
      else if(keyword.lexeme == "get_is_filled") return std::make_shared<FescriptPolygonObjectMemberDeleteAllPolygons>(std::get<FescriptPolygonObjectIndex>(value));
      else throw RuntimeError(keyword, "PolygonObject property cannot be found.");
    }
    case FescriptRectangleObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptRectangleObjectIndex)
      else throw RuntimeError(keyword, "RectangleObject property cannot be found.");
    }
    case FescriptRectangleAreaObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptRectangleAreaObjectIndex)
      else if(keyword.lexeme == "is_colliding_with") return std::make_shared<FescriptRectangleAreaObjectMemberIsCollidingWith>(std::get<FescriptRectangleAreaObjectIndex>(value));
      else throw RuntimeError(keyword, "RectangleAreaObject property cannot be found.");
    }
    case FescriptCircleAreaObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCircleAreaObjectIndex)
      else if(keyword.lexeme == "get_radius") return std::make_shared<FescriptCircleAreaObjectMemberGetRadius>(std::get<FescriptCircleAreaObjectIndex>(value));
      else if(keyword.lexeme == "set_radius") return std::make_shared<FescriptCircleAreaObjectMemberSetRadius>(std::get<FescriptCircleAreaObjectIndex>(value));
      else if(keyword.lexeme == "is_colliding_with") return std::make_shared<FescriptCircleAreaObjectMemberIsCollidingWith>(std::get<FescriptCircleAreaObjectIndex>(value));
      else throw RuntimeError(keyword, "CircleAreaObject property cannot be found.");
    }
    case FescriptPolygonAreaObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptPolygonAreaObjectIndex)
      else if(keyword.lexeme == "is_colliding_with") return std::make_shared<FescriptPolygonAreaObjectMemberIsCollidingWith>(std::get<FescriptPolygonAreaObjectIndex>(value));
      else if(keyword.lexeme == "push_polygon") return std::make_shared<FescriptPolygonAreaObjectMemberPushPolygon>(std::get<FescriptPolygonAreaObjectIndex>(value));
      else if(keyword.lexeme == "delete_all_polygons") return std::make_shared<FescriptPolygonAreaObjectMemberDeleteAllPolygons>(std::get<FescriptPolygonAreaObjectIndex>(value));
      else throw RuntimeError(keyword, "PolygonAreaObject property cannot be found.");
    }
    case FescriptWorldObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptWorldObjectIndex)
      else if(keyword.lexeme == "get_substep_count") return std::make_shared<FescriptWorldObjectMemberGetSubstepCount>(std::get<FescriptWorldObjectIndex>(value));
      else if(keyword.lexeme == "get_physics_frame") return std::make_shared<FescriptWorldObjectMemberGetPhysicsFrame>(std::get<FescriptWorldObjectIndex>(value));
      else if(keyword.lexeme == "get_timestep") return std::make_shared<FescriptWorldObjectMemberGetTimestep>(std::get<FescriptWorldObjectIndex>(value));
      else if(keyword.lexeme == "set_substep_count") return std::make_shared<FescriptWorldObjectMemberSetSubstepCount>(std::get<FescriptWorldObjectIndex>(value));
      else if(keyword.lexeme == "set_physics_frame") return std::make_shared<FescriptWorldObjectMemberSetPhysicsFrame>(std::get<FescriptWorldObjectIndex>(value));
      else throw RuntimeError(keyword, "WorldObject property cannot be found.");
    }
    case FescriptBodyObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptBodyObjectIndex)
      else throw RuntimeError(keyword, "BodyObject property cannot be found.");
    }
    case FescriptRectangleBodyObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptRectangleBodyObjectIndex)
      else if(keyword.lexeme == "set_is_static_body") return std::make_shared<FescriptRectangleBodyObjectMemberSetIsStaticBody>(std::get<FescriptRectangleBodyObjectIndex>(value));
      else if(keyword.lexeme == "get_is_static_body") return std::make_shared<FescriptRectangleBodyObjectMemberGetIsStaticBody>(std::get<FescriptRectangleBodyObjectIndex>(value));
      else throw RuntimeError(keyword, "RectangleBodyObject property cannot be found.");
    }
    case FescriptCircleBodyObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptCircleBodyObjectIndex)
      else if(keyword.lexeme == "set_is_static_body") return std::make_shared<FescriptCircleBodyObjectMemberSetIsStaticBody>(std::get<FescriptCircleBodyObjectIndex>(value));
      else if(keyword.lexeme == "get_is_static_body") return std::make_shared<FescriptCircleBodyObjectMemberGetIsStaticBody>(std::get<FescriptCircleBodyObjectIndex>(value));
      else if(keyword.lexeme == "set_radius") return std::make_shared<FescriptCircleBodyObjectMemberSetRadius>(std::get<FescriptCircleBodyObjectIndex>(value));
      else if(keyword.lexeme == "get_radius") return std::make_shared<FescriptCircleBodyObjectMemberGetRadius>(std::get<FescriptCircleBodyObjectIndex>(value));
      else throw RuntimeError(keyword, "CircleBodyObject property cannot be found.");
    }
    case FescriptPolygonBodyObjectIndex: {
      RETURN_BASE_OBJECT_PROPERTIES(FescriptPolygonBodyObjectIndex)
      else if(keyword.lexeme == "set_is_static_body") return std::make_shared<FescriptPolygonBodyObjectMemberSetIsStaticBody>(std::get<FescriptPolygonBodyObjectIndex>(value));
      else if(keyword.lexeme == "get_is_static_body") return std::make_shared<FescriptRectangleBodyObjectMemberGetIsStaticBody>(std::get<FescriptRectangleBodyObjectIndex>(value));
      else throw RuntimeError(keyword, "PolygonBodyObject property cannot be found.");
    }
    default: {
      std::cout << "Engine error: Invalid pointer passed to get_object_property!\n";
      std::exit(1);
    }
  }
}

[[nodiscard]] Object Interpreter::baseobject_to_fescript_object(std::shared_ptr<fresh::BaseObject> base_obj) noexcept {
  using namespace fresh;
  IS_INHERITED_BY(SpriteObject) return obj_SpriteObject;
  else IS_INHERITED_BY(LabelObject) return obj_LabelObject;
  else IS_INHERITED_BY(AreaObject) return obj_AreaObject;
  else IS_INHERITED_BY(CameraObject) return obj_CameraObject;
  else IS_INHERITED_BY(AnimationPlayerObject) return obj_AnimationPlayerObject;
  else IS_INHERITED_BY(AnimationFrameObject) return obj_AnimationFrameObject;
  else IS_INHERITED_BY(MusicPlayerObject) return obj_MusicPlayerObject;
  else IS_INHERITED_BY(AudioPlayerObject) return obj_AudioPlayerObject;
  else IS_INHERITED_BY(RectangleObject) return obj_RectangleObject;
  else IS_INHERITED_BY(CircleObject) return obj_CircleObject;
  else IS_INHERITED_BY(PolygonObject) return obj_PolygonObject;
  else IS_INHERITED_BY(RectangleAreaObject) return obj_RectangleAreaObject;
  else IS_INHERITED_BY(PolygonAreaObject) return obj_PolygonAreaObject;
  else IS_INHERITED_BY(CircleAreaObject) return obj_CircleAreaObject;
  else IS_INHERITED_BY(BodyObject) return obj_BodyObject;
  else IS_INHERITED_BY(RectangleBodyObject) return obj_RectangleBodyObject;
  else IS_INHERITED_BY(CircleBodyObject) return obj_CircleBodyObject;
  else IS_INHERITED_BY(PolygonBodyObject) return obj_PolygonBodyObject;
  else IS_INHERITED_BY(WorldObject) return obj_WorldObject;
  else return base_obj;
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
  GET_STRINGIFY_IMPL_OBJECT(FescriptFunctionIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptClassIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptInstanceIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptArrayIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptDictIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptCallableIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptBaseObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptSpriteObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptLabelObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptAreaObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptCameraObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptAnimationPlayerObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptAnimationFrameObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptMusicPlayerObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptAudioPlayerObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptCircleObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptPolygonObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptRectangleObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptRectangleAreaObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptCircleAreaObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptPolygonAreaObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptWorldObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptBodyObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptRectangleBodyObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptCircleBodyObjectIndex)
  GET_STRINGIFY_IMPL_OBJECT(FescriptPolygonBodyObjectIndex)
  }
  return "nil";
}

[[nodiscard]] std::shared_ptr<fresh::BaseObject>& Interpreter::get_parent_object() noexcept {
  return this->_parent_object;
}

[[nodiscard]] idk::i64& Interpreter::get_global_seed() noexcept {
  return this->global_seed;
}
}// namespace fescript