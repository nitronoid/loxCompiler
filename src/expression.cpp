#include "exprvisitor.h"
#include "expression.h"

void Assign::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Binary::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Call::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Get::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Grouping::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Literal::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Number::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Bool::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void String::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Logical::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Set::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Super::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void This::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Unary::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}

void Variable::accept(const ExprVisitor &_visitor) const
{
  return _visitor.visit(*this);
}
