#include "lexer.h"
#include <cctype>
#include <algorithm>
#include <iostream>

bool safe_isdigit(char ch)
{
  return std::isdigit(static_cast<unsigned char>(ch));
}

bool safe_isalpha(char ch)
{
  return std::isalpha(static_cast<unsigned char>(ch));
}

bool safe_isalnum(char ch)
{
  return std::isalnum(static_cast<unsigned char>(ch));
}

bool str_isalnum(const std::string &_str)
{
  return std::find_if(std::begin(_str), std::end(_str), [](const char _c) { return !safe_isalnum(_c); }) == std::end(_str);
}

bool str_isnum(const std::string &_str)
{
  return std::find_if(std::begin(_str), std::end(_str), [](const char _c) { return !safe_isdigit(_c); }) == std::end(_str);
}


std::vector<Token> Lexer::lex(const std::string &_input)
{
  m_current = 0;
  m_input = _input;
  while (!isAtEnd())
  {
    m_start = m_current;
    scanToken();
  }
  m_tokens.push_back(Token(TType::END, "", m_line));
  return m_tokens;
}



bool Lexer::isAtEnd()
{
  return m_current >= static_cast<int>(m_input.size());
}

void Lexer::addToken(const TType &_type, const std::string &_lexeme)
{
  m_tokens.push_back(Token(_type, _lexeme, m_line));
}

void Lexer::addToken(const TType &_type)
{
  m_tokens.push_back(Token(_type, m_input.substr(m_start, m_current - m_start), m_line));
}

char Lexer::peek()
{
  if (isAtEnd()) return '\0';
  return m_input[m_current];
}

char Lexer::peekNext(const int _ammount)
{
  if (m_current + _ammount >= static_cast<int>(m_input.size())) return '\0';
  return m_input[m_current + _ammount];
}

char Lexer::advance()
{
  ++m_current;
  return m_input[m_current - 1];
}

bool Lexer::match(const char _c)
{
  if (!isAtEnd() && peek() == _c)
  {
    advance();
    return true;
  }
  return false;
}

void Lexer::scanString()
{
  while (peek() != '"' && !isAtEnd())
  {
    if (peek() == '\n') ++m_line;
    advance();
  }
  if (isAtEnd())
  {
    m_errorReporter.error(m_line, "Expected closing \" for string literal.");
    return;
  }
  ++m_start;
  addToken(TType::STRING);
  advance();
}

void Lexer::scanNumber()
{
  while (safe_isdigit(peek())) advance();
  if (peek() == '.' && safe_isdigit(peekNext(1)))
  {
    advance();
    while (safe_isdigit(peek())) advance();
  }
  addToken(TType::NUMBER);
}

void Lexer::scanIdentifierOrKeyword()
{
  while (safe_isalnum(peek()) || peek() == '_') advance();
  std::string lexeme = m_input.substr(m_start, m_current - m_start);
  if (m_keywords.count(lexeme)) addToken(m_keywords[lexeme]);
  else addToken(TType::IDENTIFIER);
}

void Lexer::scanToken()
{
  char c = advance();
  switch (c)
  {
    case '(': addToken(TType::LEFT_PAREN); break;
    case ')': addToken(TType::RIGHT_PAREN); break;
    case '{': addToken(TType::LEFT_BRACE); break;
    case '}': addToken(TType::RIGHT_BRACE); break;
    case ',': addToken(TType::COMMA); break;
    case '.': addToken(TType::DOT); break;
    case '-': addToken(TType::MINUS); break;
    case '+': addToken(TType::PLUS); break;
    case ';': addToken(TType::SEMICOLON); break;
    case '*': addToken(TType::STAR); break;
    case '!': addToken(match('=') ? TType::NOT_EQUAL     : TType::NOT);     break;
    case '=': addToken(match('=') ? TType::EQUAL_EQUAL   : TType::EQUAL);   break;
    case '<': addToken(match('=') ? TType::LESS_EQUAL    : TType::LESS);    break;
    case '>': addToken(match('=') ? TType::GREATER_EQUAL : TType::GREATER); break;
    case '/':
    {
      if (match('/'))
      {
        // line comment, eat everything until end of the line
        while (!isAtEnd() && peek() != '\n') advance();
      }
      else addToken(TType::SLASH);
      break;
    }
    // Ignore whitespace
    case ' ': case '\r': case '\t': break;
    case '\n': m_line++; break;
    // Start of a string
    case '"': scanString(); break;

    default:
      if (safe_isdigit(c)) scanNumber();
      else if (safe_isalpha(c) || c == '_') scanIdentifierOrKeyword();
      else m_errorReporter.error(m_line, "Unexpected character.");
  }
}


