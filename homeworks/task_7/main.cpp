#include "variety.hpp"

int main() {
  Variety<int> set_1(5);  // Порог 5, начальная емкость массива 10

  set_1.Add(1);
  set_1.Add(2);
  set_1.Add(3);
  std::cout << set_1;  // Implementation: ArraySet

  set_1.Add(4);
  set_1.Add(5);
  set_1.Add(6);
  std::cout << set_1;  // Implementation: HashSet

  Variety<int> set_2(5);
  set_2.Add(5);
  set_2.Add(7);
  set_2.Add(8);

  auto union_set = set_1.UnionSets(set_2);
  std::cout << *union_set;  // Implementation: HashSet (т.к. размер > threshold)

  auto intersection_set = set_1.IntersectionSets(set_2);
  std::cout << *intersection_set;  // Implementation: HashSet or ArraySet
                                   // depending on intersection size

  return 0;
}
