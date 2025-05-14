#pragma once

template <typename Derived>
class counter {
 public:
  counter() { ++count_; }
  counter(const counter&) { ++count_; }
  counter(counter&&) noexcept { ++count_; }

  ~counter() { --count_; }

  static int count() { return count_; }

 private:
  inline static int count_ = 0;
};
