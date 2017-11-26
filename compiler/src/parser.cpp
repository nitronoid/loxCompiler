#include "parser.h"
#include<iostream>

std::vector<std::unique_ptr<Stmt>> Parser::parse()
{
  std::vector<std::unique_ptr<Stmt>> statements;
  while(m_current < m_tokens.size() && m_tokens[m_current].type() != TType::END)
  {
    auto dec = declaration();
    if(m_hasError) sync();
    else statements.emplace_back(dec);
  }
  return statements;
}

bool Parser::match(std::unordered_set<TType> _types) const
{
  return m_current < m_tokens.size() && _types.count(m_tokens[m_current].type());
}

Stmt* Parser::declaration()
{
  if(match({TType::VAR}))
  {
    ++m_current;
    return varDeclaration();
  }
  return statement();
}

Stmt* Parser::statement()
{
  if(match({TType::PRINT}))
  {
    ++m_current;
    return printStatement();
  }
  if(match({TType::LEFT_BRACE}))
  {
    ++m_current;
    return new Block(block());
  }
  return expressionStatement();
}

Stmt* Parser::expressionStatement()
{
  // NOT expression statement
  Expr* expr = expression();
  consume(TType::SEMICOLON, "Expected ';' after expression.");
  return new Expression(expr);
}

Stmt* Parser::printStatement()
{
  // NOT expression statement
  Expr* val = expression();
  consume(TType::SEMICOLON, "Expected ';' after value.");
  return new Print(val);
}

Stmt* Parser::varDeclaration()
{
  Token name = m_tokens[m_current];
  consume(TType::IDENTIFIER, "Expected identifier.");
  Expr* init = nullptr;
  if(match({TType::EQUAL}))
  {
    ++m_current;
    init = expression();
  }
  consume(TType::SEMICOLON, "Expected ';'.");
  return new Var(name, init);
}

std::vector<std::unique_ptr<Stmt>> Parser::block()
{
  std::vector<std::unique_ptr<Stmt>> statements;

  while (!match({TType::RIGHT_BRACE}) && m_tokens[m_current].type() != TType::END)
  {
    statements.emplace_back(declaration());
  }

  consume(TType::RIGHT_BRACE, "Expected '}' to close block.");

  return statements;
}

Expr* Parser::expression()
{
  return assignment();
}

Expr* Parser::assignment()
{
  Expr* expr = equality();
  if(match({TType::EQUAL}))
  {
    Token equals = m_tokens[m_current];
    ++m_current;
    Expr* value = assignment();
    if(auto var = dynamic_cast<Variable*>(expr))
    {
      return new Assign(var->m_name, value);
    }
    errorAt(equals, "Invalid assignment.");
  }
  return expr;
}

Expr* Parser::equality()
{
  Expr* expr = comparison();
  while(match({TType::NOT_EQUAL, TType::EQUAL_EQUAL}))
  {
    Token op = m_tokens[m_current];
    ++m_current;
    expr = new Binary(expr, op, comparison());
  }
  return expr;
}

Expr* Parser::comparison()
{
  Expr* expr = addition();
  while(match({TType::GREATER, TType::GREATER_EQUAL, TType::LESS, TType::LESS_EQUAL}))
  {
    Token op = m_tokens[m_current];
    ++m_current;
    expr = new Binary(expr, op, addition());
  }
  return expr;
}

Expr* Parser::addition()
{
  Expr* expr = multiplication();
  while(match({TType::MINUS, TType::PLUS}))
  {
    Token op = m_tokens[m_current];
    ++m_current;
    expr = new Binary(expr, op, multiplication());
  }
  return expr;
}

Expr* Parser::multiplication()
{
  Expr* expr = unary();
  while(match({TType::SLASH, TType::STAR}))
  {
    Token op = m_tokens[m_current];
    ++m_current;
    expr = new Binary(expr, op, unary());
  }
  return expr;
}

Expr* Parser::unary()
{
  if(match({TType::NOT, TType::MINUS}))
  {
    Token op = m_tokens[m_current];
    ++m_current;
    return new Unary(op, unary());
  }
  return primary();
}

Expr* Parser::primary()
{
  const auto& tok = m_tokens[m_current];
  ++m_current;
  switch(tok.type())
  {
    case TType::IDENTIFIER: return new Variable(tok);
    case TType::FALSE: return new Literal(new Bool(false));
    case TType::TRUE: return new Literal(new Bool(true));
    case TType::NIL: return new Literal(nullptr);
    case TType::NUMBER: return new Literal(new Number(std::stof(tok.lexeme())));
    case TType::STRING: return new Literal(new String(tok.lexeme()));
    case TType::LEFT_PAREN:
    {
      Expr* expr = expression();
      consume(TType::RIGHT_PAREN, "Expected ')' after expression.");
      return new Grouping(expr);
    }
    default :
    {
      --m_current;
      errorAt(tok, "Expected expression.");
      return nullptr;
    }
  }
}

void Parser::errorAt(const Token &_errTok, const std::string &_msg)
{
  m_hasError = true;
  m_panic = true;
  m_errorReporter.error(_errTok, _msg);
}

void Parser::sync()
{
  ++m_current;
  m_panic = false;
  while(!match({
               TType::END,
               TType::CLASS,
               TType::FUN,
               TType::VAR,
               TType::FOR,
               TType::IF,
               TType::WHILE,
               TType::PRINT,
               TType::RETURN
  }) && (m_current < m_tokens.size()))
  {
    if(m_tokens[m_current - 1].type() == TType::SEMICOLON) break;
    ++m_current;
  }
}

void Parser::consume(const TType &_type, const std::string &_msg)
{
  if(m_tokens[m_current].type() != _type) errorAt(m_tokens[m_current], _msg);
  else ++m_current;
}


