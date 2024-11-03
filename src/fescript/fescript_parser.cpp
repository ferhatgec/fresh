// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fescript/fescript_array.hpp>
#include <fescript/fescript_parser.hpp>

namespace fescript {
Parser::Parser(const std::vector<Token> &tokens)
    : tokens{tokens} {
}

[[nodiscard]] std::vector<std::shared_ptr<Stmt>> Parser::parse() {
  std::vector<std::shared_ptr<Stmt>> statements;
  while (!this->is_at_end()) {
    statements.push_back(std::move(this->declaration()));
  }
  return statements;
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::declaration() {
  try {
    if (this->match({TokenType::TOKEN_CLASS}))
      return std::move(this->class_declaration());
    if (this->match({TokenType::TOKEN_FUN}))
      return std::move(this->function("function"));
    if (this->match({TokenType::TOKEN_VAR}))
      return std::move(this->var_declaration("function"));
    return std::move(this->statement());
  } catch (const ParseError &error) {
    this->synchronize();
    return nullptr;
  }
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::class_declaration() {
  Token name = this->consume(TokenType::TOKEN_IDENTIFIER, "expect class name.");
  std::shared_ptr<Variable> superclass = nullptr;
  if (this->match({TokenType::TOKEN_LESS})) {
    this->consume(TokenType::TOKEN_IDENTIFIER, "expect superclass name.");
    superclass = std::make_shared<Variable>(this->previous());
  }
  this->consume(TokenType::TOKEN_EQUAL, "expect '=' before class body.");
  std::vector<std::shared_ptr<Function>> methods;
  while (!this->check(TokenType::TOKEN_SEMICOLON) && !this->is_at_end()) {
    this->consume(TokenType::TOKEN_VAR, "expected function in class member.");
    methods.push_back(this->function("method"));
  }
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after class body");
  return std::make_shared<Class>(std::move(name), std::move(superclass), std::move(methods));
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::statement() {
  if (this->match({TokenType::TOKEN_FOR}))
    return std::move(this->for_statement());
  if (this->match({TokenType::TOKEN_IF}))
    return std::move(this->if_statement());
  if (this->match({TokenType::TOKEN_RETURN}))
    return std::move(this->return_statement());
  if (this->match({TokenType::TOKEN_WHILE}))
    return std::move(this->while_statement());
  if (this->match({TokenType::TOKEN_DOT})) {
    if(this->match({TokenType::TOKEN_EQUAL})) {
      return std::make_shared<Block>(std::move(this->block()));
    }
    throw parse_error(this->peek(), "expect '=' after block declaration.");
  }
  return std::move(this->expression_statement());
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::for_statement() {
  this->consume(TokenType::TOKEN_LEFT_PAREN, "expect '(' after 'for'.");
  std::shared_ptr<Stmt> initializer;
  if (this->match({TokenType::TOKEN_SEMICOLON})) {
    initializer = nullptr;
  } else if (this->match({TokenType::TOKEN_VAR})) {
    initializer = std::move(this->var_declaration());
  } else {
    initializer = std::move(this->expression_statement());
  }
  std::shared_ptr<Expr> condition = nullptr;
  if (!this->check(TokenType::TOKEN_SEMICOLON)) {
    condition = std::move(this->expression());
  }
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after loop condition.");
  std::shared_ptr<Expr> increment = nullptr;
  if (!this->check(TokenType::TOKEN_RIGHT_PAREN)) {
    increment = std::move(this->expression());
  }
  this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after for clauses.");
  this->consume(TokenType::TOKEN_EQUAL, "expect '=' after 'for'.");
  auto body_elements = this->block();
  std::shared_ptr<Stmt> body;
  if (increment != nullptr) {
    body_elements.emplace_back(std::make_shared<Expression>(std::move(increment)));
    body = std::make_shared<Block>(std::move(body_elements));
  }
  if (condition == nullptr) {
    condition = std::make_shared<Literal>(true);
  }
  body = std::make_shared<While>(condition, body);
  if (initializer != nullptr) {
    body = std::make_shared<Block>(std::vector<std::shared_ptr<Stmt>>{
      std::move(initializer), body});
  }
  return std::move(body);
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::if_statement() {
  this->consume(TokenType::TOKEN_LEFT_PAREN, "expect '(' after 'if'.");
  std::shared_ptr<Expr> condition = std::move(this->expression());
  this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after if condition.");
  (void)this->advance();
  std::shared_ptr<Block> then_branch = std::make_shared<Block>(std::move(this->block()));
  std::map<std::shared_ptr<Expr>, std::shared_ptr<Block>> elifs;
  std::shared_ptr<Block> else_branch = nullptr;
  while(this->check(TokenType::TOKEN_ELIF)) {
    (void)this->advance();
    this->consume(TokenType::TOKEN_LEFT_PAREN, "expect '(' after 'elif'.");
    std::shared_ptr<Expr> condition = std::move(this->expression());
    this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after elif condition.");
    this->consume(TokenType::TOKEN_EQUAL, "expect '=' after 'elif'.");
    std::shared_ptr<Block> elif_then_branch = std::make_shared<Block>(std::move(this->block()));
    elifs[std::move(condition)] = std::move(elif_then_branch);
  }
  if (this->match({TokenType::TOKEN_ELSE})) {
    this->consume(TokenType::TOKEN_EQUAL, "expect '=' after 'else'.");
    else_branch = std::make_shared<Block>(std::move(this->block()));
  }
  return std::make_shared<If>(std::move(condition), std::move(then_branch), std::move(elifs), std::move(else_branch));
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::return_statement() {
  Token keyword = this->previous();
  std::shared_ptr<Expr> value = nullptr;
  if (!this->check(TokenType::TOKEN_SEMICOLON))
    value = std::move(this->expression());
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after return value.");
  return std::make_shared<Return>(keyword, std::move(value));
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::var_declaration(std::string kind) {
  Token name = this->consume(TokenType::TOKEN_IDENTIFIER, "expect variable name.");
  std::shared_ptr<Expr> initializer = nullptr;
  if(this->match({TokenType::TOKEN_LEFT_PAREN})) { // function definition.
    this->current -= 2;
    return std::move(this->function(std::move(kind)));
  }
  if (this->match({TokenType::TOKEN_EQUAL})) {
    initializer = std::move(this->expression());
  }
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after variable declaration.");
  return std::make_shared<Var>(std::move(name), std::move(initializer));
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::while_statement() {
  this->consume(TokenType::TOKEN_LEFT_PAREN, "expect '(' after 'while'.");
  std::shared_ptr<Expr> condition = std::move(this->expression());
  this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after condition.");
  std::shared_ptr<Stmt> body = std::move(this->statement());
  return std::make_shared<While>(std::move(condition), std::move(body));
}

[[nodiscard]] std::shared_ptr<Stmt> Parser::expression_statement() {
  std::shared_ptr<Expr> expr = std::move(this->expression());
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after expression.");
  return std::make_shared<Expression>(std::move(expr));
}

[[nodiscard]] std::shared_ptr<Function> Parser::function(std::string kind) {
  Token name = this->consume(TokenType::TOKEN_IDENTIFIER, "expect " + kind + " name.");
  this->consume(TokenType::TOKEN_LEFT_PAREN, "expect '(' after " + kind + " name.");
  std::vector<Token> parameters;
  bool is_variadic { false };
  if (!this->check(TokenType::TOKEN_RIGHT_PAREN)) {
    do {
      if (parameters.size() >= 255) {
        error(this->peek(), "can't have more than 255 parameters.");
      }
      parameters.push_back(this->consume(TokenType::TOKEN_IDENTIFIER, "expect parameter name."));
      // there must be only 1 variadic argument,
      // otherwise fescript cannot link arguments with their values.
      if(this->check(TokenType::TOKEN_VARIADIC)) {
        parameters.back().is_variadic = true;
        (void)this->advance();
        is_variadic = true;
        break; // no argument cannot be passed to function after the variadic argument.
      }
    } while(this->match({TokenType::TOKEN_COMMA}));
  }
  if(is_variadic && this->check(TokenType::TOKEN_COMMA)) {
    error(this->peek(), "cannot define any argument after passing the variadic argument.");
  }
  this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after parameters.");
  this->consume(TokenType::TOKEN_EQUAL, "expect '=' before " + kind + " body.");
  std::vector<std::shared_ptr<Stmt>> body = this->block();
  return std::make_shared<Function>(std::move(name), std::move(parameters), std::move(body), is_variadic);
}

[[nodiscard]] std::vector<std::shared_ptr<Stmt>> Parser::block() {
  std::vector<std::shared_ptr<Stmt>> statements;
  while (!this->check(TokenType::TOKEN_SEMICOLON) && !this->is_at_end())
    statements.push_back(std::move(this->declaration()));
  this->consume(TokenType::TOKEN_SEMICOLON, "expect ';' after block.");
  return statements;
}

[[nodiscard]] std::shared_ptr<Expr> Parser::expression() {
  return std::move(this->assignment());
}

[[nodiscard]] std::shared_ptr<Expr> Parser::assignment() {
  std::shared_ptr<Expr> expr = std::move(this->or_());
  if (this->match({TokenType::TOKEN_EQUAL})) {
    Token equals = this->previous();
    std::shared_ptr<Expr> value = std::move(this->assignment());
    if (const std::shared_ptr<Variable> &variable = std::dynamic_pointer_cast<Variable>(expr);
        variable != nullptr)
      return std::make_shared<Assign>(variable->name, std::move(value));
    else if (const std::shared_ptr<Get> get = std::dynamic_pointer_cast<Get>(expr);
             get != nullptr)
      return std::make_shared<Set>(get->object, get->name, std::move(value));
    error(std::move(equals), "invalid assignment target.");
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::or_() {
  std::shared_ptr<Expr> expr = std::move(this->and_());
  while (this->match({TokenType::TOKEN_OR})) {
    Token op = this->previous();
    expr = std::make_shared<Logical>(std::move(expr), std::move(op), std::move(this->and_()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::and_() {
  std::shared_ptr<Expr> expr = std::move(this->equality());
  while (this->match({TokenType::TOKEN_AND})) {
    Token op = this->previous();
    expr = std::make_shared<Logical>(expr, std::move(op), std::move(this->equality()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::equality() {
  std::shared_ptr<Expr> expr = std::move(this->comparison());
  while (this->match({TokenType::TOKEN_BANG_EQUAL, TokenType::TOKEN_EQUAL_EQUAL})) {
    Token op = this->previous();
    expr = std::make_shared<Binary>(expr, std::move(op), std::move(this->comparison()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::comparison() {
  std::shared_ptr<Expr> expr = std::move(this->term());
  while (this->match({TokenType::TOKEN_GREATER, TokenType::TOKEN_GREATER_EQUAL,
                      TokenType::TOKEN_LESS, TokenType::TOKEN_LESS_EQUAL})) {
    Token op = this->previous();
    expr = std::make_shared<Binary>(expr, std::move(op), std::move(this->term()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::term() {
  std::shared_ptr<Expr> expr = std::move(this->factor());
  while (this->match({TokenType::TOKEN_MINUS, TokenType::TOKEN_PLUS})) {
    Token op = this->previous();
    expr = std::make_shared<Binary>(expr, std::move(op), std::move(this->factor()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::factor() {
  std::shared_ptr<Expr> expr = std::move(this->unary());
  while (this->match({TokenType::TOKEN_SLASH, TokenType::TOKEN_STAR, TokenType::TOKEN_PERCENT})) {
    Token op = this->previous();
    expr = std::make_shared<Binary>(expr, std::move(op), std::move(this->unary()));
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::unary() {
  if (this->match({TokenType::TOKEN_BANG, TokenType::TOKEN_MINUS})) {
    Token op = this->previous();
    return std::make_shared<Unary>(std::move(op), std::move(this->unary()));
  }
  return std::move(this->call());
}

[[nodiscard]] std::shared_ptr<Expr> Parser::finish_call(std::shared_ptr<Expr> callee) {
  std::vector<std::shared_ptr<Expr>> arguments;
  if (!this->check(TokenType::TOKEN_RIGHT_PAREN)) {
    do {
      if (arguments.size() >= 255) {
        error(this->peek(), "can't have more than 255 arguments.");
      }
      arguments.push_back(std::move(this->expression()));
    } while (this->match({TokenType::TOKEN_COMMA}));
  }
  Token paren = this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after arguments.");
  return std::make_shared<Call>(callee, std::move(paren), std::move(arguments));
}

[[nodiscard]] std::shared_ptr<Expr> Parser::call() {
  std::shared_ptr<Expr> expr = std::move(this->primary());
  while (true) {
    if (this->match({TokenType::TOKEN_LEFT_PAREN})) {
      expr = this->finish_call(expr);
    } else if (this->match({TokenType::TOKEN_DOT})) {
      if(this->check(TokenType::TOKEN_IDENTIFIER) || this->check(TokenType::TOKEN_NUMBER)) {
        Token name = this->consume({ TokenType::TOKEN_IDENTIFIER,
                                    TokenType::TOKEN_NUMBER}, "expect property name after '.'.");
        expr = std::make_shared<Get>(expr,
                                     std::move(name),
                                     std::make_shared<Variable>(name));
      } else {
        expr = std::make_shared<Get>(expr,
                                     std::move(this->expression()),
                                     this->peek(),
                                     std::make_shared<Variable>(this->peek()));
      }
    } else {
      break;
    }
  }
  return std::move(expr);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::primary() {
  if (this->match({TokenType::TOKEN_FALSE}))
    return std::make_shared<Literal>(false);
  if (this->match({TokenType::TOKEN_TRUE}))
    return std::make_shared<Literal>(true);
  if (this->match({TokenType::TOKEN_NIL}))
    return std::make_shared<Literal>(nullptr);
  if (this->match({TokenType::TOKEN_NUMBER, TokenType::TOKEN_STRING}))
    return std::make_shared<Literal>(this->previous().literal);
  if (this->match({TokenType::TOKEN_SUPER})) {
    Token keyword = this->previous();
    this->consume(TokenType::TOKEN_DOT, "expect '.' after 'super'.");
    Token method = this->consume(TokenType::TOKEN_IDENTIFIER, "expect superclass method name.");
    return std::make_shared<Super>(std::move(keyword), std::move(method));
  }
  if(this->match({TokenType::TOKEN_LEFT_BOX_PAREN})) {
    return std::move(this->array());
  }
  if(this->match({TokenType::TOKEN_LEFT_BRACE})) {
    return std::move(this->dict());
  }
  if (this->match({TokenType::TOKEN_THIS}))
    return std::make_shared<This>(std::move(this->previous()));
  if (this->match({TokenType::TOKEN_IDENTIFIER}))
    return std::make_shared<Variable>(std::move(this->previous()));
  if (this->match({TokenType::TOKEN_LEFT_PAREN})) {
    std::shared_ptr<Expr> expr = std::move(this->expression());
    this->consume(TokenType::TOKEN_RIGHT_PAREN, "expect ')' after expression.");
    return std::make_shared<Grouping>(std::move(expr));
  }
  throw parse_error(this->peek(), "expect expression.");
}

[[nodiscard]] std::shared_ptr<Expr> Parser::array() {
  std::vector<std::shared_ptr<Expr>> array_content;
  if (!this->check(TokenType::TOKEN_RIGHT_BOX_PAREN)) {
    do {
      array_content.push_back(std::move(this->expression()));
    } while (this->match({TokenType::TOKEN_COMMA}));
  }
  (void)this->consume(TokenType::TOKEN_RIGHT_BOX_PAREN, "expect ']' after end of array.");
  return std::make_shared<Array>(array_content);
}

[[nodiscard]] std::shared_ptr<Expr> Parser::dict() {
  std::unordered_map<std::shared_ptr<Expr>, std::shared_ptr<Expr>> dict_content;
  if(!this->check({ TokenType::TOKEN_RIGHT_BRACE })) {
    do {
      std::shared_ptr<Expr> key = std::move(this->expression());
      this->consume(TokenType::TOKEN_COLON, "expect ':' after dict key.");
      std::shared_ptr<Expr> value = std::move(this->expression());
      dict_content[std::move(key)] = std::move(value);
    } while(this->match({TokenType::TOKEN_COMMA}));
  }
  (void)this->consume(TokenType::TOKEN_RIGHT_BRACE, "expect '}' after end of dict.");
  return std::make_shared<Dict>(dict_content);
}

[[nodiscard]] bool Parser::match(std::initializer_list<TokenType> &&type) {
  for (auto &typ : std::move(type)) {
    if (this->check(typ)) {
      this->advance();
      return true;
    }
  }
  return false;
}

[[nodiscard]] bool Parser::check(TokenType type) {
  if (this->is_at_end())
    return false;
  return this->peek().type == type;
}

[[nodiscard]] bool Parser::is_at_end() {
  return this->peek().type == TokenType::TOKEN_EOF_;
}

Token Parser::consume(TokenType type, std::string_view message) {
  if (this->check(type))
    return std::move(this->advance());
  throw parse_error(this->peek(), std::move(message));
}

Token Parser::consume(std::initializer_list<TokenType>&& types, std::string_view message) {
  for(auto& elem: types)
    if(this->check(elem))
      return std::move(this->advance());
  if(types.size() == 0)
    return std::move(this->advance());
  throw parse_error(this->peek(), std::move(message));
}

Token Parser::advance() {
  if (!this->is_at_end())
    ++this->current;
  return this->previous();
}

[[nodiscard]] Token Parser::peek() {
  return this->tokens.at(this->current);
}

[[nodiscard]] Token Parser::previous() {
  return this->tokens.at(this->current - 1);
}

Parser::ParseError Parser::parse_error(const Token &token, std::string_view message) {
  error(token, message);
  return ParseError("");
}

void Parser::synchronize() {
  this->advance();
  while (!this->is_at_end()) {
    if (this->previous().type == TokenType::TOKEN_SEMICOLON)
      return;
    switch (this->peek().type) {
    case TokenType::TOKEN_CLASS:
    case TokenType::TOKEN_FUN:
    case TokenType::TOKEN_VAR:
    case TokenType::TOKEN_FOR:
    case TokenType::TOKEN_IF:
    case TokenType::TOKEN_WHILE:
    case TokenType::TOKEN_RETURN:
      return;
    }
    this->advance();
  }
}
}// namespace fescript