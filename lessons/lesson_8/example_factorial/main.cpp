#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

// До C++11
struct const_value_struct {
  enum { value = 43 };
};

// После C++11
struct const_value_struct_11 {
  static constexpr int value = 42;
};

template <class T, T v>
struct integral_constant {
  static constexpr T value = v;
};

// как использовать integral_constant
template <unsigned long N>
struct factorial
    : public integral_constant<unsigned long, factorial<N - 1>::value * N> {};

template <>
struct factorial<0> : public integral_constant<unsigned long, 1> {};

template <unsigned long N>
constexpr unsigned long factorial_v = factorial<N>::value;

int main() { std::cout << factorial_v<5> << "\n"; }
