#ifndef STATEMENT_H
#define STATEMENT_H

#include "expression.h"

class StmtVisitor;

class Stmt
{
public:
  virtual void accept(const StmtVisitor &) const = 0;
};

class Print : public Stmt
{
public:
  Print(Expr *const _expression) :
      m_expression(_expression)
  {}

  virtual void accept(const StmtVisitor &_visitor) const override;

  const std::unique_ptr<Expr> m_expression;
};

class Expression : public Stmt
{
public:
  Expression(Expr *const _expression) :
      m_expression(_expression)
  {}

  virtual void accept(const StmtVisitor &_visitor) const override;

  const std::unique_ptr<Expr> m_expression;
};

class Var : public Stmt
{
public:
  Var(const Token &_name, Expr *const _initializer) :
      m_name(_name),
      m_initializer(_initializer)
  {}

  virtual void accept(const StmtVisitor &_visitor) const override;

  const Token m_name;
  const std::unique_ptr<Expr> m_initializer;
};

class Block : public Stmt
{
public:
  Block(std::vector<std::unique_ptr<Stmt>> &&_statements) :
    m_statements(std::move(_statements))
  {}

  virtual void accept(const StmtVisitor &_visitor) const override;

  const std::vector<std::unique_ptr<Stmt>> m_statements;
};

#endif // STATEMENT_H
