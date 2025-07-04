﻿# **Вопросы к зачету**

## **Продвинутое программирование на `С++`, 2025 г.**

## 1. `CMake`. Написать CMake для проекта, состоящего из `main.cpp`, `class1.h`, `class1.cpp`. Стандарт `С++17`.

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(Class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
  main.cpp
  class1.h
  class1.cpp
)
```

## 2. `CMake`. Алгоритм сборки библиотеки без зависимостей из исходных кодов, которые содержат `CMakeLists.txt`.

* CMake configure: (в качестве генератора выбран `Make`)
```bash
cmake -S. -B./build -G "MinGW Makefiles"
```

* Build:
```bash
cmake --build ./build --target all
```
или
```bash
cd build
make
```

## 3. `CMake`. Добавление сторонней прекомпилированной библиотеки к своему проекту.

```cmake
set(MYLIB_PATH "mylib.a")

set(MYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

include_directories(${MYLIB_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${MYLIB_PATH})
```

или

```cmake
add_library(MyLibrary STATIC IMPORTED)

set_target_properties(MyLibrary PROPERTIES
  IMPORTED_LOCATION "mylib.a"
)

set_target_properties(MyLibrary PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} MyLibrary)
```


## 4. `Git`. Отличие `checkout` от `switch`.

### Сокращенное описание команды `git checkout`

`git checkout` позволяет переключаться между ветками, восстанавливать файлы из индекса/указанного коммита, а также отсоединять HEAD.

**Основные варианты использования:**

*   **`git checkout <branch>`:** Переключается на указанную ветку, обновляя индекс и рабочее дерево. Локальные изменения сохраняются. Если ветка не найдена, но есть соответствующая remote tracking branch, предлагает создать локальную ветку, отслеживающую ее.
*   **`git checkout -b <new-branch> [<start-point>]`:** Создает новую ветку и сразу переключается на нее. Можно указать начальную точку для новой ветки.
*   **`git checkout -B <new-branch> [<start-point>]`:** Создает или пересоздает ветку, и переключается на нее.
*   **`git checkout --detach [<branch/commit>]`:** Отсоединяет HEAD от ветки и переключает на указанный коммит или tip ветки, или tip текущей ветки (если не указано).
*   **`git checkout [<tree-ish>] [--] <pathspec>...`:** Перезаписывает файлы в рабочем дереве контентом из индекса (если `<tree-ish>` не указан) или из указанного коммита (`<tree-ish>`).  Флаг `-f` игнорирует неразрешенные конфликты слияния. `--ours` и `--theirs` позволяют выбрать одну из сторон конфликта.
*   **`git checkout (-p|--patch) [<tree-ish>] [--] [<pathspec>...]`:**  Позволяет интерактивно выбирать изменения ("hunks") для восстановления из индекса/коммита.

### Сокращенное описание команды `git switch`

`git switch` переключает рабочее дерево и индекс на указанную ветку. Все новые коммиты будут добавлены к этой ветке.

**Ключевые особенности:**

*   Переключает на указанную ветку.
*   Можно создать новую ветку (`-c`, `-C`).
*   Может автоматически создать ветку из remote tracking branch, если она существует (`--guess`).
*   Можно отсоединить рабочее дерево от любой ветки (`--detach`).
*   Требует чистого индекса и рабочего дерева (без изменений относительно HEAD), если переключение приведет к потере локальных изменений. Для игнорирования этого требования используйте `--discard-changes` или `--merge`.

## 5. `Git`. Отличия `rebase`/`merge`/`cherry-pick`.

**git rebase (перебазирование):**

*   **Что делает:** Перемещает вашу ветку (например, фичу) на другую базу (например, на последнюю версию `master`). Как будто ваша ветка началась позже.
*   **Как работает:** Берет ваши коммиты, отменяет их, а потом заново применяет поверх новой базы.
*   **Особенность:** *Переписывает историю* ветки. Это может быть опасно, если ветку используют другие люди.
*   **Когда использовать:** Чтобы получить чистую, линейную историю. Часто используют для подготовки веток к мержу в `master`.

**git merge (слияние):**

*   **Что делает:** Объединяет изменения из одной ветки в другую.
*   **Как работает:** Создает новый коммит (merge commit), который показывает, как две ветки были объединены.
*   **Особенность:** *Сохраняет историю* ветки, не переписывает ее.
*   **Когда использовать:** Чтобы интегрировать изменения из фичи в `master`, или между другими ветками.  Самый распространенный способ объединения изменений.

**git cherry-pick (выборочное применение):**

*   **Что делает:** Берет изменения *из одного конкретного коммита* и применяет их в другой ветке.
*   **Как работает:** Создает *новый* коммит с теми же изменениями, что и в оригинальном коммите.
*   **Особенность:** *Не перемещает коммит*, а копирует его изменения.  Может привести к дублированию коммитов.
*   **Когда использовать:** Чтобы перенести исправление ошибки из одной ветки в другую, или для выборочного применения изменений. Не для объединения целых веток.

**Проще говоря:**

*   `rebase`: Перемещает целую ветку на новую базу (переписывает историю).
*   `merge`: Объединяет ветки (сохраняет историю).
*   `cherry-pick`: Копирует изменения из одного коммита.

## 6. `Git`. Что нужно сделать, чтобы зафиксировать изменения в локальном репозитории и добавить их в удаленный репозиторий.

```bash
git add .
git commit -m lol

git remote add origin https://github.com/UmbrellaLeaf5/UmbrellaLeaf5
git push origin main
```

## 7. Отличия `waterfall` от `agile`.

## Отличия Waterfall от Agile

**1. Подход к планированию и изменению:**

*   **Waterfall:** Планирование происходит в самом начале проекта, с четко определенной последовательностью этапов.  Требования фиксируются и изменения вносятся крайне неохотно, так как они могут потребовать значительных переделок.  Проект движется линейно: закончился один этап - переходим к следующему.
*   **Agile:**  Гибкий и итеративный подход.  Проект разбивается на небольшие инкременты (спринты). Требования могут меняться в процессе разработки на основе обратной связи от клиента и команды.  Планирование происходит на каждом спринте.

**2. Фокус:**

*   **Waterfall:** Ориентирован на детальное планирование, документацию и предсказуемость. Цель - строгое соответствие первоначальному плану.
*   **Agile:**  Ориентирован на быструю поставку ценности клиенту, адаптацию к изменениям и сотрудничество. Цель - удовлетворение потребностей клиента, даже если они изменились в процессе.

**3. Обратная связь и вовлеченность клиента:**

*   **Waterfall:** Обратная связь от клиента минимальна и происходит в основном в начале и в конце проекта. Клиент не активно вовлечен в процесс разработки.
*   **Agile:**  Клиент активно участвует в проекте, предоставляя обратную связь на каждом спринте.  Команда тесно сотрудничает с клиентом для уточнения требований и оценки прогресса.

**4. Управление рисками:**

*   **Waterfall:** Риски выявляются на этапе планирования и разрабатываются стратегии их смягчения.  Непредвиденные изменения могут серьезно повлиять на успех проекта.
*   **Agile:** Риски снижаются за счет итеративной разработки и постоянной обратной связи.  Команда может быстро адаптироваться к новым вызовам и изменить курс проекта.

**5. Командная работа:**

*   **Waterfall:**  Члены команды обычно работают независимо друг от друга на разных этапах проекта.  Коммуникация часто происходит "сверху вниз".
*   **Agile:**  Команда работает совместно и самоуправляемо.  Коммуникация открытая и частая.  Команда сама решает, как лучше достичь целей спринта.

**6. Когда применять:**

*   **Waterfall:**
    *   Четко определены требования и маловероятны изменения.
    *   Проект имеет фиксированный бюджет и сроки.
    *   Команда имеет большой опыт работы с подобными проектами.
    *   Важна документация и строгий контроль.
    *   Проекты с низким уровнем неопределенности.

*   **Agile:**
    *   Требования могут меняться в процессе разработки.
    *   Важна быстрая поставка ценности клиенту.
    *   Команда имеет опыт работы в Agile.
    *   Необходима гибкость и адаптивность.
    *   Проекты с высоким уровнем неопределенности.

| Характеристика        | Waterfall                                 | Agile                                      |
|----------------------|-------------------------------------------|--------------------------------------------|
| Планирование         | Жесткое, предварительное                 | Гибкое, итеративное                        |
| Изменения           | Ограничены, затруднительны                 | Приветствуются                             |
| Фокус                | Документация, соответствие плану            | Ценность для клиента, адаптивность        |
| Клиент               | Минимальное вовлечение                    | Активное участие                           |
| Риски                 | Выявляются заранее, сложно управлять       | Управляются итеративно, гибкая адаптация |
| Команда               | Независимая работа, иерархическая структура | Совместная работа, самоуправление        |
| Подходит для проектов | С четкими требованиями, стабильных        | С неопределенными требованиями, изменчивых|

## 8. Алгоритм Флойда.

[Алгоритм Кролика и Черепахи](https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A4%D0%BB%D0%BE%D0%B9%D0%B4%D0%B0)

## 9. Инварианты класса. Определение.

Утверждения, которое должно быть верно всё время жизни объекта класса.
В обязанности разработчика входит гарантия сохранения инвариантов объекта в его методах.

## 10. Инкапсуляция. Определение.

(Сокрытие состояния объекта) Механизм, позволяющий регулировать возможность управления состоянием объекта из вне (в частности, для сохранения инвариантов).

## 11. Модификатор доступа в классе по умолчанию. Модификатор доступа в структуре по умолчанию.

В классе по умолчанию `private`:
```cpp
// аналогичные классы:
class A {
 private:
  int var_;
};

class B {
  int var_;
};
```

В структуре по умолчанию `public`:
```cpp
// аналогичные структуры:
struct A {
 public:
  int var;
};

struct B {
  int var;
};
```

## 12. Наследование в классе по умолчанию. Наследование в структуре по умолчанию.

В классе по умолчанию `private`:
```cpp
class Base {
  public:
   void Method() {}
}

// аналогичные классы:
class A : Base {};

class B : private Base {};
```

В структуре по умолчанию `public`:
```cpp
class Base {
  public:
   void Method() {}
}

// аналогичные классы:
struct A : Base {};

struct B : public Base {};
```

## 13. Отличия `private`/`protected`/`public` (внутри определения класса и при наследовании).

* `private` - недоступны извне класса, но доступны внутри (могут использоваться в методах) конкретного экземпляра класса.
* `protected` - недоступны извне класса, но доступны внутри (могут использоваться в методах)конкретного экземпляра класса, а также в наследниках.
* `public` - доступны извне класса.

### Наследование:

* `private`: все `public` и `protected` методы и поля базового класса становятся `private` в рамках производного, `private` - недоступны.
* `protected`: все `public` и `protected` методы и поля базового класса становятся `protected` в рамках производного (то есть могут быть использованы в рамках этого поля), `private` - недоступны.
* `public`: все `public` методы и поля базового класса остаются `public` в рамках производного, `protected` остаются `protected`, `private` - недоступны.

## 14. Отличие `malloc`/`free` от `new`/`delete`.

`new` и `delete` вызывают конструктор и деструктор класса соответственно, в отличие от `malloc` и `free`.

Также последние не являются типобезопасными (компилятором не проверяется соответствие типов и выявляются ошибки на этапе компиляции), требуют приведения после вызова (т.к. возвращают `void*`) и в случае неправильной аллокации памяти, первые выбрасывают исключение `std::bad_alloc`, а вторые возвращают `NULL`.

## 15. Когда не применима инициализация «в круглых скобках», «после =», «фигурная».

* В круглых: в полях класса (компилятор может спутать с объявлением функции, например, инициализация полей по умолчанию).
* В фигурных: при сужении типа
* Через `=`: при explicit конструкторе

## 16. Сужающие преобразованию и разные виды инициализации («в круглых скобках», «после =», «фигурная»).
## 17. «Наиболее неприятный анализ» в `С++` и разные виды инициализации («в круглых скобках», «фигурная»).
## 18. В каких случаях возникает двойная инициализация? Как избежать?
## 19. В каком порядке выполняется инициализация полей класса с использованием списков инициализации (в порядке расположения полей класса или в порядке, определенном в списке инициализации)? 
## 20. Что такое `RVO`? Пример?
## 21. Полиморфизм. Определение. Виды полиморфизма.
## 22. Примеры статического полиморфизма в `С++`.
## 23. Примеры динамического полиморфизма в `С++`.
## 24. Отличие `overloading` от `overriding`.
## 25. Ключевое слово `virtual`.
## 26. Ключевое слово `override`.
## 27. Абстрактный класс. Определение.
## 28. Использование аргументов со значениями по умолчанию в виртуальных функциях.
## 29. `NVI`. Пример?
## 30. Может ли существовать шаблон виртуального метода?
## 31. Можно ли перегружать виртуальные функции?
## 32. Как добавить в `overloading set` класса-наследника методы базового класса, являющиеся перегрузками виртуального метода?
## 33. Чем плох `goto`?

![](./podaruev.png)

## 34. Примеры `goto` - маскирующих конструкций
## 35. `RAII`. Концепция.
## 36. Инвариант умного указателя с единственным(уникальным) владением.
## 37. `Drill down behavior`. Где применяется?
## 38. `Lvalue` и `rvalue`. Отличия.
## 39. `Rvalue` ссылки.
## 40. Что делает `std::move`?
## 41. Правило нуля, трех, пяти.
## 42. Виды умных указателей.
## 43. Отличие `unique_ptr` от `shared_ptr`.
## 44. Отличие `weak_ptr` от `shared_ptr`.
## 45. Способы инициализации `shared_ptr`. 
## 46. `ODR`.
## 47. `Include guards`.
## 48. `CV`-квалификаторы при выводе типов.
## 49. Манглирование имен. (Как перегрузки функций представляются компилятором).
## 50. Правила разрешения перегрузки для нешаблонных функций.
## 51. Правила разрешения перегрузки для шаблонных функций.
## 52. Что такое специализация шаблонного класса?
## 53. Что такое частичная специализация шаблонного класса?
## 54. Правила вывода типов для `auto`.
## 55. Что делает `decltype`?
## 56. Когда используем `auto`, а когда `decltype` для вывода типов?
## 57. Когда `С++` осуществляет «ленивые», а не «энергичные» вычисления?
## 58. SFINAE. Определение.
## 59. Зачем в старом `С++` (до `С++11`) для реализации `SFINAE` создавались структуры разных размеров?
## 60. Замена структурам разных размеров в современном `С++`.
## 61. `CRTP`. Определение. Зачем нужно?
## 62. Ограничения `CRTP`.
## 63. Реализация чисто виртуальных функций в `CRTP`.
## 64. Реализация виртуальных функций в `CRTP`.
## 65. Реализация методов для удаления объекта класса в `CRTP`.
## 66. Способы применения `CRTP`.
## 67. Как применяется `CRTP` для делегирования?
## 68. Как работает ключевое слово `required`? Когда проверятся ограничения?
## 69. Чем плохи `SFINAE` ограничения? Приведите пример.
## 70. Что такое `requires-expression`? Отличия `required-expression` от `required-clause`.
## 71. Виды `requires-expression`.
## 72. Что такое концепт? Особенности синтаксиса ограничения функций концептами.
## 73. Отношения между концептами.
## 74. Напишите концепт `Hashable`, принимающий одну шаблонную переменную `T`, который будет использоваться для проверки: существования типа `std::hash<T>`, существования `std::hash<T>::operator()` и приводимости типа возвращаемого значения `std::hash<T>::operator()` к `std::size_t`.
## 75. Универсальные ссылки и идеальная передача.
## 76. Функции `std::move` и `std::forward`.
## 77. Пачки параметров. Как выделить паттерн раскрытия? Что такое свертки?
## 78. Паттерн Декоратор.
## 79. Применение `CRTP` при реализации паттерна Декоратор.
## 80. Паттерн Адаптер.
## 81. Минусы паттерна декоратор при реализации потокобезопасной очереди.
## 82. Отличие паттерна декоратор от паттерна Адаптер.
## 83. Паттерн Фабрика.
## 84. Как реализовать фабрику для инициализации объектов с разными аргументами в их конструкторах?
## 85. Как реализовать полиморфное копирование с использованием фабрики?
## 86. Зачем использовать `CRTP` в реализации полиморфного копирования с использованием фабрики?
## 87. Паттерн Мост.
## 88. `COW`: достоинства и недостатки.
## 89. Паттерн Компоновщик.
## 90. Паттерн Строитель.


# P.S. мне лень было ответы на все вопросы расписывать, давайте сами как-нибудь :)
