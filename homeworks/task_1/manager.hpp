#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class User;
class Group;

/// @brief Менеджер для управления пользователями и группами.
class Manager {
 public:
  /**
   * @brief Инициализирует новый экземпляр `Manager`
   * @param os: ссылка на поток вывода для сообщений.
   */
  Manager(std::ostream& os) : os_{os} {}

  /**
   * @brief Создает нового пользователя.
   * @param user_id: уникальный идентификатор пользователя.
   * @param nickname: псевдоним пользователя.
   * @param group_id: идентификатор группы (необязательный, по умолчанию -1).
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& CreateUser(size_t user_id, const std::string& nickname,
                           ssize_t group_id = -1);

  /**
   * @brief Удаляет пользователя.
   * @param user_id: идентификатор пользователя для удаления.
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& DeleteUser(size_t user_id);

  /**
   * @brief Выводит информацию о пользователе.
   * @param user_id: идентификатор пользователя.
   * @return std::ostream&: ссылка на поток вывода с информацией.
   */
  std::ostream& PrintUser(size_t user_id) const;

  /**
   * @brief Выводит информацию обо всех пользователях.
   * @return std::ostream&: ссылка на поток вывода с информацией.
   */
  std::ostream& PrintAllUsers() const;

  /**
   * @brief Создает новую группу.
   * @param group_id: уникальный идентификатор группы.
   * @param title: название группы.
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& CreateGroup(size_t group_id, const std::string& title);

  /**
   * @brief Удаляет группу.
   * @param group_id: идентификатор группы для удаления.
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& DeleteGroup(size_t group_id);

  /**
   * @brief Выводит информацию о группе.
   * @param group_id: идентификатор группы.
   * @return std::ostream&: ссылка на поток вывода с информацией.
   */
  std::ostream& PrintGroup(size_t group_id) const;

  /**
   * @brief Выводит информацию обо всех группах.
   * @return std::ostream&: ссылка на поток вывода с информацией.
   */
  std::ostream& PrintAllGroups() const;

  /**
   * @brief Добавляет пользователя в группу.
   * @param user_id: идентификатор пользователя.
   * @param group_id: идентификатор группы.
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& AddUser(size_t user_id, size_t group_id);

  /**
   * @brief Удаляет пользователя из группы.
   * @param user_id: идентификатор пользователя.
   * @param group_id: идентификатор группы.
   * @return std::ostream&: ссылка на поток вывода с результатом операции.
   */
  std::ostream& RemoveUser(size_t user_id, size_t group_id);

  /**
   * @brief Уничтожает экземпляр `Manager`.
   */
  ~Manager() = default;

 private:
  std::ostream& os_;

  std::unordered_map<size_t, std::shared_ptr<User>> users_dict_;
  std::unordered_map<size_t, std::shared_ptr<Group>> groups_dict_;

  /**
   * @brief Получает nickname пользователя.
   * @param user_id: идентификатор пользователя.
   * @return std::string: nickname пользователя в кавычках или пустая строка.
   */
  std::string GetUserNickname_(size_t user_id) const;

  /**
   * @brief Получает название группы.
   * @param group_id: идентификатор группы.
   * @return std::string: название группы в кавычках или пустая строка.
   */
  std::string GetGroupTitle_(size_t group_id) const;

  /**
   * @brief Формирует строку с полной информацией о пользователе.
   * @param user_id: идентификатор пользователя.
   * @return std::string: строка с nickname и ID пользователя.
   */
  std::string GetUserFullString_(size_t user_id) const;

  /**
   * @brief Формирует строку с полной информацией о группе.
   * @param group_id: идентификатор группы.
   * @return std::string: строка с названием и ID группы.
   */
  std::string GetGroupFullString_(size_t group_id) const;
};
