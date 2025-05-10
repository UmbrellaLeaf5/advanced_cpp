#include "manager.hpp"

#include "group.hpp"
#include "user.hpp"
#include "utils.hpp"

std::ostream& Manager::CreateUser(size_t user_id, const std::string& nickname,
                                  ssize_t group_id) {
  if (IsKeyInMap(users_dict_, user_id)) {
    os_ << "? " << GetUserFullString_(user_id) << " is already exists ?\n\n";
    return os_;
  }

  users_dict_.insert({user_id, std::make_shared<User>(user_id, nickname)});
  if (group_id != -1) AddUser(user_id, group_id);

  os_ << "! User created SUCCESSFULLY !\n";
  return PrintUser(user_id);
}

std::ostream& Manager::DeleteUser(size_t user_id) {
  try {
    users_dict_.at(user_id);
    os_ << "! " << GetUserFullString_(user_id) << " deleted SUCCESSFULLY !\n\n";
    users_dict_.erase(user_id);

  } catch (const std::out_of_range&) {
    os_ << "? " << GetUserFullString_(user_id) << " does not exist ?\n\n";
  }

  return os_;
}

std::ostream& Manager::PrintUser(size_t user_id) const {
  try {
    os_ << users_dict_.at(user_id) << "\n\n";

  } catch (const std::out_of_range&) {
    os_ << "? " << GetUserFullString_(user_id) << " does not exist ?\n\n";
  }

  return os_;
}

std::ostream& Manager::PrintAllUsers() const {
  os_ << "! All Users: " << "\n";

  for (const auto& pair : users_dict_) PrintUser(pair.first);

  if (users_dict_.empty()) os_ << "    [no users]\n";
  return os_ << "!\n\n";
}

std::ostream& Manager::CreateGroup(size_t group_id, const std::string& title) {
  if (IsKeyInMap(groups_dict_, group_id)) {
    os_ << "? " << GetGroupFullString_(group_id) << " is already exists!\n\n";
    return os_;
  }

  groups_dict_.insert({group_id, std::make_shared<Group>(group_id, title)});

  os_ << "! Group created SUCCESSFULLY !\n";
  return PrintGroup(group_id);
}

std::ostream& Manager::DeleteGroup(size_t group_id) {
  try {
    groups_dict_.at(group_id);
    os_ << "! " << GetGroupFullString_(group_id)
        << " deleted SUCCESSFULLY !\n\n";
    groups_dict_.erase(group_id);

  } catch (const std::out_of_range&) {
    os_ << "? " << GetGroupFullString_(group_id) << " does not exist ?\n\n";
  }

  return os_;
}

std::ostream& Manager::PrintGroup(size_t group_id) const {
  try {
    os_ << groups_dict_.at(group_id) << "\n\n";

  } catch (const std::out_of_range&) {
    os_ << "? " << GetGroupFullString_(group_id) << " does not exist ?\n\n";
  }

  return os_;
}

std::ostream& Manager::PrintAllGroups() const {
  os_ << "! All Groups: " << "\n";

  for (const auto& pair : groups_dict_) PrintGroup(pair.first);

  if (groups_dict_.empty()) os_ << "    [no groups]\n";
  return os_ << "!\n\n";
}

std::ostream& Manager::AddUser(size_t user_id, size_t group_id) {
  try {
    auto user_ptr = users_dict_.at(user_id);
    auto group_ptr = groups_dict_.at(group_id);

    if (user_ptr->HasGroup()) {
      auto old_group_id = user_ptr->GetGroup()->GetId();
      auto old_group_ptr = groups_dict_.at(old_group_id);

      os_ << ". " << GetUserFullString_(user_id) << " already has "
          << GetGroupFullString_(group_id) << ", removing .\n\n";

      old_group_ptr->RemoveUser(user_ptr);
    }

    group_ptr->AddUser(user_ptr);
    user_ptr->AddToGroup(group_ptr);

    os_ << "! " << GetUserFullString_(user_id) << " added to "
        << GetGroupFullString_(group_id) << " SUCCESSFULLY !\n\n";

  } catch (const std::out_of_range&) {
    if (IsKeyInMap(groups_dict_, group_id))
      os_ << "? " << GetUserFullString_(user_id) << " does not exist ?\n\n";
    else
      os_ << "? " << GetGroupFullString_(group_id) << " does not exist ?\n\n";

  } catch (const std::runtime_error&) {
    os_ << "? " << GetGroupFullString_(group_id) << " already has "
        << GetUserFullString_(user_id) << " ?\n\n";
  }

  return os_;
}

std::ostream& Manager::RemoveUser(size_t user_id, size_t group_id) {
  try {
    groups_dict_.at(group_id)->RemoveUser(users_dict_.at(user_id));
    users_dict_.at(user_id)->RemoveFromGroup();

    os_ << "! " << GetUserFullString_(user_id) << " removed from "
        << GetGroupFullString_(group_id) << " SUCCESSFULLY !\n\n";

  } catch (const std::out_of_range&) {
    if (IsKeyInMap(groups_dict_, group_id))
      os_ << "? " << GetUserFullString_(user_id) << " does not exist ?\n\n";
    else
      os_ << "? " << GetGroupFullString_(group_id) << " does not exist ?\n\n";

  } catch (const std::runtime_error&) {
    os_ << "? " << GetGroupFullString_(group_id) << " has no "
        << GetUserFullString_(user_id) << " ?\n\n";
  }

  return os_;
}

std::string Manager::GetUserNickname_(size_t user_id) const {
  try {
    return "'" + users_dict_.at(user_id)->GetNickname() + "' ";
  } catch (const std::out_of_range&) {
    return "";
  }
}

std::string Manager::GetGroupTitle_(size_t group_id) const {
  try {
    return "'" + groups_dict_.at(group_id)->GetTitle() + "' ";
  } catch (const std::out_of_range&) {
    return "";
  }
}

std::string Manager::GetUserFullString_(size_t user_id) const {
  return "User " + GetUserNickname_(user_id) +
         "with ID: " + std::to_string(user_id);
}

std::string Manager::GetGroupFullString_(size_t group_id) const {
  return "Group " + GetGroupTitle_(group_id) +
         "with ID: " + std::to_string(group_id);
}
