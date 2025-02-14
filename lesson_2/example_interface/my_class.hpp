#pragma once

#include <iostream>

// MARK: virtual ~

class MyClassInterface {
 public:
  virtual void Func() = 0;

  MyClassInterface() {}
  virtual ~MyClassInterface() { std::cout << "MyClassInterface" << std::endl; }
};

class DerivedClass : public MyClassInterface {
 public:
  // virtual тут необязательна
  void virtual Func() override {}

  DerivedClass() {}
  ~DerivedClass() { std::cout << "DerivedClass" << std::endl; }
};

// MARK: CRTP

template <typename T>
class CRTPBase {
 public:
  void f() { static_cast<T*>(this)->g(); }
};

class CRTPDerived : public
                    /* семантический прикол */
                    CRTPBase<CRTPDerived> {
 public:
  void g() {
    a = 0;
    std::cout << "a: " << a << std::endl;
  }

  int a;
};

class CRTPDerivedOther : public CRTPBase<CRTPDerivedOther> {
 public:
  // void g() {
  //   a = 5.0;
  //   std::cout << "a: " << a << std::endl;
  // }
  float a;
};

// MARK: Агрегатная инициализация

struct Simple {
  int a;
  float b;
};

Simple SimpleAggregation() {
  Simple s = {4, 5.7};
  Simple s_1 = {.a = 4, .b = 5.7};

  // только совпадающий порядок!
  // Simple s_1 = {.b = 5.7, .a = 4};

  return s_1;
}
