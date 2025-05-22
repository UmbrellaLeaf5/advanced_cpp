#include <iostream>
#include <memory>
#include <vector>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main() {
  // Rectangle rectangle(10, 20);
  // std::cout << rectangle.area() << "\n";
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.emplace_back(new Rectangle(20, 30));
  shapes.emplace_back(new Circle(5));
  shapes.emplace_back(new Triangle(3, 4, 5));
  //  = {
  //     std::make_unique<Rectangle>(20, 10),
  //     std::make_unique<Circle>(10),
  //     std::make_unique<Triangle>(3, 4, 5)
  // };

  double area = 0;
  for (const auto& shape : shapes) area += shape->Area();

  std::cout << area << "\n";

  return 0;
}
