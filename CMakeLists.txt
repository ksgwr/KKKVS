cmake_minimum_required(VERSION 2.8.4)

project(kkkvs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

# include path
include_directories(include)

# libraries
add_subdirectory(lib)

# executables
add_executable(main main.cpp)
target_link_libraries(main
    hello)

# tests
if(NOT without-test)
    enable_testing()
    add_subdirectory(test)
endif()