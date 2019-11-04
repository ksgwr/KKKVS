cmake_minimum_required(VERSION 2.8.4)

project(jkkkvs)
set(CMAKE_CXX_STANDARD 11)
if (MSVC)
  set(CMAKE_CXX_FLAGS "/utf-8 /EHsc /MTd")
else()
  set(CMAKE_CSS_FLAGS "-fPIC")
endif()

find_package(JNI REQUIRED)

file(GLOB JKKKVS_SOURCE *.cpp)
add_library(jkkkvs SHARED ${JKKKVS_SOURCE})

if (NOT STATIC_LIB_PATH)
  set(STATIC_LIB_PATH kkkvs)
endif()

message("static_lib_path: ${STATIC_LIB_PATH}")
if (NOT EXISTS "${STATIC_LIB_PATH}")
   message("not exists file")
endif()

target_include_directories(jkkkvs PRIVATE ${JNI_INCLUDE_DIRS} ${INCLUDE_DIR_PATH})

target_link_libraries(jkkkvs ${JNI_LIBRARIES} ${STATIC_LIB_PATH})

