#pragma once

#include <type_traits>
#include <utility>
#include <vector>

#include "type_list.hpp"  // Assuming TypeList.h is in the same directory or
                          // accessible

template <typename... Types>
class TypeMap {
 private:
  using TypeList_ = TypeList<Types...>;
  using DataVector =
      std::vector<std::pair<size_t, std::aligned_union_t<0, Types...>>>;
  DataVector data_;

  template <typename T>
  static constexpr size_t GetIndex() {
    return TypeList_::template IndexOf<T>();
  }

 public:
  TypeMap() : data_(TypeList_::Size()) {}

  template <typename T>
  void AddValue(const T& value) {
    static_assert(TypeList_::template Contains<T>(),
                  "TypeMap::AddValue: Type not found in TypeList");

    size_t index = GetIndex<T>();
    new (&data_[index].second) T(value);
    data_[index].first = 1;  // Flag to indicate valid data
  }

  template <typename T>
  T& GetValue() {
    static_assert(TypeList_::template Contains<T>(),
                  "TypeMap::GetValue: Type not found in TypeList");

    size_t index = GetIndex<T>();
    return *reinterpret_cast<T*>(&data_[index].second);
  }

  template <typename T>
  const T& GetValue() const {
    static_assert(TypeList_::template Contains<T>(),
                  "TypeMap::GetValue: Type not found in TypeList");

    size_t index = GetIndex<T>();
    return *reinterpret_cast<const T*>(&data_[index].second);
  }

  template <typename T>
  bool Contains() const {
    static_assert(TypeList_::template Contains<T>(),
                  "TypeMap::Contains: Type not found in TypeList");

    size_t index = GetIndex<T>();
    return data_[index].first == 1;
  }

  template <typename T>
  void RemoveValue() {
    static_assert(TypeList_::template Contains<T>(),
                  "TypeMap::RemoveValue: Type not found in TypeList");

    size_t index = GetIndex<T>();
    if (data_[index].first == 1) {
      using Type = T;
      reinterpret_cast<Type*>(&data_[index].second)->~Type();
      data_[index].first = 0;
    }
  }

  // ~TypeMap() {
  //   for (size_t i = 0; i < TypeList_::Size(); ++i) {
  //     if (data_[i].first == 1) {
  //       using Type = typename TypeList_::At<i>;
  //       reinterpret_cast<Type*>(&data_[i].second)->~Type();
  //     }
  //   }
  // }
};
