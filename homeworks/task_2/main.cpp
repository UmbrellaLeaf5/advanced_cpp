#include <string>
#include <vector>

#include "type_list.hpp"

using MyList = TypeList<int, double, char, long>;

// Размер списка
static_assert(MyList::Size() == 4, "Size test failed");

// Получение типа по индексу
static_assert(std::is_same_v<MyList::At<0>, int>, "TypeAt index 0 failed");
static_assert(std::is_same_v<MyList::At<1>, double>, "TypeAt index 1 failed");
static_assert(std::is_same_v<MyList::At<2>, char>, "TypeAt index 2 failed");

// Проверка наличия типа
static_assert(MyList::Contains<int>() == true, "Contains int failed");
static_assert(MyList::Contains<double>() == true, "Contains double failed");
static_assert(!MyList::Contains<float>() == true,
              "Contains float should be false");

// Получение индекса типа
static_assert(MyList::IndexOf<int>() == 0, "IndexOf int failed");
static_assert(MyList::IndexOf<double>() == 1, "IndexOf double failed");
static_assert(MyList::IndexOf<char>() == 2, "IndexOf char failed");

// Добавление типа в конец
using AppendedList = MyList::Append<float>;
static_assert(AppendedList::Size() == 5, "Append size failed");
static_assert(std::is_same_v<AppendedList::At<4>, float>, "Append failed");

// Добавление типа в начало
using PrependedList = MyList::Prepend<bool>;
static_assert(PrependedList::Size() == 5, "Prepend size failed");
static_assert(std::is_same_v<PrependedList::At<0>, bool>, "Prepend failed");

using Empty = TypeList<>;
static_assert(Empty::Size() == 0, "Size test failed");

static_assert(Empty::Contains<bool>() == false, "Contains int failed");
static_assert(Empty::Contains<int>() == false, "Contains int failed");

using EmptyPrependedList = Empty::Prepend<bool>;
static_assert(EmptyPrependedList::Size() == 1, "Prepend size failed");
static_assert(std::is_same_v<EmptyPrependedList::At<0>, bool>,
              "Prepend failed");

int main() { return 0; }
