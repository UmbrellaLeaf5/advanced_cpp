// #include <algorithm>
#include <iomanip>
#include <iostream>
// #include <list>
#include <string>
#include <type_traits>
#include <vector>

template <typename T, typename U, typename = void>
struct is_equality_comparable : std::false_type {};

template <typename T, typename U>
struct is_equality_comparable<
    T, U, std::void_t<decltype(std::declval<T>() == std::declval<U>())>>
    : std::true_type {};

template <typename T, typename U>
bool check_eq(T&& lhs, U&& rhs)
  requires requires(T t, U u) { 5 == 10; }
{
  return (lhs == rhs);
}

template <class It>
struct is_input_iterator
    : std::is_base_of<std::input_iterator_tag,
                      typename std::iterator_traits<It>::iterator_category> {};

template <class It>
struct is_random_iterator
    : std::is_base_of<std::random_access_iterator_tag,
                      typename std::iterator_traits<It>::iterator_category> {};

template <class It>
int my_distance(It first, It last)
  requires(is_input_iterator<It>::value && !is_random_iterator<It>::value)
{
  return 0;
}

template <class It>
int my_distance(It first, It last)
  requires is_random_iterator<It>::value
{
  return 5;
}

template <class From, class To>
concept convertible_to = requires(From (&f)()) { static_cast<To>(f()); };

template <class T, class U>
concept Weakly = requires(T t, U u) {
  { t == u } -> convertible_to<bool>;
};

template <class From, class To>
To convert(From v)
  requires Weakly<From, To>
{
  return To();
}

int main() {
  std::string s("35");
  int a = 35;
  float f = 35;

  // check_eq(f, a);
  convert<int, float>(5);
  std::vector<int> vec{4, 5, 6};

  // std::cout << my_distance(vec.begin(), vec.end());

  return 0;
}
