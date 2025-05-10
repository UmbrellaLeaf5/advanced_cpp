#include <limits>

#include "manager.hpp"
#include "utils.hpp"

enum class EntityType { Group, User };

ssize_t ParseID(std::stringstream& ss, EntityType et,
                bool is_optional = false) {
  ssize_t id;

  if (ss.eof() && is_optional)
    return -1;

  else if (ss.eof())
    throw std::runtime_error((et == EntityType::User ? "User" : "Group") +
                             std::string(" ID is missing"));

  if (!(ss >> id))
    throw std::runtime_error((et == EntityType::User ? "User" : "Group") +
                             std::string("ID is not a number"));

  if (id < 0)
    throw std::runtime_error((et == EntityType::User ? "User" : "Group") +
                             std::string("ID should be positive"));

  return id;
}

std::string ParseName(std::stringstream& ss, EntityType et,
                      bool is_optional = false) {
  std::string name;

  if (ss.eof() && is_optional)
    return "";

  else if (ss.eof())
    throw std::runtime_error((et == EntityType::User ? "nickname" : "title") +
                             std::string(" is missing"));

  if (!(ss >> name))
    // IDK: impossible case?
    throw std::runtime_error((et == EntityType::User ? "nickname" : "title") +
                             std::string(" is not a string"));

  return name;
}

int main() {
  Manager manager(std::cout);

  std::map<std::string, std::function<void(Manager&, std::stringstream&)>>
      command_map = {
          {"help",
           []([[maybe_unused]] Manager& m,
              [[maybe_unused]] std::stringstream& ss) {
             std::cout
                 << "'createUser {userId} {nickname} [groupId]' - "
                    "create a new user;\n"
                    "'deleteUser {userId}' - delete a user;\n"
                    "'allUsers' - display information on all users;\n"
                    "'getUser {userId}' - display information on one user;\n"
                    "'createGroup {groupId} {title}' - create a new group;\n"
                    "'deleteGroup {groupId}' - delete a group;\n"
                    "'allGroups' - display information on all groups, "
                    "including all users who are members of them;\n"
                    "'getGroup {groupId}' - display information on one "
                    "group, including all users who are members of it;\n"
                    "'addUser {userId} {groupId}' - add user to group;\n"
                    "'removeUser {userId} {groupId}' - remove a user from a "
                    "group;\n\n";
           }},
          {"createUser",
           [](Manager& m, std::stringstream& ss) {
             auto user_id = ParseID(ss, EntityType::User);
             auto name = ParseName(ss, EntityType::User);
             auto group_id = ParseID(ss, EntityType::Group, true);

             m.CreateUser(user_id, name, group_id);
           }},
          {"deleteUser",
           [](Manager& m, std::stringstream& ss) {
             m.DeleteUser(ParseID(ss, EntityType::User));
           }},
          {"allUsers",
           [](Manager& m, [[maybe_unused]] std::stringstream& ss) {
             m.PrintAllUsers();
           }},
          {"getUser",
           [](Manager& m, std::stringstream& ss) {
             m.PrintUser(ParseID(ss, EntityType::User));
           }},
          {"createGroup",
           [](Manager& m, std::stringstream& ss) {
             auto id = ParseID(ss, EntityType::Group);
             auto name = ParseName(ss, EntityType::Group);

             m.CreateGroup(id, name);
           }},
          {"deleteGroup",
           [](Manager& m, std::stringstream& ss) {
             m.DeleteGroup(ParseID(ss, EntityType::Group));
           }},
          {"allGroups",
           [](Manager& m, [[maybe_unused]] std::stringstream& ss) {
             m.PrintAllGroups();
           }},
          {"getGroup",
           [](Manager& m, std::stringstream& ss) {
             m.PrintGroup(ParseID(ss, EntityType::Group));
           }},
          {"addUser",
           [](Manager& m, std::stringstream& ss) {
             auto user_id = ParseID(ss, EntityType::User);
             auto group_id = ParseID(ss, EntityType::Group);

             m.AddUser(user_id, group_id);
           }},
          {"removeUser", [](Manager& m, std::stringstream& ss) {
             auto user_id = ParseID(ss, EntityType::User);
             auto group_id = ParseID(ss, EntityType::Group);

             m.RemoveUser(user_id, group_id);
           }}};

  std::string command;

  for (;;) {
    std::cout << "/";
    if (!std::getline(std::cin, command)) break;

    std::stringstream ss(command);

    std::string action;
    ss >> action;

    auto it = command_map.find(action);

    if (it != command_map.end()) try {
        std::cout << "\n";

        it->second(manager, ss);
      } catch (const std::runtime_error& re) {
        std::cout << "? Invalid command arguments: " << re.what() << " ? \n\n";
      }

    else
      std::cerr << "? Unknown command: '" << action << "' ? \n\n";
  }

  return 0;
}
