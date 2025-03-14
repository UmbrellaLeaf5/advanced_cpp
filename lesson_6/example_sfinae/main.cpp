#include "utils.hpp"

class Simple {
 public:
  Simple(int var) : var_(var) {}
  bool DoSomething() const { return true; }
  bool DoSomething2() const { return var_ > 2; }

 private:
  int var_;
};

inline bool SimpleDoSomething(Simple* s) { return s->DoSomething(); }

inline float KahanSummation(float sum_previous, float input,
                            float& accumulator) {
  IC(sum_previous, input, accumulator);

  ICDouble(sum_previous);
  ICDouble(input);
  ICDouble(accumulator);

  const float y = input - accumulator;
  ICDouble(y);

  const float t = sum_previous + y;
  ICDouble(t);

  accumulator = (t - sum_previous) - y;

  ICDouble(t - sum_previous);
  ICDouble(accumulator);

  return t;
}

int main() {
  bool b_1 = true;
  bool b_2 = false;

  int a = 10;
  auto* ptr = new Simple(a);
  delete ptr;

  ptr = nullptr;

  if (b_1 && b_2) {
  }

  ptr->DoSomething();  // пока метод не затрагивает поля класса, его можно
                       // вызывать даже с nullptr

  // std::cout <<
  ptr->DoSomething2();  // с -O2 компилятор вырезает эту строку, иначе это seg
                        // fault
  //  << std::endl;

  // if (ptr && ptr->DoSomething()) {
  // }

  auto accumulator = 0.F;
  auto kh_s = KahanSummation(10.33F, 0.47F, accumulator);
  ICDouble(kh_s);

  return 0;
}
