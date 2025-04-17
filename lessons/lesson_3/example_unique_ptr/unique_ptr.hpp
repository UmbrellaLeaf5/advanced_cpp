
template <typename T>
class UniquePtr {
 public:
  UniquePtr(T*&& ptr) : ptr_(ptr) {}

  // UniquePtr(T* ptr) : ptr_(ptr) {}
  // UniquePtr(T* ptr) : ptr_{ptr} {}
  // разница между фигурными скобками: () - вызов конструктора
  // а так это агрегатная инициализация

  // иногда компилятор путался и вызывал функцию ptr_(T* ptr),
  // поэтому добавили возможность через {}

  // но в списке инициализации компилятор знает,
  // что происходит только вызов конструктора, так что он не путается

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&&) = delete;

  T* operator->() { return ptr_; }
  const T* operator->() const { return ptr_; }
  // T* operator->() const { return ptr_; }
  T& operator*() const { return *ptr_; }

 private:
  T* ptr_;
};

template <typename T, typename... Args>
inline UniquePtr<T> MakeUnique(Args... args) {
  return UniquePtr<T>{new T(args...)};
}