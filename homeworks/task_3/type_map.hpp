#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "type_list.hpp"

/**
 * @brief Шаблонный класс для хранения значений разных типов с безопасным
 * доступом.
 * @details Позволяет хранить по одному значению каждого из указанных типов,
 * обеспечивая проверку типов на этапе компиляции.
 * @tparam Types: список типов, которые могут храниться в `TypeMap`.
 */
template <typename... Types>
class TypeMap {
 private:
  using TypeList_ = TypeList<Types...>;
  using VariantType_ = std::variant<Types...>;

  /**
   * @brief Хранилище данных в виде пар (флаг инициализации, значение).
   * @details Каждый элемент соответствует одному из типов в TypeList_. Первый
   * элемент пары указывает, было ли значение инициализировано.
   */
  std::vector<std::pair<bool, VariantType_>> data_;

  /**
   * @brief Получает индекс типа в списке допустимых типов.
   * @tparam Type: тип, для которого требуется получить индекс.
   * @return size_t: индекс типа в списке Types.
   */
  template <typename Type>
  static constexpr size_t GetIndex_() {
    return TypeList_::template IndexOf<Type>();
  }

 public:
  /**
   * @brief Конструктор по умолчанию.
   * @details Инициализирует хранилище данными для всех типов из списка, помечая
   * их как неинициализированные.
   */
  TypeMap() : data_(TypeList_::Size()) {}

  /**
   * @brief Устанавливает значение для указанного типа.
   * @tparam Type: тип устанавливаемого значения.
   * @param value: значение для сохранения.
   * @throws static_assert: если `Type` не входит в список допустимых типов.
   */
  template <typename Type>
  void SetValue(const Type& value) {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::SetValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    data_[index].second = value;
    data_[index].first = true;
  }

  /**
   * @brief Получает значение указанного типа.
   * @tparam Type: тип запрашиваемого значения.
   * @return const Type&: константная ссылка на сохраненное значение.
   * @throws static_assert: если `Type` не входит в список допустимых типов.
   * @throws std::runtime_error: если значение не было инициализировано.
   */
  template <typename Type>
  const Type& GetValue() const {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::GetValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    if (!data_[index].first)
      throw std::runtime_error("TypeMap::GetValue: Value not initialized.");

    return std::get<Type>(data_[index].second);
  }

  /**
   * @brief Проверяет наличие значения указанного типа.
   * @tparam Type: тип для проверки.
   * @return bool: `true`, если значение было установлено, `false` в противном
   * случае.
   * @throws static_assert: если `Type` не входит в список допустимых типов.
   */
  template <typename Type>
  bool Contains() const {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::Contains: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    return data_[index].first;
  }

  /**
   * @brief Удаляет значение указанного типа.
   * @tparam Type: тип значения для удаления.
   * @throws static_assert: если `Type` не входит в список допустимых типов.
   * @details Помечает значение как неинициализированное и сбрасывает хранимое
   * значение.
   */
  template <typename Type>
  void RemoveValue() {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::RemoveValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    data_[index].first = false;
    data_[index].second = VariantType_{};
  }
};
