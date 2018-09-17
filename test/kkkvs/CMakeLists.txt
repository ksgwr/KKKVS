file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testkkkvs ${SRCS})

TARGET_LINK_LIBRARIES(testkkkvs
    kkkvs
    gtest_main
)

add_test(NAME testkkkvs
         COMMAND testkkkvs)