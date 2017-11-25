#include "interpreter.h"
#include "errorreporter.h"
#include "iostream"

using TType = TokenType;

void Interpreter::interpret(const std::vector<std::unique_ptr<Stmt>> &_statements) const
{
  for(auto & statement : _statements)
  {
    execute(*statement);
  }
}

void Interpreter::execute(const Stmt &_stmt) const
{
  _stmt.accept(*this);
}

void Interpreter::executeBlock(const std::vector<std::unique_ptr<Stmt>> &_statements, const Environment &_environment) const
{
  Environment temp = m_environment;
  m_environment = _environment;
  for (const auto& statement : _statements)
  {
    execute(*statement);
  }
  m_environment = temp;
}

std::string Interpreter::val_to_string(const Value &_val) const
{
  std::string ret;
  if(isNumber(_val)) ret = std::to_string(std::get<double>(_val));
  else if (isString(_val)) ret = std::get<std::string>(_val);
  else if (auto ptr = std::get_if<bool>(&_val)) {ret = *ptr? "true" : "false";}
  else ret = "nil";
  return ret;
}

void Interpreter::errorAt(const Token &_errTok, const std::string &_msg) const
{
  m_hasError = true;
  //m_panic = true;
  m_errorReporter.error(_errTok, _msg);
}

Interpreter::Value Interpreter::evaluate(const Expr &_expr) const
{
  _expr.accept(*this);
  return m_value;
}

bool Interpreter::isNumber(const Value &_val) const
{
  return static_cast<bool>(std::get_if<double>(&_val));
}

bool Interpreter::isString(const Value &_val) const
{
  return static_cast<bool>(std::get_if<std::string>(&_val));
}

bool Interpreter::isTruthful() const
{
  if (isNumber(m_value) || isString(m_value)) return true;
  else if (auto ptr = std::get_if<bool>(&m_value)) return *ptr;
  else return false;
}

void Interpreter::visit(const Assign   &_expr) const
{
  if (!m_environment.assign(_expr.m_name, evaluate(*_expr.m_value)))
    errorAt(_expr.m_name, "Undefined Variable.");
}

void Interpreter::visit(const Binary   &_expr) const
{

  auto lhs = evaluate(*_expr.m_left);
  auto rhs = evaluate(*_expr.m_right);
  auto numCheck = [&]()
  {
    if (!(isNumber(lhs) && isNumber(rhs)))
    {
      errorAt(_expr.m_operator,"Operands must be a pair of numbers.");
      return false;
    }
    return true;
  };

  switch (_expr.m_operator.type())
  {
    case TType::MINUS:
    {
      if (numCheck()) m_value = std::get<double>(lhs) - std::get<double>(rhs);
      break;
    }
    case TType::STAR:
    {
      if (numCheck()) m_value = std::get<double>(lhs) * std::get<double>(rhs);
      break;
    }
    case TType::SLASH:
    {
      if (numCheck()) m_value = std::get<double>(lhs) / std::get<double>(rhs);
      break;
    }
    case TType::PLUS:
    {
      if (isNumber(lhs) && isNumber(rhs))
        m_value = std::get<double>(lhs) + std::get<double>(rhs);
      else if (isString(lhs) && isString(rhs))
        m_value = std::get<std::string>(lhs) + std::get<std::string>(rhs);
      else errorAt(_expr.m_operator,"Operands must be a pair of strings or numbers.");
      break;
    }
    case TType::GREATER:
    {
      if (numCheck()) m_value = std::get<double>(lhs) > std::get<double>(rhs);
      break;
    }
    case TType::GREATER_EQUAL:
    {
      if (numCheck()) m_value = std::get<double>(lhs) >= std::get<double>(rhs);
      break;
    }
    case TType::LESS:
    {
      if (numCheck()) m_value = std::get<double>(lhs) < std::get<double>(rhs);
      break;
    }
    case TType::LESS_EQUAL:
    {
      if (numCheck()) m_value = std::get<double>(lhs) <= std::get<double>(rhs);
      break;
    }
    case TType::EQUAL_EQUAL:
    {
      m_value = lhs == rhs;
      break;
    }
    case TType::NOT_EQUAL:
    {
      m_value = lhs != rhs;
      break;
    }
    default: break;
  }
}


void Interpreter::visit(const Grouping &_expr) const
{
  m_value = evaluate(*_expr.m_expression);
}

void Interpreter::visit(const Literal  &_expr) const
{
  if(_expr.m_literal == nullptr) m_value = nullptr;
  _expr.m_literal->accept(*this);
}

void Interpreter::visit(const Number &_expr) const
{
  m_value = _expr.m_val;
}

void Interpreter::visit(const String &_expr) const
{
  m_value = _expr.m_val;
}

void Interpreter::visit(const Bool &_expr) const
{
  m_value = _expr.m_val;
}

void Interpreter::visit(const Logical  &_expr) const
{
  //TODO
}

void Interpreter::visit(const Set      &_expr) const
{
  //TODO
}

void Interpreter::visit(const Super    &_expr) const
{
  //TODO
}

void Interpreter::visit(const This     &_expr) const
{
  //TODO
}

void Interpreter::visit(const Call     &_expr) const
{
  //TODO
}

void Interpreter::visit(const Get     &_expr) const
{
  //TODO
}

void Interpreter::visit(const Unary    &_expr) const
{
  evaluate(*_expr.m_right);
  switch (_expr.m_operator.type())
  {
    case TType::MINUS:
    {
      if(isNumber(m_value)) m_value = -std::get<double>(m_value);
      else errorAt(_expr.m_operator, "Operand must be a number.");
      break;
    }
    case TType::NOT: m_value = isTruthful(); break;
    default: m_value = nullptr; break;
  }
}

void Interpreter::visit(const Variable &_expr) const
{
  m_value = m_environment.retrieve(_expr.m_name);
}

void Interpreter::visit(const Print &_stmt) const
{
  std::cout<<val_to_string(evaluate(*_stmt.m_expression))<<'\n';
}

void Interpreter::visit(const Expression &_stmt) const
{
  evaluate(*_stmt.m_expression);
}

void Interpreter::visit(const Var &_stmt) const
{
  Value val = nullptr;
  if (_stmt.m_initializer) val = evaluate(*_stmt.m_initializer);
  m_environment.define(_stmt.m_name, val);
}

void Interpreter::visit(const Block &_stmt) const
{
  executeBlock(_stmt.m_statements, Environment(m_environment));
}





