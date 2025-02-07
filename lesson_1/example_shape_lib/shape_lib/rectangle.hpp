#pragma once

#include "shape.hpp"

class Rectangle : public Shape {
 public:
  Rectangle(double width, double height);

  double Area() const override;

 private:
  double width_, height_;
};
