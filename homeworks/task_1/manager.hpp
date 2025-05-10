#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class User;
class Group;

class Manager {
 public:
  Manager(std::ostream& os) : os_{os} {}

  std::ostream& CreateUser(size_t user_id, const std::string& nickname,
                           ssize_t group_id = -1);
  std::ostream& DeleteUser(size_t user_id);

  std::ostream& PrintUser(size_t user_id) const;
  std::ostream& PrintAllUsers() const;

  std::ostream& CreateGroup(size_t group_id, const std::string& title);
  std::ostream& DeleteGroup(size_t group_id);

  std::ostream& PrintGroup(size_t group_id) const;
  std::ostream& PrintAllGroups() const;

  std::ostream& AddUser(size_t user_id, size_t group_id);
  std::ostream& RemoveUser(size_t user_id, size_t group_id);

  ~Manager() = default;

 private:
  std::ostream& os_;

  std::unordered_map<size_t, std::shared_ptr<User>> users_dict_;
  std::unordered_map<size_t, std::shared_ptr<Group>> groups_dict_;

  std::string GetUserNickname_(size_t user_id) const;
  std::string GetGroupTitle_(size_t group_id) const;

  std::string GetUserFullString_(size_t user_id) const;
  std::string GetGroupFullString_(size_t group_id) const;
};
