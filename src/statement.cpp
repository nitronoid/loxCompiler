#include "statement.h"
#include "stmtvisitor.h"

void Print::accept(const StmtVisitor &_visitor) const
{
  _visitor.visit(*this);
}

void Expression::accept(const StmtVisitor &_visitor) const
{
  _visitor.visit(*this);
}

void Var::accept(const StmtVisitor &_visitor) const
{
  _visitor.visit(*this);
}

void Block::accept(const StmtVisitor &_visitor) const
{
  _visitor.visit(*this);
}
