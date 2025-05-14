#pragma once

/**
 * @brief Шаблонный класс для подсчета экземпляров производных классов (CRTP).
 * @tparam Derived: класс, наследующий от CounterCRTP.
 * @details Реализует идиому CRTP (Curiously Recurring Template Pattern).
 * Подсчитывает количество живых экземпляров производного класса.
 */
template <typename Derived>
class CounterCRTP {
 public:
  /**
   * @brief Конструктор по умолчанию.
   * @details Увеличивает счетчик экземпляров.
   */
  CounterCRTP() { count_++; }

  /**
   * @brief Конструктор копирования.
   * @details Увеличивает счетчик экземпляров.
   */
  CounterCRTP(const Derived&) { count_++; }

  /**
   * @brief Уничтожает экземпляр Counter CRTP
   * @details Уменьшает счетчик экземпляров.
   */
  ~CounterCRTP() { count_--; }

  /**
   * @brief Возвращает количество живых экземпляров.
   * @return int: текущее количество экземпляров.
   */
  static int Count() { return count_; }

 private:
  inline static int count_ = 0;
};
