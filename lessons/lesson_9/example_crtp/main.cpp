#include "utils.hpp"

template <typename T>
class BaseCRTP {
 protected:
  int i = 0;

 public:
  void action(int add) {
    std::cout << "base action " << i << "\n";
    static_cast<T*>(this)->action_impl(add);
    std::cout << "after action " << i << "\n";
  }
  void action_impl([[maybe_unused]] int add) {}

 protected:
  ~BaseCRTP() {};
};

template <typename T>
class Singleton {
 public:
  static T& instance() {
    static T inst;
    return inst;
  }
};

class B : public Singleton<B> {
 public:
  void f() {};
};

template <typename T>
void apply(BaseCRTP<T>* ptr, int add) {
  ptr->action(add);
}

template <typename T>
void destroy(BaseCRTP<T>* ptr) {
  delete static_cast<T*>(ptr);
}

class DerivedCRTP : public BaseCRTP<DerivedCRTP> {
 public:
  void action_impl(int add) {
    i += add;
    std::cout << "action" << "\n";
  }
};

class A {};

class OtherDerivedCRTP : public BaseCRTP<OtherDerivedCRTP> {
  A* ptr = nullptr;

 public:
  OtherDerivedCRTP() : ptr(new A) { std::cout << "Ctr" << "\n"; }
  ~OtherDerivedCRTP() {
    delete ptr;
    ptr = nullptr;
    std::cout << "Dtr" << "\n";
  }
  //     void action(int add) {
  //         i -= add;
  //         std::cout << " other action " << "\n";
  //     }action
};

int main() {
  DerivedCRTP derived;
  BaseCRTP<DerivedCRTP>* ptr = &derived;

  // OtherDerivedCRTP            other;
  BaseCRTP<OtherDerivedCRTP>* ptr2 = new OtherDerivedCRTP;

  ptr->action(5);
  ptr2->action(50);

  // apply(&derived, 5);
  // apply(&other, 5);
  B::instance().f();
  destroy(ptr2);
  // delete ptr2;
}
