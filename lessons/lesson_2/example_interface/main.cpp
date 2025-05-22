#include "my_class.hpp"

int main() {
  DerivedClass *d = new DerivedClass();
  // оба деструктора: DerivedClass, потом MyClassInterface
  delete d;

  std::cout << "\n";

  MyClassInterface *mci = new DerivedClass();
  // только MyClassInterface (если нет виртуального конструктора)
  delete mci;

  // CRTPDerivedOther crtp;
  // crtp.f(); не работает, при подстановке шаблона не находится метода g

  // CRTPBase<int> *ptri;
  // ptri->f(); у int даже static_cast не работает

  return 0;
}
