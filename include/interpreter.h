#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "exprvisitor.h"
#include "stmtvisitor.h"
#include "value.h"
#include "environment.h"
#include "errorreporter.h"


class Interpreter : public ExprVisitor, public StmtVisitor
{
public:
  Interpreter(ErrorReporter &io_errorReporter) :
    m_errorReporter(io_errorReporter)
  {}
  void interpret(const std::vector<std::unique_ptr<Stmt>> &_statements) const;

private:
  using Value = detail::Value;
  Value evaluate(const Expr &_expr) const;
  virtual void visit(const Assign     &_expr) const override;
  virtual void visit(const Binary     &_expr) const override;
  virtual void visit(const Call       &_expr) const override;
  virtual void visit(const Get        &_expr) const override;
  virtual void visit(const Grouping   &_expr) const override;
  virtual void visit(const Literal    &_expr) const override;
  virtual void visit(const Number     &_expr) const override;
  virtual void visit(const String     &_expr) const override;
  virtual void visit(const Bool       &_expr) const override;
  virtual void visit(const Logical    &_expr) const override;
  virtual void visit(const Set        &_expr) const override;
  virtual void visit(const Super      &_expr) const override;
  virtual void visit(const This       &_expr) const override;
  virtual void visit(const Unary      &_expr) const override;
  virtual void visit(const Variable   &_expr) const override;

  virtual void visit(const Print      &_stmt) const override;
  virtual void visit(const Expression &_stmt) const override;
  virtual void visit(const Var        &_stmt) const override;
  virtual void visit(const Block      &_stmt) const override;

private:

  mutable Environment m_environment;

  mutable Value m_value;

  mutable bool m_hasError = false;

  ErrorReporter& m_errorReporter;

  std::string val_to_string(const Value &_val) const;

  void execute(const Stmt &_stmt) const;

  void executeBlock(const std::vector<std::unique_ptr<Stmt>> &_statements, const Environment &_environment) const;

  bool isNumber(const Value &_val) const;

  bool isString(const Value &_val) const;

  bool isTruthful() const;

  void errorAt(const Token &_errTok, const std::string &_msg) const;
};

#endif // INTERPRETER_H
