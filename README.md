# Advanced programming in C++

templated: generated from [UmbrellaLeaf5/template_cpp_lessons](https://github.com/UmbrellaLeaf5/template_cpp_lessons)

## Краткое описание

Это репозиторий с моими домашними и семинарскими работами по этому курсу, который в 2025 году читался в четвертом семестре на ПИШ ФАЛТ МФТИ.

## О CMake

Под CMake тут настроены и домашние работы, и семинарские занятия (активно используя `file(GLOB)`).
Также тут используется библиотека [`icecream-cpp`](https://github.com/renatoGarcia/icecream-cpp), так что клонируйте репозиторий следующим образом:

```
git clone --recurse-submodules https://github.com/UmbrellaLeaf5/advanced_cpp
```

или

```
git clone https://github.com/UmbrellaLeaf5/advanced_cpp
git submodule init
git submodule update
```

А далее CMake вам выдаст `WARNING` с требованием произвести `install` для этой библиотеки.
