cmake_minimum_required(VERSION 2.8.4)

project(kkkvs)
set(CMAKE_CXX_STANDARD 11)
if (MSVC)
  set(CMAKE_CXX_FLAGS "/utf-8 /EHsc /MTd")
else()
  set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")
endif()

# include path
include_directories(include)

# libraries
add_subdirectory(lib)

# java
#if (NOT APPLE) # wait for release gradle 6.0 (java 13)
#  add_subdirectory(java)
#endif()

# python
add_subdirectory(python)

# executables
add_executable(main main.cpp)
target_link_libraries(main
    hello)

# tests
if(NOT without-test)
  enable_testing()
  # skip test because it can not build gtest in MSVC
  if (NOT MSVC)
    add_subdirectory(test)
  endif()
endif()