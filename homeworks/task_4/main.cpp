#include <cassert>
#include <iostream>

#include "counter.hpp"
#include "less_than_comparable.hpp"

class Number : public less_than_comparable<Number>, public counter<Number> {
 public:
  Number(int value) : value_{value} {}

  int value() const { return value_; }

  bool operator<(Number const& other) const { return value_ < other.value_; }

 private:
  int value_;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};

  // assert(one >= one);
  // assert(three <= four);
  // assert(two == two);
  // assert(three > two);
  assert(one < two);

  std::cout << "Count: " << counter<Number>::count() << std::endl;
  return 0;
}
