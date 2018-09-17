cmake_minimum_required(VERSION 2.8)

file(GLOB KKKVS_SOURCES *.cpp)

add_library(kkkvs STATIC ${KKKVS_SOURCES})