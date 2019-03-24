cmake_minimum_required(VERSION 2.8)

file(GLOB KKKVS_SOURCES *.cpp)

add_library(kkkvs_static STATIC ${KKKVS_SOURCES})
set_target_properties(kkkvs_static PROPERTIES OUTPUT_NAME kkkvs)
add_library(kkkvs SHARED ${KKKVS_SOURCES})