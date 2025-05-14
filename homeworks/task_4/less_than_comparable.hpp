#pragma once

// template <typename T>
// concept LessThanComparable = requires(const T& a, const T& b) {
//   { a < b } -> std::convertible_to<bool>;
// };

template <typename Derived>
class LessThanComparableCRTP {
 public:
  bool operator>(const Derived& other) const {
    return other < static_cast<const Derived&>(*this);
  }

  bool operator<=(const Derived& other) const {
    return !(other < static_cast<const Derived&>(*this));
  }

  bool operator>=(const Derived& other) const {
    return !(other > static_cast<const Derived&>(*this));
  }

  bool operator==(const Derived& other) const {
    return (other <= static_cast<const Derived&>(*this)) &&
           (other >= static_cast<const Derived&>(*this));
  }

  bool operator!=(const Derived& other) const { return !(*this == other); }
};
