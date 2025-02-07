#include "rectangle.hpp"

Rectangle::Rectangle(double width, double height)
    : Shape("rectangle"), width_(width), height_(height) {}

double Rectangle::Area() const { return width_ * height_; }