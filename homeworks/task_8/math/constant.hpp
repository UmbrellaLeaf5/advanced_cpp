#pragma once

#include "expression.hpp"

class Constant : public Expression {
 public:
  Constant(int value) : value(value) {}

  void Print() const override { std::cout << value; }

  int Evaluate(const std::map<std::string, int>&) const override {
    return value;
  }

  int GetValue() const { return value; }

 private:
  int value;
};