cmake_minimum_required(VERSION 3.10)

file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testhello ${SRCS})

TARGET_LINK_LIBRARIES(testhello
    hello
    gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET testhello)