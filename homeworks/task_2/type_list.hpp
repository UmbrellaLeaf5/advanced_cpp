#pragma once

#include <type_traits>

using std::size_t;
using ssize_t = std::make_signed<size_t>::type;

template <typename... Types>
class TypeList {
 private:
  template <typename... Ts>
  struct TypeList_ {};

  template <size_t Index, typename List>
  struct TypeAt_;

  template <typename Current, typename... Rest>
  struct TypeAt_<0, TypeList_<Current, Rest...>> {
    using type = Current;
  };

  template <size_t Index, typename Current, typename... Rest>
  struct TypeAt_<Index, TypeList_<Current, Rest...>>
      : TypeAt_<Index - 1, TypeList_<Rest...>> {};

  template <typename T>
  static constexpr bool Contains_() {
    return false;
  }

  template <typename T, typename Current, typename... Rest>
  static constexpr bool Contains_() {
    if constexpr (!std::is_same_v<T, Current>) return Contains_<T, Rest...>();

    return true;
  }

  template <typename T>
  static constexpr ssize_t IndexOf_() {
    return -1;
  }

  template <typename T, typename Current, typename... Rest>
  static constexpr ssize_t IndexOf_() {
    constexpr ssize_t next_index = IndexOf_<T, Rest...>();

    if constexpr (!std::is_same_v<T, Current>)
      return next_index == -1 ? next_index : 1 + next_index;

    return 0;
  }

 public:
  static constexpr size_t Size() noexcept { return sizeof...(Types); }

  template <size_t Index>
  using At = typename TypeAt_<Index, TypeList_<Types...>>::type;

  template <typename Type>
  static constexpr bool Contains() noexcept {
    return Contains_<Type, Types...>();
  }

  template <typename Type>
  static constexpr size_t IndexOf() noexcept {
    constexpr ssize_t index_of = IndexOf_<Type, Types...>();

    static_assert(Contains<Type>(),
                  "TypeList::IndexOf: Type not found in TypeList");

    static_assert(index_of != -1, "TypeList::IndexOf: illegal instruction");

    return static_cast<size_t>(index_of);
  }

  template <typename Type>
  using Append = TypeList<Types..., Type>;

  template <typename Type>
  using Prepend = TypeList<Type, Types...>;
};
