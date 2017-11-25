#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"
#include "errorreporter.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Lexer
{
public:
  using TType = TokenType;
  Lexer(ErrorReporter &_errorReporter) :
    m_errorReporter(_errorReporter)
  {}
  std::vector<Token> lex(const std::string &_input);

private:

  bool isAtEnd();
  void addToken(const TType &_type, const std::string &_lexeme);
  void addToken(const TType &_type);
  char peek();
  char peekNext(const int _ammount);
  char advance();
  bool match(const char _c);
  void scanString();
  void scanNumber();
  void scanMultiLineComment();
  void scanIdentifierOrKeyword();
  void scanToken();


  std::vector<Token> m_tokens;
  std::unordered_map<std::string, TType> m_keywords
  {
    {"and",   TType::AND},
    {"class", TType::CLASS},
    {"else",  TType::ELSE},
    {"false", TType::FALSE},
    {"for",   TType::FOR},
    {"fun",   TType::FUN},
    {"if",    TType::IF},
    {"nil",   TType::NIL},
    {"or",    TType::OR},
    {"print", TType::PRINT},
    {"return",TType::RETURN},
    {"super" ,TType::SUPER},
    {"this",  TType::THIS},
    {"true",  TType::TRUE},
    {"var",   TType::VAR},
    {"while", TType::WHILE},
    // Sentinel to mark end of the array.
    {"",      TType::END}
  };
  std::string m_input;
  int  m_start     = 0;
  int  m_current   = 0;
  int  m_line      = 1;
  ErrorReporter& m_errorReporter;
};

#endif
