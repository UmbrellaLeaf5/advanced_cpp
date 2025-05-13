#include "user.hpp"

#include "group.hpp"

// MARK: operator<<

std::ostream& operator<<(std::ostream& os, const User& user) {
  auto group_ptr = user.GetGroup();

  os << "User:\n    | Nickname: " << user.GetNickname()
     << "\n    | ID: " << user.GetId() << "\n    | Group: ";

  if (group_ptr)
    os << "Title: " << group_ptr->GetTitle()
       << "\n    |           ID: " << group_ptr->GetId();
  else
    os << "[no group]";

  return os;
}

std::ostream& operator<<(std::ostream& os,
                         const std::weak_ptr<User>& user_ptr) {
  if (!user_ptr.lock()) return os << "*nullptr";

  return os << *user_ptr.lock();
}

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<User>& user_ptr) {
  if (!user_ptr) return os << "*nullptr";

  return os << *user_ptr;
}
