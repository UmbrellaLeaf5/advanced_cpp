#pragma once

#include "operator.hpp"

class MultiplyOperator : public Operator {
 public:
  using Operator::Operator;

  void Print() const override {
    std::cout << "(";
    left->Print();
    std::cout << " * ";
    right->Print();
    std::cout << ")";
  }

  int Evaluate(const std::map<std::string, int>& variables) const override {
    return left->Evaluate(variables) * right->Evaluate(variables);
  }
};