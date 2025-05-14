#pragma once

#include <type_traits>

using std::size_t;
using ssize_t = std::make_signed<size_t>::type;

/**
 * @brief Шаблонный класс для работы со списком типов.
 * @tparam Types: список типов, хранимых в `TypeList`.
 */
template <typename... Types>
class TypeList {
 private:
  /**
   * @brief Внутренняя структура-обертка для списка типов.
   * @tparam List: список типов для хранения.
   */
  template <typename... List>
  struct TypeList_ {};

  /**
   * @brief Вспомогательная структура для получения типа по индексу.
   * @tparam Index: индекс искомого типа.
   * @tparam List: список типов для поиска.
   */
  template <size_t Index, typename List>
  struct TypeAt_;

  /**
   * @brief Специализация для получения первого типа в списке (индекс 0).
   * @tparam Current: текущий (первый) тип в списке.
   * @tparam Rest: остальные типы в списке.
   */
  template <typename Current, typename... Rest>
  struct TypeAt_<0, TypeList_<Current, Rest...>> {
    using type = Current;
  };

  /**
   * @brief Рекурсивная специализация для получения типа по индексу.
   * @tparam Index: искомый индекс (должен быть > 0).
   * @tparam Current: текущий тип в списке.
   * @tparam Rest: остальные типы в списке.
   */
  template <size_t Index, typename Current, typename... Rest>
  struct TypeAt_<Index, TypeList_<Current, Rest...>>
      : TypeAt_<Index - 1, TypeList_<Rest...>> {};

  /**
   * @brief Вспомогательная функция проверки наличия типа в списке (базовый
   * случай).
   * @tparam T: искомый тип.
   * @return false: всегда для пустого списка.
   */
  template <typename T>
  static constexpr bool Contains_() {
    return false;
  }

  /**
   * @brief Вспомогательная функция проверки наличия типа в списке.
   * @tparam T: искомый тип.
   * @tparam Current: текущий тип в списке.
   * @tparam Rest: остальные типы в списке.
   * @return bool: `true`, если тип найден, `false` в противном случае.
   */
  template <typename T, typename Current, typename... Rest>
  static constexpr bool Contains_() {
    if constexpr (!std::is_same_v<T, Current>) return Contains_<T, Rest...>();

    return true;
  }

  /**
   * @brief Вспомогательная функция поиска индекса типа (базовый случай).
   * @tparam T: искомый тип.
   * @return ssize_t: всегда `-1` для пустого списка.
   */
  template <typename T>
  static constexpr ssize_t IndexOf_() {
    return -1;
  }

  /**
   * @brief Вспомогательная функция поиска индекса типа.
   * @tparam T: искомый тип.
   * @tparam Current: текущий тип в списке.
   * @tparam Rest: остальные типы в списке.
   * @return ssize_t: индекс типа или `-1`, если тип не найден.
   */
  template <typename T, typename Current, typename... Rest>
  static constexpr ssize_t IndexOf_() {
    constexpr ssize_t next_index = IndexOf_<T, Rest...>();

    if constexpr (!std::is_same_v<T, Current>)
      return next_index == -1 ? next_index : 1 + next_index;

    return 0;
  }

 public:
  /**
   * @brief Возвращает количество типов в списке.
   * @return size_t: количество типов в списке.
   */
  static constexpr size_t Size() noexcept { return sizeof...(Types); }

  /**
   * @brief Получает тип по индексу.
   * @details Вызывает ошибку компиляции, если индекс выходит за границы списка.
   * @tparam Index: индекс искомого типа.
   */
  template <size_t Index>
  using At = typename TypeAt_<Index, TypeList_<Types...>>::type;

  /**
   * @brief Проверяет наличие типа в списке.
   * @tparam Type: искомый тип.
   * @return bool: `true`, если тип присутствует в списке, `false` в противном
   * случае.
   */
  template <typename Type>
  static constexpr bool Contains() noexcept {
    return Contains_<Type, Types...>();
  }

  /**
   * @brief Находит индекс типа в списке.
   * @details Вызывает static_assert, если тип не найден в списке.
   * @tparam Type: искомый тип.
   * @return size_t: индекс типа в списке.
   */
  template <typename Type>
  static constexpr size_t IndexOf() noexcept {
    constexpr ssize_t index_of = IndexOf_<Type, Types...>();

    static_assert(Contains<Type>() || index_of != -1,
                  "TypeList::IndexOf: Type not found in TypeList");

    return static_cast<size_t>(index_of);
  }

  /**
   * @brief Добавляет тип в конец списка.
   * @tparam Type: тип для добавления.
   */
  template <typename Type>
  using Append = TypeList<Types..., Type>;

  /**
   * @brief Добавляет тип в начало списка.
   * @tparam Type: тип для добавления.
   */
  template <typename Type>
  using Prepend = TypeList<Type, Types...>;
};
