#pragma once

#include <unordered_map>
#include <vector>

#include "math/constant.hpp"
#include "math/operators.hpp"
#include "math/variable.hpp"

class MathFactory {
 public:
  MathFactory(const MathFactory&) = delete;
  MathFactory& operator=(const MathFactory&) = delete;

  static MathFactory& GetInstance() {
    static MathFactory instance;
    return instance;
  }

  std::shared_ptr<Variable> GetVariable(const std::string& name);
  std::shared_ptr<Constant> GetConstant(int value);

  void DeleteVariable(const std::string& name);
  void DeleteConstant(int value);

 private:
  MathFactory() {
    for (int i = -5; i <= 256; ++i)
      constants[i] = std::make_shared<Constant>(i);
  };

  ~MathFactory() = default;

  std::unordered_map<std::string, std::weak_ptr<Variable>> variables;
  std::unordered_map<int, std::shared_ptr<Constant>> constants;
  std::vector<std::shared_ptr<Constant>> custom_constants;
};
