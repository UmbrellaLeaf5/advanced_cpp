#pragma once

#include "operator.hpp"

class DivideOperator : public Operator {
 public:
  using Operator::Operator;

  void Print() const override {
    std::cout << "(";
    left->Print();
    std::cout << " / ";
    right->Print();
    std::cout << ")";
  }

  int Evaluate(const std::map<std::string, int>& variables) const override {
    int rightValue = right->Evaluate(variables);
    if (rightValue == 0) throw std::runtime_error("Division by zero");

    return left->Evaluate(variables) / rightValue;
  }
};