#pragma once

// #include <concepts>

// template <typename T>
// concept LessThanComparable = requires(const T& a, const T& b) {
//   { a < b } -> std::convertible_to<bool>;
// };

/**
 * @brief Шаблонный класс для добавления операторов сравнения через CRTP.
 * @tparam Derived: класс, наследующий от LessThanComparableCRTP.
 * @details Реализует идиому CRTP. Требует только оператор `<` в производном
 * классе, остальные операторы (`>`, `<=`, `>=`, `==`, `!=`) реализуются
 * автоматически.
 */
template <typename Derived>
class LessThanComparableCRTP {
 public:
  /**
   * @brief Оператор "больше".
   * @param other: объект для сравнения.
   * @return bool: результат сравнения `other < *this`.
   */
  bool operator>(const Derived& other) const {
    // LessThanComparableCRTP<Derived> (to) const Derived&
    // + гарантированно знаем, что Derived является производным от
    // LessThanComparableCRTP<Derived>
    return other < static_cast<const Derived&>(*this);
  }

  /**
   * @brief Оператор "меньше или равно".
   * @param other: объект для сравнения.
   * @return bool: результат отрицания `other < *this`.
   */
  bool operator<=(const Derived& other) const {
    return !(other < static_cast<const Derived&>(*this));
  }

  /**
   * @brief Оператор "больше или равно".
   * @param other: объект для сравнения.
   * @return bool: результат отрицания `other > *this`.
   */
  bool operator>=(const Derived& other) const {
    return !(other > static_cast<const Derived&>(*this));
  }

  /**
   * @brief Оператор равенства.
   * @param other: объект для сравнения.
   * @return bool: результат сравнения `other <= *this && other >= *this`.
   */
  bool operator==(const Derived& other) const {
    return (other <= static_cast<const Derived&>(*this)) &&
           (other >= static_cast<const Derived&>(*this));
  }

  /**
   * @brief Оператор неравенства.
   * @param other: объект для сравнения.
   * @return bool: результат отрицания `*this == other`.
   */
  bool operator!=(const Derived& other) const { return !(*this == other); }
};
