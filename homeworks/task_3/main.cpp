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
  myTypeMap.AddValue<int>(42);
  myTypeMap.AddValue<double>(3.14);
  myTypeMap.AddValue<DataA>({"Hello, TypeMap!"});
  myTypeMap.AddValue<DataB>({10});

  // Получение и вывод значений по типам ключей
  std::cout << "Value for int: " << myTypeMap.GetValue<int>()
            << std::endl;  // Вывод: 42
  std::cout << "Value for double: " << myTypeMap.GetValue<double>()
            << std::endl;  // Вывод: 3.14
  std::cout << "Value for DataA: " << myTypeMap.GetValue<DataA>().value
            << std::endl;  // Вывод: Hello, TypeMap!
  std::cout << "Value for DataB: " << myTypeMap.GetValue<DataB>().value
            << std::endl;  // Вывод: 10
  // Проверка наличия элемента
  std::cout << "Contains int? " << (myTypeMap.Contains<int>() ? "Yes" : "No")
            << std::endl;  // Вывод: Yes

  // Удаление элемента
  myTypeMap.RemoveValue<double>();

  // Попытка получения удаленного элемента
  std::cout << "Value for double after removal: "
            << myTypeMap.GetValue<double>()
            << std::endl;  // Вывод: (некорректное значение)
  return 0;
}
