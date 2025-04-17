# Lesson 3: 21.02.2025

SFINAE: Substitution failure is not an error

Пример, когда clang выводит более понятные сообщения:

g++:
```log
[build] In file included from C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:1:
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\unique_ptr.hpp: In instantiation of 'UniquePtr<T> MakeUnique(Args ...) [with T = SimpleClass; Args = {}]':
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:22:42:   required from here
[build]    22 |   auto made_ptr = MakeUnique<SimpleClass>();
[build]       |                   ~~~~~~~~~~~~~~~~~~~~~~~^~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\unique_ptr.hpp:32:23: error: no matching function for call to 'SimpleClass::SimpleClass()'
[build]    32 |   return UniquePtr<T>{new T(args...)};
[build]       |                       ^~~~~~~~~~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:7:3: note: candidate: 'SimpleClass::SimpleClass(int)'
[build]     7 |   SimpleClass(int a) : a{a} {}
[build]       |   ^~~~~~~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:7:3: note:   candidate expects 1 argument, 0 provided
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note: candidate: 'constexpr SimpleClass::SimpleClass(const SimpleClass&)'
[build]     4 | class SimpleClass {
[build]       |       ^~~~~~~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note:   candidate expects 1 argument, 0 provided
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note: candidate: 'constexpr SimpleClass::SimpleClass(SimpleClass&&)'
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note:   candidate expects 1 argument, 0 provided
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\unique_ptr.hpp:32:37: error: no matching function for call to 'UniquePtr<SimpleClass>::UniquePtr(<brace-enclosed initializer list>)'
[build]    32 |   return UniquePtr<T>{new T(args...)};
[build]       |                                     ^
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\unique_ptr.hpp:5:3: note: candidate: 'UniquePtr<T>::UniquePtr(T*&&) [with T = SimpleClass]'
[build]     5 |   UniquePtr(T*&& ptr) : ptr_(ptr) {}
[build]       |   ^~~~~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\unique_ptr.hpp:5:3: note:   conversion of argument 1 would be ill-formed:
[build] mingw32-make[3]: *** [lesson_3\CMakeFiles\lesson_3_example_unique_ptr.dir\build.make:79: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/example_unique_ptr/main.cpp.obj] Error 1
[build] mingw32-make[2]: *** [CMakeFiles\Makefile2:316: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/all] Error 2
[build] mingw32-make[1]: *** [CMakeFiles\Makefile2:323: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/rule] Error 2
[build] mingw32-make: *** [Makefile:162: lesson_3_example_unique_ptr] Error 2
[proc] The command: C:\Program_Files\MSYS2\mingw64\bin\cmake.EXE --build c:/UL/Programs/C++/semesters/4/advanced_cpp/build --config Debug --target lesson_3_example_unique_ptr -j 18 -- exited with code: 2
[driver] Build completed: 00:00:01.554
[build] Build finished with exit code 2
```

clang
```log
[build] In file included from C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:1:
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr/unique_ptr.hpp:32:27: error: no matching constructor for initialization of 'SimpleClass'
[build]    32 |   return UniquePtr<T>{new T(args...)};
[build]       |                           ^
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:22:19: note: in instantiation of function template specialization 'MakeUnique<SimpleClass>' requested here
[build]    22 |   auto made_ptr = MakeUnique<SimpleClass>();
[build]       |                   ^
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:7:3: note: candidate constructor not viable: requires single argument 'a', but no arguments were provided
[build]     7 |   SimpleClass(int a) : a{a} {}
[build]       |   ^           ~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note: candidate constructor (the implicit copy constructor) not viable: requires 1 argument, but 0 were provided
[build]     4 | class SimpleClass {
[build]       |       ^~~~~~~~~~~
[build] C:\UL\Programs\C++\semesters\4\advanced_cpp\lesson_3\example_unique_ptr\main.cpp:4:7: note: candidate constructor (the implicit move constructor) not viable: requires 1 argument, but 0 were provided
[build]     4 | class SimpleClass {
[build]       |       ^~~~~~~~~~~
[build] 3 warnings and 1 error generated.
[build] mingw32-make[3]: *** [lesson_3\CMakeFiles\lesson_3_example_unique_ptr.dir\build.make:79: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/example_unique_ptr/main.cpp.obj] Error 1
[build] mingw32-make[2]: *** [CMakeFiles\Makefile2:316: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/all] Error 2
[build] mingw32-make[1]: *** [CMakeFiles\Makefile2:323: lesson_3/CMakeFiles/lesson_3_example_unique_ptr.dir/rule] Error 2
[build] mingw32-make: *** [Makefile:162: lesson_3_example_unique_ptr] Error 2
[proc] The command: C:\Program_Files\MSYS2\mingw64\bin\cmake.EXE --build c:/UL/Programs/C++/semesters/4/advanced_cpp/build --config Debug --target lesson_3_example_unique_ptr -j 18 -- exited with code: 2
[driver] Build completed: 00:00:01.961
[build] Build finished with exit code 2
```