#include <iostream>
#include <type_traits>

#include "utils.hpp"

template <typename T>
// подходит по механизму умных ссылок
void Func([[maybe_unused]] T&& var) {
  std::cout << "Template" << std::endl;
}

// void func(int& var) { std::cout << "LValue Ref" << std::endl; }

void Func([[maybe_unused]] int&& var) { std::cout << "Simple" << std::endl; }

extern void Other();

int main() {
  int a = 5;
  const int b = 5;

  Func(5);

  // т.е. void func<int &>(int &var)
  Func(a);
  // т.е. void func<const int &>(const int &var)
  Func(b);

  Func(std::move(a));
  Func(std::move(b));

  std::cout << "Type of std::move(b): " << std::endl;
  PrintVerboseVarInfo(std::move(b));

  Other();

  return 0;
}
