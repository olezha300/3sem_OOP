cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Установка nlohmann/json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
        TLS_VERIFY false
)
FetchContent_MakeAvailable(nlohmann_json)

# Установка fmt
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        TLS_VERIFY false
)
FetchContent_MakeAvailable(fmt)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/gtests")

include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}/factories)
include_directories(${INCLUDE_DIR}/configs)
include_directories(${INCLUDE_DIR}/game)
include_directories(${INCLUDE_DIR}/npcs)
include_directories(${INCLUDE_DIR}/observers)
include_directories(${INCLUDE_DIR}/visitors)

file(GLOB_RECURSE LIB_HEADERS "${INCLUDE_DIR}/*.hpp")
file(GLOB_RECURSE LIB_SOURCES "${SRC_DIR}/*.cpp")

add_library(lab7_lib ${LIB_HEADERS} ${LIB_SOURCES})
target_link_libraries(lab7_lib PRIVATE pthread nlohmann_json fmt)
include_directories(${nlohmann_json_SOURCE_DIR}/include)
add_executable(lab7 main.cpp)
target_link_libraries(lab7 PRIVATE lab7_lib pthread nlohmann_json fmt)

enable_testing()

function(add_gtest_executable TEST_NAME TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} gtest_main lab7_lib pthread nlohmann_json fmt)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_gtest_executable(tests gtests/tests07.cpp)
