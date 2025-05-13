# Task 4: Операторные `MixIn`

1) Реализуете `MixIn` класс `less_then_comparable`, который при помощи CRTP "подмешивает" в целевой класс операторы сравнения (`>`, `<=`, `>=`, `==`, `!=`).
2) Реализуйте `MixIn` класс `counter`, который обеспечивает возможность подсчета созданных экземпляров целевого класса.

Пример использования созданных `MixIn`:
```cpp
class Number : public less_than_comparable<Number>, public counter<Number> {
 public:
  Number(int value) : m_value{value} {}

  int value() const { return m_value; }

  bool operator<(Number const& other) const { return m_value < other.m_value; }

 private:
  int m_value;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};

  assert(one >= one);
  assert(three <= four);
  assert(two == two);
  assert(three > two);
  assert(one < two);

  std::cout << "Count: " << counter<Number>::count() << std::endl;
  return 0;
}
```

(тут не нужен список экземпляров)
