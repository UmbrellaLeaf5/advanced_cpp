#pragma once

#include <memory>
#include <string>
#include <vector>

class Group;

// MARK: User

class User {
 public:
  User(const User&) = delete;
  User& operator=(const User&) = delete;

  User(size_t id, const std::string& nickname) : id_{id}, nickname_(nickname) {}

  bool HasGroup() const { return group_ptr_.lock() != nullptr; }

  void AddToGroup(const std::shared_ptr<Group>& group) { group_ptr_ = group; }
  void RemoveFromGroup() { group_ptr_.reset(); }

  auto GetId() const { return id_; }
  auto GetNickname() const { return nickname_; }

  auto GetGroup() const { return group_ptr_.lock(); }

  bool operator==(const User& rhs) const { return id_ == rhs.GetId(); }

  ~User();

 private:
  std::weak_ptr<Group> group_ptr_;
  size_t id_;

  std::string nickname_;
};

// MARK: operator<<

std::ostream& operator<<(std::ostream& os, const User& user);

std::ostream& operator<<(std::ostream& os, const std::weak_ptr<User>& user_ptr);

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<User>& user_ptr);
