#include "unique_ptr.hpp"
#include "utils.hpp"

class SimpleClass {
 public:
  int a;
  SimpleClass(int a) : a{a} {}
};

class OtherClass {
 public:
  UniquePtr<SimpleClass> val = new SimpleClass(3);
};

int main() {
  UniquePtr<SimpleClass> gl_value = new SimpleClass(7);
  auto other_ptr = new SimpleClass(5);
  // UniquePtr<SimpleClass> other_value = other_ptr;
  // UniquePtr<int> value2 = value;
  auto made_ptr = MakeUnique<SimpleClass>(20);

  const OtherClass smth;
  auto val = smth.val->a;
  // smth.val->a = 7;
  (*smth.val).a = 5;
  (*gl_value).a = 10;
  // value = value2;
  gl_value->a = 6;
}
