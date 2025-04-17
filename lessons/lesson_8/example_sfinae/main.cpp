#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

template <class T, T V>
struct integral_constant {
  static constexpr T value = V;
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

// MARK: detail
namespace detail {

template <class T>
T declval();

template <class T>
struct is_sort_fun : public false_type {};

template <class T>
struct is_sort_fun<void (T::*)()> : public true_type {};

template <class T>
is_sort_fun<decltype(&T::sort)> test_have_sort(T);
false_type test_have_sort(...);

template <class T>
struct __have_sort : public same<decltype(test_have_sort(declval<T>()))> {};

template <class T>
struct is_range_fun : public false_type {};

template <class T>
struct is_range_fun<typename T::iterator (T::*)()> : public true_type {};

template <bool V1, bool V2>
struct __and : public false_type {};

template <>
struct __and<true, true> : public true_type {};

template <typename T>
__and<is_range_fun<decltype(&T::begin)>::value,
      is_range_fun<decltype(&T::end)>::value>
    test_have_range(T);

false_type test_have_range(...);

template <class T>
struct __have_range : public same<decltype(test_have_range(declval<T>()))> {};

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
  using iterator = int*;

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

template <class T>
void f() = delete;

int main() {
  A a;
  fast_sort(a);

  B b;
  fast_sort(b);

  C c;
  fast_sort(c);

  // std::list l{1, 2, 3, 4};
  // std::vector v{4.6, 7.8, 8.0};

  // auto tmp = static_cast<void (std::list<int>::*)()>(std::list<int>::sort);
  // std::cout << std::boolalpha
  //           << detail::is_sort_fun<decltype(&std::list<int>::sort)>::value
  //           << std::endl;

  // fast_sort(l);
  // fast_sort(v);
}