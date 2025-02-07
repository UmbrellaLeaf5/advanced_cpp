#include "triangle.hpp"

#include <cmath>

Triangle::Triangle(double a, double b, double c)
    : Shape("triangle"), a_(a), b_(b), c_(c) {};

double Triangle::Area() const {
  double p = 0.5 * (a_ + b_ + c_);
  return sqrt(p * (p - a_) * (p - b_) * (p - c_));
}