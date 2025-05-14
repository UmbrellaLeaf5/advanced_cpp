#pragma once

#include <memory>
#include <string>
#include <vector>

class User;

// MARK: Group

/// @brief Представляет группу пользователей.
class Group {
 public:
  Group() = delete;
  Group(const Group&) = delete;
  Group& operator=(const Group&) = delete;

  /**
   * @brief Инициализирует новый экземпляр `Group`
   * @param id: уникальный идентификатор группы.
   * @param title: название группы.
   */
  Group(size_t id, const std::string& title) : id_{id}, title_(title) {}

  /**
   * @brief Проверяет, состоит ли пользователь в группе.
   * @param user_ptr: умный указатель на объект `User`.
   * @return `true`, если пользователь состоит в группе, `false` в противном
   * случае.
   */
  bool IsUserIn(const std::shared_ptr<User>& user_ptr) const;

  /**
   * @brief Добавляет пользователя в группу.
   * @param user_ptr: умный указатель на объект `User`.
   * @throw std::runtime_error: если пользователь уже состоит в группе.
   */
  void AddUser(const std::shared_ptr<User>& user_ptr);

  /**
   * @brief Удаляет пользователя из группы.
   * @param user_ptr: умный указатель на объект `User`.
   * @throw std::runtime_error: если пользователь не состоит в группе.
   */
  void RemoveUser(const std::shared_ptr<User>& user_ptr);

  /**
   * @brief Возвращает идентификатор группы.
   * @return size_t: уникальный идентификатор группы.
   */
  auto GetId() const { return id_; }

  /**
   * @brief Возвращает название группы.
   * @return std::string: название группы.
   */
  auto GetTitle() const { return title_; }

  /**
   * @brief Возвращает список пользователей в группе.
   * @return std::vector<std::weak_ptr<User>>: слабые указателей на объекты
   * `User`, состоящие в группе.
   */
  auto GetUsers() const { return user_ptrs_; }

  /**
   * @brief Уничтожает экземпляр `Group`.
   * @details: При уничтожении группы, уведомляет всех пользователей в группе об
   * удалении группы, устанавливая их `Group` в `nullptr`.
   */
  ~Group();

 private:
  /**
   * @brief Ищет пользователя в векторе `user_ptrs_`.
   * @param user_ptr: умный указатель на объект User, который необходимо найти.
   * @return std::vector<std::weak_ptr<User>>::const_iterator: итератор на
   * найденного пользователя, либо `user_ptrs_.cend()`, если пользователь не
   * найден.
   */
  std::vector<std::weak_ptr<User>>::const_iterator UserIter_(
      const std::shared_ptr<User>& user_ptr) const;

  std::vector<std::weak_ptr<User>> user_ptrs_;
  size_t id_;

  std::string title_;
};

// MARK: operator<<

/**
 * @brief Перегруженный оператор << для вывода информации о группе в поток
 * вывода.
 * @param os: ссылка на поток вывода.
 * @param group: ссылка на объект `Group`, который необходимо вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os, const Group& group);

/**
 * @brief Перегруженный оператор << для вывода информации о Group,
 * представленном слабым указателем,  в поток вывода.
 * @param os: ссылка на поток вывода.
 * @param group_ptr: слабый указатель на объект `Group`, который необходимо
 * вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os,
                         const std::weak_ptr<Group>& group_ptr);

/**
 * @brief Перегруженный оператор << для вывода информации о Group,
 * представленном общим указателем, в поток вывода.
 * @param os: ссылка на поток вывода.
 * @param group_ptr: общий указатель на объект `Group`, который необходимо
 * вывести.
 * @return std::ostream&: ссылка на поток вывода.
 */
std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<Group>& group_ptr);
