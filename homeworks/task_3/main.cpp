#include <iostream>
#include <string>

#include "type_map.hpp"

struct DataA {
  std::string value;
};

struct DataB {
  int value;
};

int main() {
  TypeMap<int, DataA, double, DataB> myTypeMap;

  // Добавление элементов в контейнер
  myTypeMap.SetValue<int>(42);
  myTypeMap.SetValue<double>(3.14);
  myTypeMap.SetValue<DataA>({"Hello, TypeMap!"});
  myTypeMap.SetValue<DataB>({10});

  // Получение и вывод значений по типам ключей
  std::cout << "Value for int: " << myTypeMap.GetValue<int>()
            << "\n";  // Вывод: 42
  std::cout << "Value for double: " << myTypeMap.GetValue<double>()
            << "\n";  // Вывод: 3.14
  std::cout << "Value for DataA: " << myTypeMap.GetValue<DataA>().value
            << "\n";  // Вывод: Hello, TypeMap!
  std::cout << "Value for DataB: " << myTypeMap.GetValue<DataB>().value
            << "\n";  // Вывод: 10
  // Проверка наличия элемента
  std::cout << "Contains int? " << (myTypeMap.Contains<int>() ? "Yes" : "No")
            << "\n";  // Вывод: Yes

  // Удаление элемента
  myTypeMap.RemoveValue<double>();

  // Попытка получения удаленного элемента
  std::cout << "Value for double after removal: "
            << myTypeMap.GetValue<double>()
            << "\n";  // Вывод: (некорректное значение)
  return 0;
}
