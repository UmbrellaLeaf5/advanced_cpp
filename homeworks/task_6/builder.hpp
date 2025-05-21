#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Checkpoint;

/**
 * @brief Абстрактный интерфейс строителя списка контрольных точек.
 * @details Определяет основные этапы построения различных представлений списка
 * контрольных точек.
 */
class CheckpointListBuilder {
 public:
  /// @brief Сбрасывает состояние строителя для нового построения.
  virtual void Reset() = 0;

  /**
   * @brief Добавляет контрольную точку в строитель.
   * @param checkpoint: контрольная точка для добавления.
   */
  virtual void Add(const Checkpoint& checkpoint) = 0;

  /**
   * @brief Возвращает результат построения.
   * @return std::string: строковое представление результата.
   */
  virtual std::string GetResult() = 0;

  /// @brief Виртуальный деструктор для корректного удаления производных
  /// классов.
  virtual ~CheckpointListBuilder() = default;
};

/**
 * @brief Класс, представляющий контрольную точку трассы.
 * @details Содержит информацию о контрольной точке:
 * - Название
 * - Географические координаты
 * - Штрафное время (для опциональных точек)
 * - Флаг обязательности
 */
class Checkpoint {
 public:
  std::string name;
  double latitude;
  double longitude;
  double penalty;
  bool is_optional;

  /**
   * @brief Основной конструктор контрольной точки.
   * @param name: название точки.
   * @param latitude: широта.
   * @param longitude: долгота.
   * @param penalty: штрафное время.
   * @param is_optional: флаг опциональности.
   */
  Checkpoint(const std::string& name, double latitude, double longitude,
             double penalty, bool is_optional)
      : name(name),
        latitude(latitude),
        longitude(longitude),
        penalty(penalty),
        is_optional(is_optional) {}

  /**
   * @brief Упрощенный конструктор для обязательных контрольных точек.
   * @param name: название точки.
   * @param latitude: широта.
   * @param longitude: долгота.
   * @details Создает обязательную точку с нулевым штрафом.
   */
  Checkpoint(const std::string& name, double latitude, double longitude)
      : Checkpoint(name, latitude, longitude, 0.0, false) {}
};

/**
 * @brief Конкретный строитель для текстового представления списка точек.
 * @details Формирует читаемое текстовое описание всех контрольных точек.
 */
class TextCheckpointListBuilder : public CheckpointListBuilder {
 private:
  std::string result_;
  int checkpoint_count_;

 public:
  /// @brief Конструктор, инициализирующий начальное состояние.
  TextCheckpointListBuilder() : checkpoint_count_(0) { Reset(); }

  void Reset() override {
    result_.clear();
    checkpoint_count_ = 0;
  }

  void Add(const Checkpoint& checkpoint) override {
    checkpoint_count_++;

    result_ += std::to_string(checkpoint_count_) + ". ";
    result_ += checkpoint.name + "; ";
    result_ += "Latitude: " + std::to_string(checkpoint.latitude) +
               ", Longitude: " + std::to_string(checkpoint.longitude) + "; ";

    result_ +=
        checkpoint.is_optional
            ? "Penalty: " + std::to_string(checkpoint.penalty) + " hours\n"
            : "Penalty: [optional cp]\n";
  }

  std::string GetResult() override { return result_; }
};

/**
 * @brief Конкретный строитель для расчета суммарного штрафа.
 * @details Вычисляет общее штрафное время только для опциональных точек.
 */
class PenaltyCheckpointListBuilder : public CheckpointListBuilder {
 private:
  double total_penalty_;

 public:
  PenaltyCheckpointListBuilder() { Reset(); }

  void Reset() override { total_penalty_ = 0.0; }

  void Add(const Checkpoint& checkpoint) override {
    if (checkpoint.is_optional) total_penalty_ += checkpoint.penalty;
  }

  std::string GetResult() override {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << total_penalty_;
    return "Total Penalty: " + ss.str() + " hours";
  }
};

/**
 * @brief Директор, управляющий процессом построения.
 * @details Организует процесс построения, используя переданный строитель.
 */
class RaceTrackDirector {
 public:
  /**
   * @brief Строит представление списка контрольных точек.
   * @param builder: указатель на конкретный строитель.
   * @param checkpoints: вектор контрольных точек для обработки.
   */
  void Construct(CheckpointListBuilder* builder,
                 const std::vector<Checkpoint>& checkpoints) {
    builder->Reset();

    for (const auto& checkpoint : checkpoints) builder->Add(checkpoint);
  }
};
