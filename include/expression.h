#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"
#include <memory>
#include <vector>

class ExprVisitor;

class Expr
{
public:
  virtual void accept(const ExprVisitor &) const = 0;
};

class Assign : public Expr
{
public:
  Assign(const Token &_name, Expr *const _value) :
    m_name(_name),
    m_value(_value)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const Token m_name;
  const std::unique_ptr<Expr> m_value;
};

class Binary : public Expr
{
public:
  Binary(Expr *const _left, const Token &_operator, Expr *const _right) :
    m_left(_left),
    m_operator(_operator),
    m_right(_right)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const std::unique_ptr<Expr> m_left;
  const Token m_operator;
  const std::unique_ptr<Expr> m_right;
};

class Call : public Expr
{
public:
  Call(Expr *const _callee, const Token &_paren, std::vector<std::unique_ptr<Expr>> &&_args) :
    m_callee(_callee),
    m_paren(_paren),
    m_args(std::move(_args))
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const std::unique_ptr<Expr> m_callee;
  const Token m_paren;
  const std::vector<std::unique_ptr<Expr>> m_args;
};

class Get : public Expr
{
public:
  Get(const Token &_name, Expr *const _object) :
    m_name(_name),
    m_object(_object)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const Token m_name;
  const std::unique_ptr<Expr> m_object;
};

class Grouping : public Expr
{
public:
  Grouping(Expr *const _expression) :
    m_expression(_expression)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const std::unique_ptr<Expr> m_expression;
};

class Literal : public Expr
{
public:
  Literal(Expr *const _literal) :
    m_literal(_literal)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;


  const std::unique_ptr<Expr> m_literal;
};

class Number : public Expr
{
public:
  Number(const float &_val) :
    m_val(_val)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;
  const float m_val;
};

class String : public Expr
{
public:
  String(const std::string &_val) :
    m_val(_val)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;
  const std::string m_val;
};

class Bool : public Expr
{
public:
  Bool(const bool &_val) :
    m_val(_val)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;
  const bool m_val;
};

class Logical : public Expr
{
public:
  Logical(Expr *const _left, const Token &_operator, Expr *const _right) :
    m_left(_left),
    m_operator(_operator),
    m_right(_right)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const std::unique_ptr<Expr> m_left;
  const Token m_operator;
  const std::unique_ptr<Expr> m_right;
};

class Set : public Expr
{
public:
  Set(Expr *const _object, const Token &_name, Expr *const _value) :
    m_object(_object),
    m_name(_name),
    m_value(_value)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const std::unique_ptr<Expr> m_object;
  const Token m_name;
  const std::unique_ptr<Expr> m_value;
};

class Super : public Expr
{
public:
  Super(const Token &_keyword, const Token &_method) :
    m_keyword(_keyword),
    m_method(_method)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const Token m_keyword;
  const Token m_method;
};

class This : public Expr
{
public:
  This(const Token &_keyword) :
    m_keyword(_keyword)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const Token m_keyword;
};

class Unary : public Expr
{
public:
  Unary(const Token &_operator, Expr *const _right) :
    m_operator(_operator),
    m_right(_right)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const Token m_operator;
  const std::unique_ptr<Expr> m_right;
};

class Variable : public Expr
{
public:
  Variable(const Token &_name) :
    m_name(_name)
  {}

  virtual void accept(const ExprVisitor &_visitor) const override;

  const Token m_name;
};


#endif // EXPRESSION_H
