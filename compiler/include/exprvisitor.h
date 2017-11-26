#ifndef EXPRVISITOR_H
#define EXPRVISITOR_H

#include "expression.h"

class ExprVisitor
{
public:
  virtual void visit(const Assign   &_expr) const = 0;
  virtual void visit(const Binary   &_expr) const = 0;
  virtual void visit(const Call     &_expr) const = 0;
  virtual void visit(const Get      &_expr) const = 0;
  virtual void visit(const Grouping &_expr) const = 0;
  virtual void visit(const Literal  &_expr) const = 0;
  virtual void visit(const Number   &_expr) const = 0;
  virtual void visit(const String   &_expr) const = 0;
  virtual void visit(const Bool     &_expr) const = 0;
  virtual void visit(const Logical  &_expr) const = 0;
  virtual void visit(const Set      &_expr) const = 0;
  virtual void visit(const Super    &_expr) const = 0;
  virtual void visit(const This     &_expr) const = 0;
  virtual void visit(const Unary    &_expr) const = 0;
  virtual void visit(const Variable &_expr) const = 0;
};

#endif // EXPRVISITOR_H
