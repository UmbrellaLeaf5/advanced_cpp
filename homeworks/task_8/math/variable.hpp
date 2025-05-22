#pragma once

#include <stdexcept>

#include "expression.hpp"

class Variable : public Expression {
 public:
  Variable(const std::string& name) : name(name) {}

  void Print() const override { std::cout << name; }

  int Evaluate(const std::map<std::string, int>& variables) const override {
    auto it = variables.find(name);
    if (it != variables.end()) return it->second;

    throw std::runtime_error("Variable " + name + " not found");
  }

  const std::string& GetName() const { return name; }

 private:
  std::string name;
};