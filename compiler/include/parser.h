#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "expression.h"
#include "errorreporter.h"
#include "statement.h"
#include <unordered_set>

class Parser
{
public:
  Parser(const std::vector<Token> &_tokens, ErrorReporter &io_errorReporter) :
    m_tokens(_tokens),
    m_errorReporter(io_errorReporter)
  {}

  std::vector<std::unique_ptr<Stmt>> parse();

  inline bool hadError() { return m_hasError; }
private:
  using TType = TokenType;

  void errorAt(const Token &_errTok, const std::string &_msg);

  bool match(std::unordered_set<TokenType> _types) const;

  void sync();

  void consume(const TType &_type, const std::string &_msg);

  // Expression parsing
  Expr* expression();
  Expr* assignment();
  Expr* equality();
  Expr* comparison();
  Expr* addition();
  Expr* multiplication();
  Expr* unary();
  Expr* primary();

  // Statement parsing
  Stmt* statement();
  Stmt* expressionStatement();
  Stmt* printStatement();
  Stmt* declaration();
  Stmt* varDeclaration();
  std::vector<std::unique_ptr<Stmt>> block();

  const std::vector<Token> m_tokens;
  size_t m_current = 0;
  bool m_hasError = false;
  bool m_panic = false;
  ErrorReporter& m_errorReporter;
};

#endif // PARSER_H
