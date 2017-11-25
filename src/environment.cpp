#include "environment.h"

void Environment::define(const Token &_name, const Value &_value)
{
  m_values[_name.lexeme()] = _value;
}

bool Environment::assign(const Token &_name, const Value &_value)
{
  if (m_values.count(_name.lexeme()))
  {
    define(_name, _value);
    return true;
  }

  if (m_enclosing)
  {
    m_enclosing->define(_name, _value);
    return true;
  }

  return false;
}

Environment::Value Environment::retrieve(const Token &_name)
{
  if(m_values.count(_name.lexeme()))
    return m_values[_name.lexeme()];

  if(m_enclosing) return m_enclosing->retrieve(_name);

  return nullptr;
}
