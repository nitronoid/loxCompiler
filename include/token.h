#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  NOT, NOT_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  ERROR, END
};

class Token
{
public:
  Token(TokenType _type, const std::string &_lexeme, const int _line) :
    m_type(_type),
    m_lexeme(_lexeme),
    m_line(_line)
  {}

  inline std::string info() const
  {
    return std::to_string(static_cast<int>(m_type)) + " " + m_lexeme;
  }

  inline std::string lexeme() const { return m_lexeme; }

  inline TokenType type() const { return m_type; }

  inline int line() const { return m_line; }

  bool operator==(const Token &_rhs) const
  {
    return (m_type == _rhs.type()) &&
           (m_lexeme == _rhs.lexeme()) &&
           (m_line == _rhs.line());
  }

private:
  const TokenType m_type;
  const std::string m_lexeme;
  const int m_line;
};

#endif // TOKEN_H
