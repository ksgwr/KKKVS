cmake_minimum_required(VERSION 2.8.4)

project(jkkkvs)
set(CMAKE_CXX_STANDARD 11)

find_package(JNI REQUIRED)

file(GLOB JKKKVS_SOURCE *.c)
add_library(jkkkvs SHARED ${JKKKVS_SOURCE})

target_include_directories(jkkkvs
        PRIVATE
            ${JNI_INCLUDE_DIRS}
        )
target_link_libraries(jkkkvs ${JNI_LIBRARIES})

