#include <algorithm>
#include <iomanip>
#include <iostream>

#include "utils.hpp"

struct YesStruct {
  char c;
};

struct NoStruct {
  char c;
  YesStruct cl;
};

static_assert(sizeof(YesStruct) != sizeof(NoStruct), "Выберите другие типы");

template <typename T>
YesStruct TestSort(decltype(&T::Sort));
template <typename T>
NoStruct TestSort(...);

template <typename T, size_t S>
struct FastSortHelper;

template <typename T>
struct FastSortHelper<T, sizeof(YesStruct)> {
  static void FastSort(T& x) {
    IC();
    x.Sort();
  }
};

template <typename T>
struct FastSortHelper<T, sizeof(NoStruct)> {
  static void FastSort(T& x) {
    IC();
    std::sort(x.begin(), x.end());
  }
};

template <typename T>
inline void FastSort(T& x) {
  FastSortHelper<T, sizeof(TestSort<T>(nullptr))>::FastSort(x);
}

class A {
 public:
  void Sort() {}
};

class B {
 public:
  void f() {}
};

int main() {
  A a;
  FastSort(a);

  B b;
  // FastSort(b);
}