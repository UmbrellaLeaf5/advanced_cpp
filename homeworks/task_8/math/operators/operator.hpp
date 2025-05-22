#pragma once

#include <memory>

#include "../expression.hpp"

class Operator : public Expression {
 public:
  Operator(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : left(l), right(r) {}

 protected:
  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;
};
