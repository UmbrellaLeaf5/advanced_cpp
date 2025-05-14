#include <cassert>
#include <iostream>
#include <stdexcept>

#include "counter.hpp"
#include "less_than_comparable.hpp"

class Number : public LessThanComparableCRTP<Number>,
               public CounterCRTP<Number> {
 public:
  Number(int value) : value_{value} {}

  int Value() const { return value_; }

  bool operator<(const Number& other) const { return value_ < other.Value(); }

 private:
  int value_;
};

class NumberAdvanced : public LessThanComparableCRTP<NumberAdvanced>,
                       public CounterCRTP<NumberAdvanced> {
 public:
  NumberAdvanced() : value_{0} {}
  NumberAdvanced(int value) : value_{value} {}

  NumberAdvanced(const NumberAdvanced& other)
      : CounterCRTP<NumberAdvanced>(other), value_{other.Value()} {}

  NumberAdvanced(NumberAdvanced&& other) noexcept : value_{other.Value()} {
    // other.value_ = 0;
  }

  int Value() const { return value_; }

  ~NumberAdvanced() = default;

  bool operator<(const NumberAdvanced& other) const {
    return value_ < other.Value();
  }

  NumberAdvanced& operator=(const NumberAdvanced& other) {
    if (this != &other) value_ = other.Value();

    return *this;
  }

  NumberAdvanced& operator=(NumberAdvanced&& other) noexcept {
    if (this != &other) {
      value_ = other.Value();
      // other.value_ = 0;
    }

    return *this;
  }

  NumberAdvanced operator+(const NumberAdvanced& other) const {
    return NumberAdvanced(value_ + other.Value());
  }

  NumberAdvanced& operator+=(const NumberAdvanced& other) {
    value_ += other.Value();
    return *this;
  }

  NumberAdvanced operator-(const NumberAdvanced& other) const {
    return NumberAdvanced(value_ - other.Value());
  }

  NumberAdvanced& operator-=(const NumberAdvanced& other) {
    value_ -= other.Value();
    return *this;
  }

  NumberAdvanced operator*(const NumberAdvanced& other) const {
    return NumberAdvanced(value_ * other.Value());
  }

  NumberAdvanced& operator*=(const NumberAdvanced& other) {
    value_ *= other.Value();
    return *this;
  }

  NumberAdvanced operator/(const NumberAdvanced& other) const {
    if (other.Value() == 0) throw std::runtime_error("Division by zero");

    return NumberAdvanced(value_ / other.Value());
  }

  NumberAdvanced& operator/=(const NumberAdvanced& other) {
    if (other.Value() == 0) throw std::runtime_error("Division by zero");

    value_ /= other.Value();
    return *this;
  }

  NumberAdvanced operator-() const { return NumberAdvanced(-value_); }

 private:
  int value_;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};

  assert(one >= one);
  assert(three <= four);
  assert(two == two);
  assert(three > two);
  assert(one < two);

  std::cout << "Count Number: " << CounterCRTP<Number>::Count() << std::endl;

  NumberAdvanced one_a{1};
  NumberAdvanced two_a;
  two_a = one_a * 2;

  NumberAdvanced three_a = one_a;
  three_a += two_a;

  auto four_a = one_a * 8 / two_a;

  assert(one_a >= one_a);
  assert(three_a <= four_a);
  assert(two_a == two_a);
  assert(three_a > two_a);
  assert(one_a < two_a);

  std::cout << "Count NumberAdvanced: " << CounterCRTP<NumberAdvanced>::Count()
            << std::endl;

  return 0;
}
