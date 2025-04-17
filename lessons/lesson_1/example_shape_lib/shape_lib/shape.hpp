#pragma once

#include <string>

class Shape {
 public:
  Shape(std::string name) : name_(std::move(name)) {}

  virtual double Area() const = 0;

 protected:
  std::string name_;
};
