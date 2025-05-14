#pragma once

template <typename Derived>
class CounterCRTP {
 public:
  CounterCRTP() { count_++; }
  CounterCRTP(const CounterCRTP&) { count_++; }
  CounterCRTP(CounterCRTP&&) noexcept { count_++; }

  CounterCRTP& operator=(const CounterCRTP&) { count_++; }
  CounterCRTP& operator=(CounterCRTP&&) noexcept { count_++; }

  ~CounterCRTP() { count_--; }

  static int Count() { return count_; }

 private:
  inline static int count_ = 0;
};
