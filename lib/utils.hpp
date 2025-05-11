#pragma once

#include <cxxabi.h>

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "icecream.hpp"

#ifndef IC_TYPE
#define IC_TYPE(x) IC(x, detail::TypeName<decltype(x)>())
#endif

#ifndef ICDouble
#define ICDouble(value)                                   \
  {                                                       \
    std::stringstream ss;                                 \
    ss << std::fixed << std::setprecision(19) << (value); \
    IC(value, ss.str());                                  \
  }
#endif

namespace detail {

/**
 * @brief Преобразует имя типа из "искажённого" в удобочитаемый вид.
 *
 * @details Эта функция использует `abi::__cxa_demangle` для преобразования
 * имени типа, полученного из `typeid(T).name()`. "Искажённое" имя (например,
 * `NSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE`)
 * преобразуется в более понятную форму (например, `std::string`).
 *
 * @tparam T: тип, имя которого нужно преобразовать.
 * @return `std::string`: строка, содержащая удобочитаемое имя типа,
 * или "искажённое" имя, если преобразование не удалось.
 */
template <typename T>
std::string TypeName() {
  int status = -1;
  std::unique_ptr<char, void (*)(void*)> res{
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free};
  return (status == 0) ? res.get() : typeid(T).name();
}

}  // namespace detail

/**
 * @brief Выводит подробную информацию о переменной, включая её значение,
 * преобразованное имя типа (с использованием std::decay), "искажённое"
 * имя типа (с использованием typeid) и результат работы макроса IC_TYPE.
 *
 * @details Эта функция предоставляет детальный обзор свойств переменной,
 * полезный для отладки и понимания вывода типов в C++. Она выводит значение,
 * преобразованное имя типа с использованием `detail::TypeName` для
 * "разложенного" типа (decayed type), "искажённое" имя типа с использованием
 * `typeid`, и результат работы макроса `IC_TYPE`.
 *
 * @tparam T: тип переменной.
 * @param value: константная ссылка на переменную, которую нужно исследовать.
 */
template <typename T>
void PrintVerboseVarInfo(const T& value) {
  std::cout << "--------------------------------------------------"
            << std::endl;
  std::cout << "Variable Information:" << std::endl;
  std::cout << "\tValue: " << value << std::endl;

  using ActualType = typename std::decay<decltype(value)>::type;

  std::cout << "\tType (std::decay): " << detail::TypeName<ActualType>()
            << std::endl;
  std::cout << "\tType (typeid): " << typeid(value).name() << std::endl;

  IC_TYPE(value);
  std::cout << "--------------------------------------------------"
            << std::endl;
}
