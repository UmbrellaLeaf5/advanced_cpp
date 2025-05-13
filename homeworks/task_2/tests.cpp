#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "type_list.hpp"

using SimpleList = TypeList<int, double, char, long>;
using EmptyList = TypeList<>;
using ComplexList =
    TypeList<std::map<int, std::string>, std::vector<std::list<bool>>,
             std::unordered_map<std::vector<std::list<std::string>>, char>>;

// MARK: размер списка

static_assert(EmptyList::Size() == 0, "Empty: Size test failed");

static_assert(SimpleList::Size() == 4, "Simple: Size test failed");

static_assert(ComplexList::Size() == 3, "Complex: Size test failed");

// MARK: тип по индексу

static_assert(std::is_same_v<SimpleList::At<0>, int>,
              "Simple: TypeAt index 0 failed");
static_assert(std::is_same_v<SimpleList::At<1>, double>,
              "Simple: TypeAt index 1 failed");
static_assert(std::is_same_v<SimpleList::At<2>, char>,
              "Simple: TypeAt index 2 failed");
static_assert(std::is_same_v<SimpleList::At<3>, long>,
              "Simple: TypeAt index 3 failed");

static_assert(std::is_same_v<ComplexList::At<0>, std::map<int, std::string>>,
              "Complex: TypeAt index 0 failed");
static_assert(std::is_same_v<ComplexList::At<1>, std::vector<std::list<bool>>>,
              "Complex: TypeAt index 1 failed");
static_assert(
    std::is_same_v<
        ComplexList::At<2>,
        std::unordered_map<std::vector<std::list<std::string>>, char>>,
    "Complex: TypeAt index 2 failed");

// MARK: наличие типа

static_assert(SimpleList::Contains<int>() == true,
              "Simple: Contains int failed");
static_assert(SimpleList::Contains<bool>() == false,
              "Simple: Contains bool failed");
static_assert(SimpleList::Contains<double>() == true,
              "Simple: Contains double failed");
static_assert(SimpleList::Contains<float>() == false,
              "Simple: Contains float failed");
static_assert(SimpleList::Contains<long>() == true,
              "Simple: Contains long failed");

static_assert(EmptyList::Contains<bool>() == false,
              "Empty: Contains int failed");
static_assert(EmptyList::Contains<int>() == false,
              "Empty: Contains int failed");

static_assert(ComplexList::Contains<std::map<int, std::string>>() == true,
              "Complex: Contains std::map<int, std::string> failed");
static_assert(ComplexList::Contains<std::map<long, std::string>>() == false,
              "Complex: Contains std::map<long, std::string> failed");
static_assert(ComplexList::Contains<std::vector<std::list<bool>>>() == true,
              "Complex: Contains std::vector<std::list<bool>> failed");
static_assert(
    ComplexList::Contains<
        std::unordered_map<std::vector<std::list<std::string>>, char>>() ==
        true,
    "Complex: Contains std::unordered_map<std::vector<std::list<std::string>>, "
    "char> failed");
static_assert(ComplexList::Contains<int>() == false,
              "Complex: Contains int failed");
static_assert(ComplexList::Contains<std::string>() == false,
              "Complex: Contains string failed");

// MARK: индекс типа

static_assert(SimpleList::IndexOf<int>() == 0, "Simple: IndexOf int failed");
static_assert(SimpleList::IndexOf<double>() == 1,
              "Simple: IndexOf double failed");
static_assert(SimpleList::IndexOf<char>() == 2, "Simple: IndexOf char failed");
static_assert(SimpleList::IndexOf<long>() == 3, "Simple: IndexOf long failed");

static_assert(ComplexList::IndexOf<std::map<int, std::string>>() == 0,
              "Complex: IndexOf map failed");
static_assert(ComplexList::IndexOf<std::vector<std::list<bool>>>() == 1,
              "Complex: IndexOf vector failed");
static_assert(
    ComplexList::IndexOf<
        std::unordered_map<std::vector<std::list<std::string>>, char>>() == 2,
    "Complex: IndexOf unordered_map failed");

// MARK: тип в конец

using SimpleAppendedList = SimpleList::Append<float>;
static_assert(SimpleAppendedList::Size() == 5, "Simple: Append size failed");
static_assert(std::is_same_v<SimpleAppendedList::At<4>, float>,
              "Simple: Append failed");

using EmptyAppendedList = EmptyList::Append<long>;
static_assert(EmptyAppendedList::Size() == 1, "Empty: Append size failed");
static_assert(std::is_same_v<EmptyAppendedList::At<0>, long>,
              "Empty: Append failed");

using ComplexAppendedList = ComplexList::Append<int>;
static_assert(ComplexAppendedList::Size() == 4, "Complex: Append size failed");
static_assert(std::is_same_v<ComplexAppendedList::At<3>, int>,
              "Complex: Append type failed");

// MARK: тип в начало

using SimplePrependedList = SimpleList::Prepend<bool>;
static_assert(SimplePrependedList::Size() == 5, "Simple: Prepend size failed");
static_assert(std::is_same_v<SimplePrependedList::At<0>, bool>,
              "Simple: Prepend failed");

using EmptyPrependedList = EmptyList::Prepend<char>;
static_assert(EmptyPrependedList::Size() == 1, "Empty: Prepend size failed");
static_assert(std::is_same_v<EmptyPrependedList::At<0>, char>,
              "Empty: Prepend failed");

using ComplexPrependedList = ComplexList::Prepend<int>;
static_assert(ComplexPrependedList::Size() == 4,
              "Complex: Prepend size failed");
static_assert(std::is_same_v<ComplexPrependedList::At<0>, int>,
              "Complex: Prepend type failed");

int main() { return 0; }
