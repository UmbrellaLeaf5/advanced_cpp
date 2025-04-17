#include "circle.hpp"

#include <cmath>

Circle::Circle(double radius) : Shape("circle"), radius_(radius) {}

double Circle::Area() const { return M_PI * radius_ * radius_; }
