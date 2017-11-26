#include "errorreporter.h"
#include <iostream>


void ErrorReporter::report(const int _line, const std::string &_where, const std::string &_message)
{
  std::cerr << "[line " << _line << "] Error" << _where << ": " << _message <<'\n';
  m_hadError = true;
}

void ErrorReporter::error(const int _line, const std::string &_message)
{
  report(_line, "", _message);
}

void ErrorReporter::error(const Token &_token, const std::string &_message)
{
  std::string loc;
  if(_token.type() == TokenType::END) loc = "end";
  else loc = _token.lexeme();
  report(_token.line(), " at " + loc, _message);
}
