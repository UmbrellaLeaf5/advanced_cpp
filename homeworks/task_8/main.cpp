#include "math_factory.hpp"

int main() {
  auto& factory = MathFactory::GetInstance();

  auto two = factory.GetConstant(2);
  auto three = factory.GetConstant(3);
  auto x = factory.GetVariable("x");
  auto y = factory.GetVariable("y");

  auto expression = std::make_shared<MultiplyOperator>(
      std::make_shared<DivideOperator>(
          std::make_shared<AddOperator>(two, y),
          std::make_shared<SubtractOperator>(x, three)),
      x);

  std::cout << "Expression: ";
  expression->Print();
  std::cout << std::endl;

  std::map<std::string, int> variables = {{"x", 5}, {"y", 8}};
  int result = expression->Evaluate(variables);

  std::cout << "Result when x = 5, y = 8: " << result << std::endl;

  return 0;
}