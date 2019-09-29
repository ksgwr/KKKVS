cmake_minimum_required(VERSION 2.8)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

add_subdirectory(kkkvs)
add_subdirectory(hello)