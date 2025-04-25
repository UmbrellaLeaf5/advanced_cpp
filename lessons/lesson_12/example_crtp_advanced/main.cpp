#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
class Automobile {
 public:
  void drive() { static_cast<T*>(this)->drive_impl(); }
  // int get_wheels() const {}
  // int get_mass() const {}drive_impl
  Automobile() = default;

 protected:
  ~Automobile() = default;

  // friend void destroy(Automobile<T>*);
};

template <typename T>
void drive_some(std::vector<Automobile<T>*> mobiles) {
  for (auto car : mobiles) {
    car->drive();
  }
}

template <typename T>
void destroy(Automobile<T>* ptr) {
  delete static_cast<T*>(ptr);
}

template <typename T>
class registry {
 public:
  static size_t count;
  static T* head;
  T* next;
  T* prev;

 protected:
  registry() {
    ++count;
    prev = nullptr;
    next = head;
    head = static_cast<T*>(this);
    if (next) next->prev = head;
  }
  registry(const registry&) {
    ++count;
    prev = nullptr;
    next = head;
    head = static_cast<T*>(this);
    if (next) next->prev = head;
  }
  ~registry() {
    --count;
    if (prev) prev->next = next;
    if (next) next->prev = prev;
    if (head == this) head = next;
  }
};

template <typename T>
size_t registry<T>::count(0);

template <typename T>
T* registry<T>::head(nullptr);

class BusForChildren : public Automobile<BusForChildren>,
                       registry<BusForChildren> {
  friend registry<BusForChildren>;

 public:
  void drive_impl() { std::cout << "carefully driving  bus" << std::endl; }
};

int main() {
  // BusForChildren   bus;
  // auto               bus      = new Bus;
  auto bus_ch = new BusForChildren;
  Automobile<BusForChildren>* base_ptr = bus_ch;
  // delete base_ptr;
  base_ptr->drive();
  destroy(base_ptr);

  registry<BusForChildren>::count;

  // delete ptr;

  // std::vector<Automobile<Bus>*> vec;

  // drive_some(vec);
}