#pragma once

#include "shape.hpp"

class Triangle : public Shape {
 public:
  Triangle(double a, double b, double c);

  double Area() const override;

 private:
  double a_, b_, c_;
};
