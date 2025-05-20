#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

/**
 * @brief Абстрактный интерфейс для реализации множества.
 * @tparam T: тип элементов множества.
 * @details Определяет базовые операции для работы с множеством:
 * - Добавление и удаление элементов
 * - Проверка принадлежности
 * - Операции над множествами
 * - Получение информации о множестве
 */
template <typename T>
class VarietyImplementation {
 public:
  /// @brief Виртуальный деструктор для полиморфизма
  virtual ~VarietyImplementation() = default;

  /**
   * @brief Добавляет элемент в множество.
   * @param element: элемент для добавления.
   * @return bool: true если элемент был добавлен, false если уже существовал.
   */
  virtual bool Add(const T& element) = 0;

  /**
   * @brief Удаляет элемент из множества.
   * @param element: элемент для удаления.
   * @return bool: true если элемент был удален, false если не найден.
   */
  virtual bool Remove(const T& element) = 0;

  /**
   * @brief Проверяет наличие элемента в множестве.
   * @param element: искомый элемент.
   * @return bool: true если элемент присутствует.
   */
  virtual bool Contains(const T& element) const = 0;

  /**
   * @brief Объединяет текущее множество с другим.
   * @param other: другое множество для объединения.
   * @return unique_ptr<VarietyImplementation>: новое множество-результат.
   */
  virtual std::unique_ptr<VarietyImplementation> UnionSets(
      const VarietyImplementation& other) const = 0;

  /**
   * @brief Находит пересечение текущего множества с другим.
   * @param other: другое множество для пересечения.
   * @return unique_ptr<VarietyImplementation>: новое множество-результат.
   */
  virtual std::unique_ptr<VarietyImplementation> IntersectionSets(
      const VarietyImplementation& other) const = 0;

  /**
   * @brief Возвращает количество элементов в множестве.
   * @return size_t: текущий размер множества.
   */
  virtual size_t Size() const = 0;

  /**
   * @brief Конвертирует множество в вектор.
   * @return vector<T>: вектор содержащий все элементы множества.
   */
  virtual std::vector<T> ToVector() const = 0;
};

/**
 * @brief Реализация множества на основе массива.
 * @tparam T: тип элементов множества.
 * @details Оптимальна для небольших множеств:
 * - Использует vector для хранения
 * - Имеет ограничение по вместимости
 * - Линейный поиск элементов
 */
template <typename T>
class ArrayVarietyImplementation : public VarietyImplementation<T> {
 private:
  std::vector<T> data_;

  /// @brief Максимальная вместимость
  size_t capacity_;

 public:
  /**
   * @brief Конструктор реализации на массиве.
   * @param capacity: максимальное количество элементов.
   */
  explicit ArrayVarietyImplementation(size_t capacity) : capacity_(capacity) {}

  bool Add(const T& element) override {
    if (data_.size() >= capacity_ || Contains(element))
      return false;  // Нельзя добавить при превышении capacity или если элемент
                     // уже есть

    data_.push_back(element);
    return true;
  }

  bool Remove(const T& element) override {
    auto it = std::find(data_.begin(), data_.end(), element);

    if (it != data_.end()) {
      data_.erase(it);
      return true;
    }

    return false;
  }

  bool Contains(const T& element) const override {
    return std::find(data_.begin(), data_.end(), element) != data_.end();
  }

  std::unique_ptr<VarietyImplementation<T>> UnionSets(
      const VarietyImplementation<T>& other) const override {
    auto result = std::make_unique<ArrayVarietyImplementation<T>>(capacity_ +
                                                                  other.Size());

    for (const auto& val : data_) result->Add(val);
    for (const auto& val : other.ToVector()) result->Add(val);

    return result;
  }

  std::unique_ptr<VarietyImplementation<T>> IntersectionSets(
      const VarietyImplementation<T>& other) const override {
    auto result = std::make_unique<ArrayVarietyImplementation<T>>(capacity_);

    for (const auto& val : data_)
      if (other.Contains(val)) result->Add(val);

    return result;
  }

  size_t Size() const override { return data_.size(); }

  std::vector<T> ToVector() const override { return data_; }
};

/**
 * @brief Реализация множества на основе хеш-таблицы.
 * @tparam T: тип элементов множества.
 * @details Оптимальна для больших множеств:
 * - Использует unordered_set для хранения
 * - Быстрый поиск и вставка
 * - Нет ограничений по размеру
 */
template <typename T>
class HashVarietyImplementation : public VarietyImplementation<T> {
 private:
  std::unordered_set<T> data_;

 public:
  bool Add(const T& element) override { return data_.insert(element).second; }

  bool Remove(const T& element) override { return data_.erase(element) > 0; }

  bool Contains(const T& element) const override {
    return data_.count(element) > 0;
  }

  std::unique_ptr<VarietyImplementation<T>> UnionSets(
      const VarietyImplementation<T>& other) const override {
    auto result = std::make_unique<HashVarietyImplementation<T>>();

    for (const auto& val : data_) result->Add(val);

    for (const auto& val : other.ToVector()) result->Add(val);

    return result;
  }

  std::unique_ptr<VarietyImplementation<T>> IntersectionSets(
      const VarietyImplementation<T>& other) const override {
    auto result = std::make_unique<HashVarietyImplementation<T>>();

    for (const auto& val : data_)
      if (other.Contains(val)) result->Add(val);

    return result;
  }

  size_t Size() const override { return data_.size(); }

  std::vector<T> ToVector() const override {
    return std::vector<T>(data_.begin(), data_.end());
  }
};

/**
 * @brief Класс множества с автоматическим выбором реализации.
 * @tparam T: тип элементов множества.
 * @details Автоматически переключается между:
 * - ArrayVarietyImplementation для небольших множеств
 * - HashVarietyImplementation для больших множеств
 * на основе заданного порога (threshold_).
 */
template <typename T>
class Variety {
 private:
  std::unique_ptr<VarietyImplementation<T>> implementation_;
  /// @brief Порог переключения на хеш-таблицу
  size_t threshold_;
  size_t array_capacity_;

  /**
   * @brief Проверяет и корректирует реализацию при необходимости.
   * @details Переключает реализацию если:
   * - Размер превысил threshold_ и используется массив
   * - Размер меньше threshold_ и используется хеш-таблица
   */
  void EnsureCorrectImplementation_() {
    if (implementation_->Size() > threshold_ &&
        !dynamic_cast<HashVarietyImplementation<T>*>(implementation_.get())) {
      // Переключение на хеш-таблицу
      auto temp_imp = std::make_unique<HashVarietyImplementation<T>>();
      for (const auto& val : implementation_->ToVector()) temp_imp->Add(val);

      implementation_ = std::move(temp_imp);
    } else {
      // Переключение на массив
      auto temp_imp =
          std::make_unique<ArrayVarietyImplementation<T>>(array_capacity_);
      for (const auto& val : implementation_->ToVector()) temp_imp->Add(val);

      implementation_ = std::move(temp_imp);
    }
  }

 public:
  /**
   * @brief Конструктор множества.
   * @param threshold: порог для переключения реализаций.
   * @param array_capacity: вместимость массива в ArrayVarietyImplementation.
   */
  Variety(size_t threshold, size_t array_capacity)
      : threshold_(threshold), array_capacity_(array_capacity) {
    implementation_ =
        std::make_unique<ArrayVarietyImplementation<T>>(array_capacity);
  }

  /**
   * @brief Добавляет элемент в множество.
   * @param element: элемент для добавления.
   * @return bool: true если элемент был добавлен.
   */
  bool Add(const T& element) {
    bool result = implementation_->Add(element);
    EnsureCorrectImplementation_();
    return result;
  }

  /**
   * @brief Удаляет элемент из множества.
   * @param element: элемент для удаления.
   * @return bool: true если элемент был удален.
   */
  bool Remove(const T& element) {
    bool result = implementation_->Remove(element);
    EnsureCorrectImplementation_();
    return result;
  }

  /**
   * @brief Проверяет наличие элемента в множестве.
   * @param element: искомый элемент.
   * @return bool: true если элемент присутствует.
   */
  bool Contains(const T& element) const {
    return implementation_->Contains(element);
  }

  /**
   * @brief Объединяет текущее множество с другим.
   * @param other: другое множество для объединения.
   * @return unique_ptr<Variety>: новое множество-результат.
   */
  std::unique_ptr<Variety> UnionSets(const Variety& other) const {
    auto result = std::make_unique<Variety>(threshold_, array_capacity_);

    result->implementation_ =
        implementation_->UnionSets(*other.implementation_);
    result->EnsureCorrectImplementation_();

    return result;
  }

  /**
   * @brief Находит пересечение текущего множества с другим.
   * @param other: другое множество для пересечения.
   * @return unique_ptr<Variety>: новое множество-результат.
   */
  std::unique_ptr<Variety> IntersectionSets(const Variety& other) const {
    auto result = std::make_unique<Variety>(threshold_, array_capacity_);

    result->implementation_ =
        implementation_->IntersectionSets(*other.implementation_);
    result->EnsureCorrectImplementation_();

    return result;
  }

  /**
   * @brief Возвращает количество элементов в множестве.
   * @return size_t: текущий размер множества.
   */
  size_t Size() const { return implementation_->Size(); }

  /**
   * @brief Оператор вывода множества в поток.
   * @param os: выходной поток.
   * @param obj: множество для вывода.
   * @return ostream&: ссылка на поток.
   * @details Выводит все элементы и текущую реализацию.
   */
  friend std::ostream& operator<<(std::ostream& os, const Variety<T>& obj) {
    os << "Variety: ";
    for (const auto& val : obj.implementation_->ToVector()) os << val << " ";

    os << "\nImplementation: "
       << (dynamic_cast<ArrayVarietyImplementation<T>*>(
               obj.implementation_.get())
               ? "ArrayVariety"
               : "HashVariety")
       << "\n";

    return os;
  }
};
