#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <variant>

namespace detail 
{
  using Value = std::variant<double, std::string, bool, std::nullptr_t>;

}


#endif // VALUE_H
