#pragma once

#include "shape.hpp"

class Circle : public Shape {
 public:
  Circle(double radius);

  double Area() const override;

 private:
  double radius_;
};
