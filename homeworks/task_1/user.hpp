#pragma once

#include <memory>
#include <string>
#include <vector>

class Group;

// MARK: User

/// @brief Представляет пользователя системы.
class User {
 public:
  User() = delete;
  User(const User&) = delete;
  User& operator=(const User&) = delete;

  /**
   * @brief Инициализирует новый экземпляр `User`
   * @param id: уникальный идентификатор пользователя.
   * @param nickname: псевдоним пользователя.
   */
  User(size_t id, const std::string& nickname) : id_{id}, nickname_(nickname) {}

  /**
   * @brief Проверяет, состоит ли пользователь в какой-либо группе.
   * @return bool: `true`, если пользователь состоит в группе, `false` в
   * противном случае.
   */
  bool HasGroup() const { return group_ptr_.lock() != nullptr; }

  /**
   * @brief Добавляет пользователя в группу.
   * @param group: умный указатель на объект `Group`.
   */
  void AddToGroup(const std::shared_ptr<Group>& group) { group_ptr_ = group; }

  /**
   * @brief Удаляет пользователя из текущей группы.
   */
  void RemoveFromGroup() { group_ptr_.reset(); }

  /**
   * @brief Возвращает идентификатор пользователя.
   * @return size_t: уникальный идентификатор пользователя.
   */
  auto GetId() const { return id_; }

  /**
   * @brief Возвращает псевдоним пользователя.
   * @return std::string: псевдоним пользователя.
   */
  auto GetNickname() const { return nickname_; }

  /**
   * @brief Возвращает указатель на группу пользователя.
   * @return std::shared_ptr<Group>: умный указатель на объект `Group` или
   * `nullptr`.
   */
  auto GetGroup() const { return group_ptr_.lock(); }

  /**
   * @brief Сравнивает пользователей по идентификатору.
   * @param rhs: ссылка на объект `User` для сравнения.
   * @return bool: `true`, если идентификаторы совпадают, `false` в противном
   * случае.
   */
  bool operator==(const User& rhs) const { return id_ == rhs.GetId(); }

  /**
   * @brief Уничтожает экземпляр `User`.
   * @note Лучше удалять пользователя из группы через менеджер, а не в
   * деструкторе.
   */
  ~User() = default;

 private:
  std::weak_ptr<Group> group_ptr_;
  size_t id_;

  std::string nickname_;
};

// MARK: operator<<

/**
 * @brief Перегруженный оператор << для вывода информации о пользователе в поток
 * вывода.
 * @param os: ссылка на поток вывода.
 * @param user: ссылка на объект `User`, который необходимо вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os, const User& user);

/**
 * @brief Перегруженный оператор << для вывода информации о User, представленном
 * слабым указателем.
 * @param os: ссылка на поток вывода.
 * @param user_ptr: слабый указатель на объект `User`, который необходимо
 * вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os, const std::weak_ptr<User>& user_ptr);

/**
 * @brief Перегруженный оператор << для вывода информации о User, представленном
 * общим указателем.
 * @param os: ссылка на поток вывода.
 * @param user_ptr: общий указатель на объект `User`, который необходимо
 * вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<User>& user_ptr);
