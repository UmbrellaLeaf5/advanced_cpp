#pragma once

#include <memory>

/**
 * @brief Макрос для быстрого объявления Singleton-класса.
 * @param ClassName: имя создаваемого класса.
 */
#define SINGLETON(ClassName)                          \
  class ClassName : public SingletonCRTP<ClassName> { \
   public:                                            \
    friend class SingletonCRTP<ClassName>;            \
                                                      \
   private:

/**
 * @brief Базовый класс для реализации `Singleton` через CRTP.
 * @tparam T: класс, который должен стать `Singleton`.
 */
template <typename T>
class SingletonCRTP {
 public:
  SingletonCRTP(const SingletonCRTP&) = delete;
  SingletonCRTP& operator=(const SingletonCRTP&) = delete;

  /**
   * @brief Возвращает единственный экземпляр класса.
   * @return T*: указатель на экземпляр `Singleton`.
   */
  static T* Instance() {
    static T inst;
    return &inst;
  }

 protected:
  /**
   * @brief Защищенный конструктор.
   * @details Предотвращает создание экземпляров вне метода `Instance()`.
   */
  SingletonCRTP() = default;

  /**
   * @brief Защищенный деструктор.
   */
  ~SingletonCRTP() = default;
};
