#ifndef ASTVISITOR_H
#define ASTVISITOR_H

#include "exprvisitor.h"
#include <initializer_list>
#include <functional>

class ASTVisitor : public ExprVisitor
{
public:
  std::string print(const Expr& _expr);
  virtual void visit(const Assign   &_expr) const override;
  virtual void visit(const Binary   &_expr) const override;
  virtual void visit(const Call     &_expr) const override;
  virtual void visit(const Get      &_expr) const override;
  virtual void visit(const Grouping &_expr) const override;
  virtual void visit(const Literal  &_expr) const override;
  virtual void visit(const Number   &_expr) const override;
  virtual void visit(const String   &_expr) const override;
  virtual void visit(const Bool     &_expr) const override;
  virtual void visit(const Logical  &_expr) const override;
  virtual void visit(const Set      &_expr) const override;
  virtual void visit(const Super    &_expr) const override;
  virtual void visit(const This     &_expr) const override;
  virtual void visit(const Unary    &_expr) const override;
  virtual void visit(const Variable &_expr) const override;

private:
  void parenthesize(const std::string &_name,
      std::initializer_list<std::reference_wrapper<const std::unique_ptr<Expr> > > &&_list
      ) const;

  mutable std::string m_build;

};

#endif // ASTVISITOR_H
