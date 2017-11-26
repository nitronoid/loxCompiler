#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "token.h"
#include <unordered_map>
#include <value.h>

class Environment
{
private:
  using Value = detail::Value;
public:
  Environment() = default;
  Environment(Environment* const _enclosing) :
    m_enclosing(_enclosing)
  {}
  void define(const Token &_name, const Value &_value);
  bool assign(const Token &_name, const Value &_value);
  Value retrieve(const Token &_name);
private:
  Environment* m_enclosing = nullptr;
  std::unordered_map<std::string, Value> m_values;
};

#endif // ENVIRONMENT_H
