#ifndef STMTVISITOR_H
#define STMTVISITOR_H

#include "statement.h"

class StmtVisitor
{
public:
  virtual void visit(const Print      &_expr) const = 0;
  virtual void visit(const Expression &_expr) const = 0;
  virtual void visit(const Var        &_expr) const = 0;
  virtual void visit(const Block      &_stmt) const = 0;
};

#endif // STMTVISITOR_H
