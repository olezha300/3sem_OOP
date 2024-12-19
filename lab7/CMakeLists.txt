cmake_minimum_required(VERSION 3.10)
project(LabWork1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS Off)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.15.2
            TLS_VERIFY false
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG v3.11.2
            TLS_VERIFY false
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}/factories)
include_directories(${INCLUDE_DIR}/configs)
include_directories(${INCLUDE_DIR}/game)
include_directories(${INCLUDE_DIR}/npcs)
include_directories(${INCLUDE_DIR}/observers)
include_directories(${INCLUDE_DIR}/visitors)


file(GLOB_RECURSE LIB_HEADERS "${INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE LIB_SOURCES "${SRC_DIR}/*.cpp")

add_library(lab6_lib ${LIB_HEADERS} ${LIB_SOURCES})

target_link_libraries(lab6_lib PRIVATE nlohmann_json::nlohmann_json)
include_directories(${nlohmann_json_SOURCE_DIR}/include)


add_executable(main_file_exe main.cpp)
target_link_libraries(main_file_exe PRIVATE lab6_lib)


# Найти и подключить fmt
find_package(fmt REQUIRED)
# Подключить fmt к основной библиотеке
target_link_libraries(lab6_lib PRIVATE fmt::fmt)
# Подключить fmt к исполняемому файлу
target_link_libraries(main_file_exe PRIVATE lab6_lib fmt::fmt)

enable_testing()

function(add_gtest_executable TEST_NAME TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} GTest::GTest GTest::Main lab6_lib)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_gtest_executable(tests ${TEST_DIR}/tests.cpp)
