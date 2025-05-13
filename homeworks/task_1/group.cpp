#include "group.hpp"

#include "user.hpp"

// MARK: Group

bool Group::IsUserIn(const std::shared_ptr<User>& user_ptr) const {
  return UserIter_(user_ptr) != user_ptrs_.end();
}

void Group::AddUser(const std::shared_ptr<User>& user_ptr) {
  if (IsUserIn(user_ptr)) throw std::runtime_error("Group::AddUser");

  user_ptrs_.push_back(user_ptr);
}

void Group::RemoveUser(const std::shared_ptr<User>& user_ptr) {
  auto it = UserIter_(user_ptr);

  if (it == user_ptrs_.end()) throw std::runtime_error("Group::RemoveUser");

  user_ptrs_.erase(it);
}

Group::~Group() {
  for (const auto& user_ptr : user_ptrs_)
    if (user_ptr.lock()) user_ptr.lock()->AddToGroup(nullptr);
}

std::vector<std::weak_ptr<User>>::const_iterator Group::UserIter_(
    const std::shared_ptr<User>& user_ptr) const {
  return std::find_if(user_ptrs_.cbegin(), user_ptrs_.cend(),
                      [&user_ptr](const auto& u) {
                        return u.lock() && *u.lock() == *user_ptr;
                      });
}

// MARK: operator<<

std::ostream& operator<<(std::ostream& os, const Group& group) {
  os << "Group:\n     | Title: " << group.GetTitle()
     << "\n     | ID: " << group.GetId() << "\n     | Users: ";

  for (const auto& user_ptr : group.GetUsers()) os << "\n " << user_ptr;

  if (group.GetUsers().empty()) os << "[no users]";

  return os;
}

std::ostream& operator<<(std::ostream& os,
                         const std::weak_ptr<Group>& group_ptr) {
  if (!group_ptr.lock()) return os << "*nullptr";

  return os << *group_ptr.lock();
}

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<Group>& group_ptr) {
  if (!group_ptr) return os << "*nullptr";

  return os << *group_ptr;
}
