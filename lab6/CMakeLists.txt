cmake_minimum_required(VERSION 3.10)
project(lab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

add_executable(lab6
        include/dragon.h
        include/factory.h
        include/frog.h
        include/knight.h
        include/npc.h
        include/observer.h
        include/utils.h
        include/visitor.h

        src/dragon.cpp
        src/frog.cpp
        src/knight.cpp
        src/npc.cpp
        src/utils.cpp
        main.cpp
)
target_include_directories(lab6 PRIVATE include)

# Добавление тестов
enable_testing()

add_executable(tests gtests/tests06.cpp
        include/dragon.h
        include/factory.h
        include/frog.h
        include/knight.h
        include/npc.h
        include/observer.h
        include/utils.h
        include/visitor.h

        src/dragon.cpp
        src/frog.cpp
        src/knight.cpp
        src/npc.cpp
        src/utils.cpp
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)
