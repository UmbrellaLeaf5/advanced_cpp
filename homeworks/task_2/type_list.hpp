#pragma once

#include <type_traits>

using std::size_t;
using ssize_t = std::make_signed<size_t>::type;

template <typename... Types>
class TypeList {
 private:
  template <typename... Ts>
  struct TypeListImplementation {};

  template <size_t Index, typename TList>
  struct TypeAt;

  template <size_t Index, typename T, typename... Ts>
  struct TypeAt<Index, TypeListImplementation<T, Ts...>>
      : TypeAt<Index - 1, TypeListImplementation<Ts...>> {};

  template <typename T, typename... Ts>
  struct TypeAt<0, TypeListImplementation<T, Ts...>> {
    using type = T;
  };

  template <typename T, typename TList>
  struct Contains;

  template <typename T>
  struct Contains<T, TypeListImplementation<>> : std::false_type {};

  template <typename T, typename Start, typename... BehindStart>
  struct Contains<T, TypeListImplementation<Start, BehindStart...>>
      : std::conditional_t<
            std::is_same_v<T, Start>, std::true_type,
            Contains<T, TypeListImplementation<BehindStart...>>> {};

  template <typename T, typename TList>
  struct IndexOf;

  template <typename T, typename Start, typename... BehindStart>
  struct IndexOf<T, TypeListImplementation<Start, BehindStart...>> {
   private:
    static constexpr ssize_t next =
        IndexOf<T, TypeListImplementation<BehindStart...>>::value;

   public:
    static constexpr size_t value =
        std::is_same_v<T, Start> ? 0 : (next == -1 ? next : 1 + next);
  };

  template <typename T>
  struct IndexOf<T, TypeListImplementation<>> {
    static constexpr ssize_t value = -1;
  };

 public:
  static constexpr size_t size() noexcept { return sizeof...(Types); }

  template <size_t Index>
  using at = typename TypeAt<Index, TypeListImplementation<Types...>>::type;

  template <typename Type>
  static constexpr bool contains() noexcept {
    return Contains<Type, TypeListImplementation<Types...>>::value;
  }

  template <typename Type>
  static constexpr size_t index_of() noexcept {
    static_assert(contains<Type>(),
                  "TypeList::index_of: Type not found in TypeList");
    return IndexOf<Type, TypeListImplementation<Types...>>::value;
  }

  template <typename Type>
  using append = TypeList<Types..., Type>;

  template <typename Type>
  using prepend = TypeList<Type, Types...>;
};
