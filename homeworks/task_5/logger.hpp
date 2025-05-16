#pragma once

#include <chrono>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "singleton.hpp"

/**
 * @brief Уровни важности лог-сообщений.
 * @details Определяет три уровня логирования:
 * - `LOG_NORMAL`: Обычные информационные сообщения
 * - `LOG_WARNING`: Предупреждения
 * - `LOG_ERROR`: Критические ошибки
 */
enum LoggerLevel { LOG_NORMAL, LOG_WARNING, LOG_ERROR };

/**
 * @brief Класс для логирования сообщений (реализует паттерн `Singleton`).
 * @details Обеспечивает:
 * - Запись сообщений с временными метками
 * - Поддержку разных уровней важности
 * - Вывод в консоль или файл
 * - Хранение последних 10 сообщений (кольцевой буфер)
 */
class Logger : public SingletonCRTP<Logger> {
  friend class SingletonCRTP<Logger>;

 public:
  /**
   * @brief Добавляет сообщение в лог.
   * @param level: уровень важности сообщения.
   * @param text: текст сообщения.
   * @details Формат сообщения:
   * [ВРЕМЯ | ДАТА] [УРОВЕНЬ] Текст сообщения
   */
  void Message(LoggerLevel level, const std::string& text) {
    auto time_t_now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto tm_now = *std::localtime(&time_t_now);

    std::ostringstream oss;
    oss << "[" << std::put_time(&tm_now, "%H:%M:%S | %d.%m.%Y") << "] "
        << "[" << LevelToString_(level) << "] " << text;

    if (logs_.size() >= 10) logs_.pop_front();

    logs_.push_back(oss.str());
  }

  /**
   * @brief Выводит все сохраненные сообщения.
   * @details Вывод осуществляется в текущий установленный поток (файл или
   * консоль). Сообщения разделяются разделительной линией.
   */
  void Print() const {
    *output_stream_ << "--------------------------------------------------\n";
    for (const auto& log : logs_) *output_stream_ << log << "\n";
  }

  /**
   * @brief Устанавливает выходной поток для логирования.
   * @param stream: ссылка на поток вывода (std::cout, std::cerr и т.д.)
   * @return std::ostream*: указатель на установленный поток.
   */
  auto SetStream(std::ostream& stream) {
    output_stream_ = &stream;
    return output_stream_;
  }

  /**
   * @brief Устанавливает файл для логирования.
   * @param filename: путь к файлу для записи.
   * @return std::ostream*: указатель на файловый поток.
   * @note Если файл не может быть открыт, автоматически используется std::cout.
   */
  auto SetStream(const std::string& filename) {
    file_stream_ = std::make_unique<std::ofstream>(filename);

    if (file_stream_->is_open())
      output_stream_ = file_stream_.get();

    else {
      std::cerr << "Failed to open file: " << filename
                << ".\n\t(using std::cout instead)" << std::endl;
      output_stream_ = &std::cout;
    }

    return file_stream_.get();
  }

 private:
  /**
   * @brief Приватный конструктор.
   * @details Инициализирует вывод в std::cout по умолчанию.
   */
  Logger() : output_stream_(&std::cout) {}

  /// @brief Приватный деструктор.
  ~Logger() = default;

  /**
   * @brief Преобразует уровень логирования в строку.
   * @param level: уровень логирования.
   * @return std::string: строковое представление уровня.
   */
  std::string LevelToString_(LoggerLevel level) const {
    switch (level) {
      case LOG_NORMAL:
        return "NORMAL";
      case LOG_WARNING:
        return "WARNING";
      case LOG_ERROR:
        return "ERROR";
      default:
        return "UNKNOWN";
    }
  }

  std::deque<std::string> logs_;
  std::ostream* output_stream_;
  std::unique_ptr<std::ofstream> file_stream_;
};
