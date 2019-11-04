cmake_minimum_required(VERSION 2.8)

file(GLOB KKKVS_SOURCES *.cpp)

add_library(kkkvs_static STATIC ${KKKVS_SOURCES})
set_target_properties(kkkvs_static PROPERTIES OUTPUT_NAME kkkvs)
add_library(kkkvs SHARED ${KKKVS_SOURCES})

install(TARGETS
        kkkvs
        kkkvs_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/kkkvs/*.hpp)
install(FILES ${HEADER_FILES} DESTINATION include/kkkvs)
