#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "type_list.hpp"

template <typename... Types>
class TypeMap {
 private:
  using TypeList_ = TypeList<Types...>;
  using VariantType_ = std::variant<Types...>;

  std::vector<std::pair<bool, VariantType_>> data_;

  template <typename Type>
  static constexpr size_t GetIndex_() {
    return TypeList_::template IndexOf<Type>();
  }

 public:
  TypeMap() : data_(TypeList_::Size()) {}

  template <typename Type>
  void SetValue(const Type& value) {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::SetValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();

    data_[index].second = value;
    data_[index].first = true;
  }

  template <typename Type>
  const Type& GetValue() const {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::GetValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();

    if (!data_[index].first)
      throw std::runtime_error("TypeMap::GetValue: Value not initialized.");

    return std::get<Type>(data_[index].second);
  }

  template <typename Type>
  bool Contains() const {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::Contains: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    return data_[index].first;
  }

  template <typename Type>
  void RemoveValue() {
    static_assert(TypeList_::template Contains<Type>(),
                  "TypeMap::RemoveValue: Type not found in TypeList.");

    size_t index = GetIndex_<Type>();
    data_[index].first = false;
    data_[index].second = VariantType_{};
  }
};
