#pragma once

#include <compare>

template <typename T>
concept LessThanComparable = requires(const T& a, const T& b) {
  { a < b } -> std::convertible_to<bool>;
};

template <LessThanComparable Derived>
class less_than_comparable {
 public:
  bool operator>(Derived const& other) const {
    return static_cast<Derived const&>(*this) < other;
  }

  bool operator<=(Derived const& other) const {
    return !(static_cast<Derived const&>(*this) > other);
  }

  bool operator>=(Derived const& other) const {
    return !(static_cast<Derived const&>(*this) < other);
  }

  bool operator==(Derived const& other) const {
    return !(static_cast<Derived const&>(*this) < other) &&
           !(other < static_cast<Derived const&>(*this));
  }

  bool operator!=(Derived const& other) const { return !(*this == other); }
};
