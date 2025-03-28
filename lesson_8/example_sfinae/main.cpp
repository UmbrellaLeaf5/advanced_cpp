#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

template <class T, T v>
struct integral_constant {
  static constexpr T value = v;
};

struct true_type : public integral_constant<bool, true> {};

struct false_type : public integral_constant<bool, false> {};

template <class T>
struct same {
  using type = T;
};

template <bool V, class T = void>
struct enable_if;

template <class T>
struct enable_if<true, T> : public same<T> {};

template <bool V, class T = void>
using enable_if_t = typename enable_if<V, T>::type;

namespace detail {

template <typename T>
true_type test_have_sort(decltype(&T::sort));
template <typename T>
false_type test_have_sort(...);

// в C++11 нельзя было наследоваться от decltype
template <class T>
struct __have_sort : public same<decltype(test_have_sort<T>(nullptr))> {};

template <typename T>
true_type test_have_range(decltype(&T::begin), decltype(&T::end));
template <typename T>
false_type test_have_range(...);

template <class T>
struct __have_range
    : public same<decltype(test_have_range<T>(nullptr, nullptr))> {};

};  // namespace detail

template <class T>
using have_sort = typename detail::__have_sort<T>::type;

template <class T>
constexpr bool have_sort_v = have_sort<T>::value;

template <class T>
using have_range = typename detail::__have_range<T>::type;

template <class T>
constexpr bool have_range_v = have_range<T>::value;

template <class T>
enable_if_t<have_sort_v<T>> fast_sort(T& x) {
  std::cout << "x.sort();" << std::endl;
  x.sort();
}

template <class T>
enable_if_t<have_range_v<T> && !have_sort_v<T>> fast_sort(T& x) {
  std::cout << "std::sort(x.begin(), x.end());" << std::endl;
  std::sort(x.begin(), x.end());
}

class A {
 public:
  void sort() {};
};

class B {
 public:
  void f();
  int* begin() { return a; }
  int* end() { return a + 10; }
  int a[10];
};

class C {
 public:
  void sort() {};
  int* begin() { return a; }
  int* end() { return a + 10; }
  int a[10];
};

int main() {
  A a;
  fast_sort(a);

  B b;
  fast_sort(b);

  C c;
  fast_sort(c);

  // std::list<int> l{1, 2, 3, 4};
  // std::vector<float> v{4.6, 7.8, 8.0};

  // fast_sort(l);
  // fast_sort(v);
}