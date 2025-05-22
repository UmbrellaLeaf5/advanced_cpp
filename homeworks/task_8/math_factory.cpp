#include "math_factory.hpp"

std::shared_ptr<Variable> MathFactory::GetVariable(const std::string& name) {
  auto it = variables.find(name);
  if (it != variables.end())
    if (auto sp = it->second.lock()) return sp;

  auto var = std::make_shared<Variable>(name);
  variables[name] = var;
  return var;
}

std::shared_ptr<Constant> MathFactory::GetConstant(int value) {
  if (value >= -5 && value <= 256) return constants[value];

  for (const auto& constant : custom_constants)
    if (constant->GetValue() == value) return constant;

  auto constant = std::make_shared<Constant>(value);
  custom_constants.push_back(constant);
  return constant;
}

void MathFactory::DeleteVariable(const std::string& name) {
  auto it = variables.find(name);
  if (it != variables.end() && it->second.expired()) variables.erase(it);
}

void MathFactory::DeleteConstant(int value) {
  if (value >= -5 && value <= 256) return;

  for (auto it = custom_constants.begin(); it != custom_constants.end();)
    if ((*it)->GetValue() == value && it->use_count() == 1) {
      it = custom_constants.erase(it);
      return;
    } else
      ++it;
}
