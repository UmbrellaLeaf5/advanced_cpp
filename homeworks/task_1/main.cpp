#include "manager.hpp"
#include "utils.hpp"

int main() {
  auto manager = Manager(std::cout);

  manager.CreateUser(5, "Dima");
  manager.CreateUser(7, "Nikita");
  manager.CreateUser(8, "Iluha");
  manager.CreateUser(8, "Lolich");

  manager.PrintAllUsers();

  manager.CreateGroup(1, "137");

  manager.PrintAllGroups();

  manager.AddUser(5, 1);
  manager.AddUser(5, 1);
  manager.AddUser(7, 1);
  manager.AddUser(8, 1);

  manager.AddUser(8, 3);
  manager.AddUser(10, 3);
  manager.AddUser(10, 1);

  manager.PrintAllGroups();

  manager.CreateGroup(1, "Botalka");
  manager.CreateGroup(2, "Botalka");
  manager.CreateUser(9, "Sanya", 2);
  manager.AddUser(9, 1);

  manager.RemoveUser(9, 2);

  manager.PrintAllUsers();
  manager.PrintAllGroups();

  manager.DeleteUser(5);
  manager.DeleteUser(45);

  manager.PrintAllUsers();
  manager.PrintAllGroups();

  manager.DeleteGroup(42);
  manager.DeleteGroup(1);

  manager.PrintAllUsers();
  manager.PrintAllGroups();

  return 0;
}
