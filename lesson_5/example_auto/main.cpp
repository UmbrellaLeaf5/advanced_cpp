#include <functional>

#include "utils.hpp"

int* F(int arg, int (*)(float)) { return &arg; }

float Calc(int a) { return a / 2.0; }

auto Func(int a) {
  if (a < 5) return 0.f;
  // return 0;
  // error: inconsistent deduction for auto return type: 'int' and then 'float'
  else
    return Calc(a);
}

int main() {
  int a = 6;

  const int& ref_a = a;

  auto b = ref_a;
  auto& c = ref_a;

  PrintVerboseVarInfo(b);
  PrintVerboseVarInfo(c);

  // указатель на функцию, внутри которой
  // в качестве аргумента тоже указатель на функцию
  void (*ptr)(int, int (*)(float));

  // возвращает тоже указатель на функцию
  int* (*ptr_2)(int, int (*)(float)) = &F;

  auto ptr_3 = &F;

  return 0;
}
