#pragma once

#include <iostream>
#include <map>
#include <string>

class Expression {
 public:
  virtual ~Expression() = default;
  virtual void Print() const = 0;
  virtual int Evaluate(const std::map<std::string, int>& variables) const = 0;
};