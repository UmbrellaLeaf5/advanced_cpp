#include <algorithm>
#include <iomanip>
#include <iostream>

#include "utils.hpp"

struct HaveSort {
  char c;
};

struct HaveRange {
  char c;
  HaveSort cl;
};

struct HaveNothing {
  char c;
  HaveRange cl;
};

// static_assert(sizeof(yes) != sizeof(no), "Выберите другие типы");

template <typename T>
HaveSort TestSort(decltype(&T::Sort), decltype(&T::Sort));
template <typename T>
HaveRange TestSort(decltype(&T::begin), decltype(&T::end));
template <typename T>
HaveNothing TestSort(...);

template <typename T, size_t s>
struct FastSortHelper;

template <typename T>
struct FastSortHelper<T, sizeof(HaveSort)> {
  static void FastSort(T& x) {
    IC();
    x.Sort();
  }
};

template <typename T>
struct FastSortHelper<T, sizeof(HaveRange)> {
  static void FastSort(T& x) {
    IC();
    std::sort(x.begin(), x.end());
  }
};

template <typename T>
void FastSort(T& x) {
  FastSortHelper<T, sizeof(TestSort<T>(NULL, NULL))>::FastSort(x);
}

class A {
 public:
  void Sort() {};
};

class B {
 public:
  void f();

  float begin() { return 0.0; }
  int end() { return 0; }
};

class C {
 public:
  void f();

  int* begin() { return a; }
  int* end() { return a + 10; }

  int a[10];
};

int main() {
  A a;
  FastSort(a);

  B b;
  // FastSort(b);
  // ERROR: no matching function for call to 'sort(float, int)'

  C c;
  FastSort(c);
}