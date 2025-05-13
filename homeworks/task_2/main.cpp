#include "type_list.hpp"

using MyList = TypeList<int, double, char, long>;

// Размер списка
static_assert(MyList::size() == 4, "Size test failed");

// Получение типа по индексу
static_assert(std::is_same_v<MyList::at<0>, int>, "TypeAt index 0 failed");
static_assert(std::is_same_v<MyList::at<1>, double>, "TypeAt index 1 failed");
static_assert(std::is_same_v<MyList::at<2>, char>, "TypeAt index 2 failed");

// Проверка наличия типа
static_assert(MyList::contains<int>(), "Contains int failed");
static_assert(MyList::contains<double>(), "Contains double failed");
static_assert(!MyList::contains<float>(), "Contains float should be false");

// Получение индекса типа
static_assert(MyList::index_of<int>() == 0, "IndexOf int failed");
static_assert(MyList::index_of<double>() == 1, "IndexOf double failed");
static_assert(MyList::index_of<char>() == 2, "IndexOf char failed");

// Добавление типа в конец
using AppendedList = MyList::append<float>;
static_assert(AppendedList::size() == 5, "Append size failed");
static_assert(std::is_same_v<AppendedList::at<4>, float>, "Append failed");

// Добавление типа в начало
using PrependedList = MyList::prepend<bool>;
static_assert(PrependedList::size() == 5, "Prepend size failed");
static_assert(std::is_same_v<PrependedList::at<0>, bool>, "Prepend failed");

int main() { return 0; }
