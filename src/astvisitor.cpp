#include "astvisitor.h"

std::string ASTVisitor::print(const Expr& _expr)
{
   _expr.accept(*this);
   return m_build;
}

void ASTVisitor::parenthesize(const std::string &_name,
    std::initializer_list<std::reference_wrapper<const std::unique_ptr<Expr> > > &&_list
    ) const
{
  m_build += "(" + _name;
  for(const auto e : _list )
  {
    m_build += " ";
    e.get()->accept(*this);
  }
  m_build += ")";
}

void ASTVisitor::visit(const Assign   &_expr) const
{

}

void ASTVisitor::visit(const Binary   &_expr) const
{
   parenthesize(_expr.m_operator.lexeme(), {_expr.m_left, _expr.m_right});
}

void ASTVisitor::visit(const Call     &_expr) const
{

}

void ASTVisitor::visit(const Get      &_expr) const
{

}

void ASTVisitor::visit(const Grouping &_expr) const
{
   parenthesize("group", {_expr.m_expression});
}

void ASTVisitor::visit(const Literal  &_expr) const
{
  if(_expr.m_literal == nullptr) m_build += "nil";
   _expr.m_literal->accept(*this);
}

void ASTVisitor::visit(const Number &_expr) const
{
   m_build += std::to_string(_expr.m_val);
}

void ASTVisitor::visit(const String &_expr) const
{
   m_build +=  _expr.m_val;
}

void ASTVisitor::visit(const Bool &_expr) const
{
   m_build +=  std::to_string(_expr.m_val);
}

void ASTVisitor::visit(const Logical  &_expr) const
{

}

void ASTVisitor::visit(const Set      &_expr) const
{

}

void ASTVisitor::visit(const Super    &_expr) const
{

}

void ASTVisitor::visit(const This     &_expr) const
{

}

void ASTVisitor::visit(const Unary    &_expr) const
{
   parenthesize(_expr.m_operator.lexeme(),{_expr.m_right});
}

void ASTVisitor::visit(const Variable &_expr) const
{

}
