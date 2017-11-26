#ifndef COMPILEERROR_H
#define COMPILEERROR_H

#include <string>
#include "token.h"

class ErrorReporter
{
 public:
  inline bool hadError() { return m_hadError; }
  void report(const int _line, const std::string &_where, const std::string &_message);
  void error(const int _line, const std::string &_message);
  void error(const Token &_token, const std::string &_message);
  inline void reset() { m_hadError = false; }
 private:
  bool m_hadError = false;
};

#endif // COMPILEERROR_H
