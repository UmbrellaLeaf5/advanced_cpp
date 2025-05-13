#pragma once

#include <memory>
#include <string>
#include <vector>

class User;

// MARK: Group

class Group {
 public:
  Group() = delete;
  Group(const Group&) = delete;
  Group& operator=(const Group&) = delete;

  Group(size_t id, const std::string& title) : id_{id}, title_(title) {}

  bool IsUserIn(const std::shared_ptr<User>& user_ptr) const;

  void AddUser(const std::shared_ptr<User>& user_ptr);
  void RemoveUser(const std::shared_ptr<User>& user_ptr);

  auto GetId() const { return id_; }
  auto GetTitle() const { return title_; }

  auto GetUsers() const { return user_ptrs_; }

  ~Group();

 private:
  std::vector<std::weak_ptr<User>>::const_iterator UserIter_(
      const std::shared_ptr<User>& user_ptr) const;

  std::vector<std::weak_ptr<User>> user_ptrs_;
  size_t id_;

  std::string title_;
};

// MARK: operator<<

std::ostream& operator<<(std::ostream& os, const Group& group);

std::ostream& operator<<(std::ostream& os,
                         const std::weak_ptr<Group>& group_ptr);

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<Group>& group_ptr);
